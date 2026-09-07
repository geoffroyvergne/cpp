#pragma once

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/rational.h>
#include <libswscale/swscale.h>
}

class VideoDecoder
{
public:
    explicit VideoDecoder(const char* filename);
    ~VideoDecoder();

    bool open();

    // Decode next frame.
    bool readFrame();

    // Seek relatively from the current position.
    bool seekRelative(double seconds);

    // Seek to an absolute position in seconds.
    bool seekTo(double seconds);

    AVFrame* getFrame() const;

    int getWidth() const;
    int getHeight() const;

    double getFPS() const;

    // PTS of current frame in seconds.
    double getCurrentPTS() const;

    // Duration of the video in seconds.
    double getDuration() const;

private:
    const char* filename_;

    AVFormatContext* formatContext_;
    AVCodecContext* codecContext_;

    AVFrame* frame_;
    AVFrame* rgbFrame_;

    SwsContext* swsContext_;

    AVPacket* packet_;

    int videoStreamIndex_;

    int width_;
    int height_;

    double fps_;

    double currentPTS_;
    double duration_;

    uint8_t* rgbBuffer_;

    bool endOfStream_;
};
