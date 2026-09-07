#include "VideoDecoder.hpp"

#include <iostream>
#include <stdexcept>


VideoDecoder::VideoDecoder(const char* filename)
    : filename_(filename),
      formatContext_(nullptr),
      codecContext_(nullptr),
      frame_(nullptr),
      rgbFrame_(nullptr),
      swsContext_(nullptr),
      videoStreamIndex_(-1),
      width_(0),
      height_(0),
      fps_(30.0),
      rgbBuffer_(nullptr)
{
}


VideoDecoder::~VideoDecoder()
{
    if (rgbBuffer_) {
        av_free(rgbBuffer_);
    }

    if (rgbFrame_) {
        av_frame_free(&rgbFrame_);
    }

    if (frame_) {
        av_frame_free(&frame_);
    }

    if (swsContext_) {
        sws_freeContext(swsContext_);
    }

    if (codecContext_) {
        avcodec_free_context(&codecContext_);
    }

    if (formatContext_) {
        avformat_close_input(&formatContext_);
    }
}


bool VideoDecoder::open()
{
    // --------------------------------------------------
    // Open video file
    // --------------------------------------------------

    if (avformat_open_input(
            &formatContext_,
            filename_,
            nullptr,
            nullptr) < 0)
    {
        std::cerr << "Could not open video: "
                  << filename_
                  << std::endl;

        return false;
    }


    // --------------------------------------------------
    // Read stream information
    // --------------------------------------------------

    if (avformat_find_stream_info(
            formatContext_,
            nullptr) < 0)
    {
        std::cerr << "Could not find stream information"
                  << std::endl;

        return false;
    }


    // --------------------------------------------------
    // Find video stream
    // --------------------------------------------------

    for (unsigned int i = 0;
         i < formatContext_->nb_streams;
         ++i)
    {
        if (formatContext_->streams[i]->codecpar->codec_type
            == AVMEDIA_TYPE_VIDEO)
        {
            videoStreamIndex_ = static_cast<int>(i);
            break;
        }
    }


    if (videoStreamIndex_ == -1)
    {
        std::cerr << "No video stream found"
                  << std::endl;

        return false;
    }


    AVStream* videoStream =
        formatContext_->streams[videoStreamIndex_];

    AVCodecParameters* codecParameters =
        videoStream->codecpar;


    // --------------------------------------------------
    // Find decoder
    // --------------------------------------------------

    const AVCodec* codec =
        avcodec_find_decoder(codecParameters->codec_id);

    if (!codec)
    {
        std::cerr << "Could not find decoder"
                  << std::endl;

        return false;
    }


    // --------------------------------------------------
    // Create codec context
    // --------------------------------------------------

    codecContext_ = avcodec_alloc_context3(codec);

    if (!codecContext_)
    {
        std::cerr << "Could not allocate codec context"
                  << std::endl;

        return false;
    }


    if (avcodec_parameters_to_context(
            codecContext_,
            codecParameters) < 0)
    {
        std::cerr << "Could not copy codec parameters"
                  << std::endl;

        return false;
    }


    // --------------------------------------------------
    // Open decoder
    // --------------------------------------------------

    if (avcodec_open2(
            codecContext_,
            codec,
            nullptr) < 0)
    {
        std::cerr << "Could not open codec"
                  << std::endl;

        return false;
    }


    width_ = codecContext_->width;
    height_ = codecContext_->height;


    // --------------------------------------------------
    // Get FPS
    // --------------------------------------------------

    AVRational frameRate =
        videoStream->avg_frame_rate;

    if (frameRate.num != 0 &&
        frameRate.den != 0)
    {
        fps_ = av_q2d(frameRate);
    }

    if (fps_ <= 0.0) {
        fps_ = 30.0;
    }


    // --------------------------------------------------
    // Allocate frames
    // --------------------------------------------------

    frame_ = av_frame_alloc();
    rgbFrame_ = av_frame_alloc();

    if (!frame_ || !rgbFrame_)
    {
        std::cerr << "Could not allocate frames"
                  << std::endl;

        return false;
    }


    // --------------------------------------------------
    // RGB buffer
    // --------------------------------------------------

    int numBytes =
        av_image_get_buffer_size(
            AV_PIX_FMT_RGB24,
            width_,
            height_,
            1);

    rgbBuffer_ =
        static_cast<uint8_t*>(
            av_malloc(numBytes)
        );

    if (!rgbBuffer_)
    {
        std::cerr << "Could not allocate RGB buffer"
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


    // --------------------------------------------------
    // Create pixel format converter
    // --------------------------------------------------

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
        std::cerr << "Could not create "
                     "pixel converter"
                  << std::endl;

        return false;
    }


    return true;
}


bool VideoDecoder::readFrame()
{
    AVPacket* packet = av_packet_alloc();

    if (!packet)
        return false;


    while (av_read_frame(formatContext_, packet) >= 0)
    {
        if (packet->stream_index != videoStreamIndex_)
        {
            av_packet_unref(packet);
            continue;
        }


        // Send packet to decoder
        int result =
            avcodec_send_packet(
                codecContext_,
                packet
            );

        av_packet_unref(packet);


        if (result < 0)
            continue;


        // Receive decoded frame
        result =
            avcodec_receive_frame(
                codecContext_,
                frame_
            );


        if (result == 0)
        {
            // Convert decoded frame to RGB

            sws_scale(
                swsContext_,

                frame_->data,
                frame_->linesize,

                0,
                height_,

                rgbFrame_->data,
                rgbFrame_->linesize
            );

            av_packet_free(&packet);

            return true;
        }
    }


    av_packet_free(&packet);

    return false;
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