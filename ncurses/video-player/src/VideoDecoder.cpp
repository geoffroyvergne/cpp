#include "VideoDecoder.hpp"

#include <iostream>
#include <algorithm>

VideoDecoder::VideoDecoder(const char* filename)
    : filename_(filename),
      formatContext_(nullptr),
      codecContext_(nullptr),
      frame_(nullptr),
      rgbFrame_(nullptr),
      swsContext_(nullptr),
      packet_(nullptr),
      videoStreamIndex_(-1),
      width_(0),
      height_(0),
      fps_(30.0),
      currentPTS_(0.0),
      duration_(0.0),
      rgbBuffer_(nullptr),
      endOfStream_(false)
{
}

VideoDecoder::~VideoDecoder()
{
    if (packet_)
    {
        av_packet_free(&packet_);
    }

    if (rgbBuffer_)
    {
        av_free(rgbBuffer_);
        rgbBuffer_ = nullptr;
    }

    if (rgbFrame_)
    {
        av_frame_free(&rgbFrame_);
    }

    if (frame_)
    {
        av_frame_free(&frame_);
    }

    if (swsContext_)
    {
        sws_freeContext(swsContext_);
        swsContext_ = nullptr;
    }

    if (codecContext_)
    {
        avcodec_free_context(&codecContext_);
    }

    if (formatContext_)
    {
        avformat_close_input(&formatContext_);
    }
}

bool VideoDecoder::open()
{
    // ------------------------------------------------------------
    // Open file
    // ------------------------------------------------------------

    if (avformat_open_input(
            &formatContext_,
            filename_,
            nullptr,
            nullptr) < 0)
    {
        std::cerr
            << "Error: could not open video file: "
            << filename_
            << std::endl;

        return false;
    }

    // ------------------------------------------------------------
    // Stream information
    // ------------------------------------------------------------

    if (avformat_find_stream_info(
            formatContext_,
            nullptr) < 0)
    {
        std::cerr
            << "Error: could not find stream information."
            << std::endl;

        return false;
    }

    // ------------------------------------------------------------
    // Find video stream
    // ------------------------------------------------------------

    for (unsigned int i = 0;
         i < formatContext_->nb_streams;
         ++i)
    {
        if (formatContext_->streams[i]->codecpar->codec_type
            == AVMEDIA_TYPE_VIDEO)
        {
            videoStreamIndex_ =
                static_cast<int>(i);

            break;
        }
    }

    if (videoStreamIndex_ < 0)
    {
        std::cerr
            << "Error: no video stream found."
            << std::endl;

        return false;
    }

    AVStream* videoStream =
        formatContext_->streams[
            videoStreamIndex_
        ];

    // ------------------------------------------------------------
    // Duration
    // ------------------------------------------------------------

    if (videoStream->duration != AV_NOPTS_VALUE)
    {
        duration_ =
            videoStream->duration *
            av_q2d(videoStream->time_base);
    }
    else if (formatContext_->duration != AV_NOPTS_VALUE)
    {
        duration_ =
            formatContext_->duration /
            static_cast<double>(AV_TIME_BASE);
    }

    // ------------------------------------------------------------
    // Find decoder
    // ------------------------------------------------------------

    const AVCodecParameters* codecParameters =
        videoStream->codecpar;

    const AVCodec* codec =
        avcodec_find_decoder(
            codecParameters->codec_id
        );

    if (!codec)
    {
        std::cerr
            << "Error: decoder not found."
            << std::endl;

        return false;
    }

    // ------------------------------------------------------------
    // Codec context
    // ------------------------------------------------------------

    codecContext_ =
        avcodec_alloc_context3(codec);

    if (!codecContext_)
    {
        std::cerr
            << "Error: could not allocate codec context."
            << std::endl;

        return false;
    }

    if (avcodec_parameters_to_context(
            codecContext_,
            codecParameters) < 0)
    {
        std::cerr
            << "Error: could not copy codec parameters."
            << std::endl;

        return false;
    }

    // ------------------------------------------------------------
    // Open decoder
    // ------------------------------------------------------------

    if (avcodec_open2(
            codecContext_,
            codec,
            nullptr) < 0)
    {
        std::cerr
            << "Error: could not open codec."
            << std::endl;

        return false;
    }

    // ------------------------------------------------------------
    // Dimensions
    // ------------------------------------------------------------

    width_ =
        codecContext_->width;

    height_ =
        codecContext_->height;

    // ------------------------------------------------------------
    // FPS
    // ------------------------------------------------------------

    AVRational frameRate =
        videoStream->avg_frame_rate;

    if (frameRate.num > 0 &&
        frameRate.den > 0)
    {
        fps_ =
            av_q2d(frameRate);
    }

    if (fps_ <= 0.0)
    {
        fps_ = 30.0;
    }

    // ------------------------------------------------------------
    // Frames
    // ------------------------------------------------------------

    frame_ =
        av_frame_alloc();

    rgbFrame_ =
        av_frame_alloc();

    if (!frame_ ||
        !rgbFrame_)
    {
        std::cerr
            << "Error: could not allocate frames."
            << std::endl;

        return false;
    }

    // ------------------------------------------------------------
    // Packet
    // ------------------------------------------------------------

    packet_ =
        av_packet_alloc();

    if (!packet_)
    {
        std::cerr
            << "Error: could not allocate packet."
            << std::endl;

        return false;
    }

    // ------------------------------------------------------------
    // RGB buffer
    // ------------------------------------------------------------

    int bufferSize =
        av_image_get_buffer_size(
            AV_PIX_FMT_RGB24,
            width_,
            height_,
            1
        );

    rgbBuffer_ =
        static_cast<uint8_t*>(
            av_malloc(bufferSize)
        );

    if (!rgbBuffer_)
    {
        std::cerr
            << "Error: could not allocate RGB buffer."
            << std::endl;

        return false;
    }

    av_image_fill_arrays(
        rgbFrame_->data,
        rgbFrame_->linesize,
        rgbBuffer_,
        AV_PIX_FMT_RGB24,
        width_,
        height_,
        1
    );

    rgbFrame_->format =
        AV_PIX_FMT_RGB24;

    rgbFrame_->width =
        width_;

    rgbFrame_->height =
        height_;

    // ------------------------------------------------------------
    // Pixel conversion
    // ------------------------------------------------------------

    swsContext_ =
        sws_getContext(
            width_,
            height_,
            codecContext_->pix_fmt,

            width_,
            height_,
            AV_PIX_FMT_RGB24,

            SWS_BILINEAR,

            nullptr,
            nullptr,
            nullptr
        );

    if (!swsContext_)
    {
        std::cerr
            << "Error: could not create SwsContext."
            << std::endl;

        return false;
    }

    currentPTS_ = 0.0;
    endOfStream_ = false;

    return true;
}

bool VideoDecoder::readFrame()
{
    if (endOfStream_)
    {
        return false;
    }

    AVStream* videoStream =
        formatContext_->streams[
            videoStreamIndex_
        ];

    while (true)
    {
        // --------------------------------------------------------
        // First try to receive a frame already buffered
        // by the decoder.
        // --------------------------------------------------------

        int ret =
            avcodec_receive_frame(
                codecContext_,
                frame_
            );

        if (ret == 0)
        {
            // ----------------------------------------------------
            // Convert to RGB
            // ----------------------------------------------------

            sws_scale(
                swsContext_,
                frame_->data,
                frame_->linesize,
                0,
                height_,
                rgbFrame_->data,
                rgbFrame_->linesize
            );

            // ----------------------------------------------------
            // Get presentation timestamp.
            //
            // best_effort_timestamp is preferable to raw PTS
            // when dealing with codecs that reorder frames.
            // ----------------------------------------------------

            int64_t pts =
                frame_->best_effort_timestamp;

            if (pts != AV_NOPTS_VALUE)
            {
                currentPTS_ =
                    pts *
                    av_q2d(
                        videoStream->time_base
                    );
            }

            return true;
        }

        if (ret != AVERROR(EAGAIN) &&
            ret != AVERROR_EOF)
        {
            std::cerr
                << "Warning: error receiving frame."
                << std::endl;

            return false;
        }

        if (ret == AVERROR_EOF)
        {
            endOfStream_ = true;
            return false;
        }

        // --------------------------------------------------------
        // Decoder needs another packet.
        // --------------------------------------------------------

        ret =
            av_read_frame(
                formatContext_,
                packet_
            );

        if (ret < 0)
        {
            // ----------------------------------------------------
            // EOF: flush decoder.
            // ----------------------------------------------------

            avcodec_send_packet(
                codecContext_,
                nullptr
            );

            continue;
        }

        // --------------------------------------------------------
        // Ignore audio / other streams.
        // --------------------------------------------------------

        if (packet_->stream_index !=
            videoStreamIndex_)
        {
            av_packet_unref(packet_);
            continue;
        }

        // --------------------------------------------------------
        // Send packet to decoder.
        // --------------------------------------------------------

        ret =
            avcodec_send_packet(
                codecContext_,
                packet_
            );

        av_packet_unref(packet_);

        if (ret < 0)
        {
            std::cerr
                << "Warning: error sending packet "
                   "to decoder."
                << std::endl;

            continue;
        }

        // Loop back and call receive_frame().
    }
}

bool VideoDecoder::seekTo(double seconds)
{
    if (!formatContext_)
    {
        return false;
    }

    AVStream* videoStream =
        formatContext_->streams[
            videoStreamIndex_
        ];

    // ------------------------------------------------------------
    // Clamp target position
    // ------------------------------------------------------------

    if (duration_ > 0.0)
    {
        seconds =
            std::clamp(
                seconds,
                0.0,
                duration_
            );
    }
    else
    {
        seconds =
            std::max(
                0.0,
                seconds
            );
    }

    // ------------------------------------------------------------
    // Convert seconds to stream timestamp
    // ------------------------------------------------------------

    int64_t timestamp =
        static_cast<int64_t>(
            seconds /
            av_q2d(videoStream->time_base)
        );

    // ------------------------------------------------------------
    // Seek to the previous keyframe.
    //
    // FFmpeg normally cannot jump directly to an arbitrary frame.
    // It jumps to a keyframe, then we decode forward.
    // ------------------------------------------------------------

    int ret =
        av_seek_frame(
            formatContext_,
            videoStreamIndex_,
            timestamp,
            AVSEEK_FLAG_BACKWARD
        );

    if (ret < 0)
    {
        return false;
    }

    // ------------------------------------------------------------
    // Clear decoder buffers.
    // ------------------------------------------------------------

    avcodec_flush_buffers(
        codecContext_
    );

    av_packet_unref(packet_);

    endOfStream_ = false;

    // ------------------------------------------------------------
    // Reset current position.
    // ------------------------------------------------------------

    currentPTS_ = 0.0;

    // ------------------------------------------------------------
    // Decode until we reach the requested position.
    //
    // Example:
    //
    // Requested: 37 seconds
    //
    // FFmpeg seeks to keyframe at 34 seconds.
    //
    // 34.0
    // 34.04
    // 34.08
    // ...
    // 36.96
    // 37.00  <-- stop here
    // ------------------------------------------------------------

    while (true)
    {
        if (!readFrame())
        {
            return false;
        }

        if (currentPTS_ >= seconds)
        {
            break;
        }
    }

    return true;
}

bool VideoDecoder::seekRelative(double seconds)
{
    return seekTo(
        currentPTS_ + seconds
    );
}

AVFrame* VideoDecoder::getFrame() const
{
    return rgbFrame_;
}

int VideoDecoder::getWidth() const
{
    return width_;
}

int VideoDecoder::getHeight() const
{
    return height_;
}

double VideoDecoder::getFPS() const
{
    return fps_;
}

double VideoDecoder::getCurrentPTS() const
{
    return currentPTS_;
}

double VideoDecoder::getDuration() const
{
    return duration_;
}