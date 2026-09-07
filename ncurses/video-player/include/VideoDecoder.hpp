#pragma once

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

class VideoDecoder
{
public:
    explicit VideoDecoder(const char* filename);
    ~VideoDecoder();

    bool open();
    bool readFrame();

    AVFrame* getFrame() const;

    int getWidth() const;
    int getHeight() const;

    double getFPS() const;

private:
    const char* filename_;

    AVFormatContext* formatContext_;
    AVCodecContext* codecContext_;
    AVFrame* frame_;
    AVFrame* rgbFrame_;

    SwsContext* swsContext_;

    int videoStreamIndex_;

    int width_;
    int height_;

    double fps_;

    uint8_t* rgbBuffer_;
};