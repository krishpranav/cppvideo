/**
 * @file video_reader.cpp
 * @author Krisna Pranav
 * @brief video_reader
 * @version 1.0
 * @date 2024-06-01
 *
 * @copyright Copyright (c) 2024 Krisna Pranav
 *
 */

#include "video_reader.hpp"

/**
 * @param errnum
 * @return const char*
 */
static const char *av_make_error(int errnum)
{
    static char str[AV_ERROR_MAX_STRING_SIZE];
    memset(str, 0, sizeof(str));
    return av_make_error_string(str, AV_ERROR_MAX_STRING_SIZE, errnum);
}

/**
 * @param pix_fmt
 * @return AVPixelFormat
 */
static AVPixelFormat correct_for_deprecated_pixel_format(AVPixelFormat pix_fmt)
{
    switch (pix_fmt)
    {
    case AV_PIX_FMT_YUVJ420P:
        return AV_PIX_FMT_YUV420P;
    case AV_PIX_FMT_YUVJ422P:
        return AV_PIX_FMT_YUV422P;
    case AV_PIX_FMT_YUVJ444P:
        return AV_PIX_FMT_YUV444P;
    case AV_PIX_FMT_YUVJ440P:
        return AV_PIX_FMT_YUV440P;
    default:
        return pix_fmt;
    }
}

/**
 * @param state
 * @param filename
 * @return true
 * @return false
 */
bool video_reader_open(VideoReaderState *state, const char *filename)
{
    auto &width = state->width;
    auto &height = state->height;
    auto &time_base = state->time_base;
    auto &av_format_ctx = state->av_format_ctx;
    auto &av_codec_ctx = state->av_codec_ctx;
    auto &video_stream_index = state->video_stream_index;
    auto &av_frame = state->av_frame;
    auto &av_packet = state->av_packet;

    av_format_ctx = avformat_alloc_context();

    if (!av_format_ctx)
    {
        printf("Couldn't created AVFormatContext\n");
        return false;
    }
}