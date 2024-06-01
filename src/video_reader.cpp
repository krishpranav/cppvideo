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

    if (avformat_open_input(&av_format_ctx, filename, NULL, NULL) != 0)
    {
        printf("Couldn't open file\n");
        return false;
    }

    video_stream_index = -1;

    AVCodecParameters *av_codec_params;
    AVCodec *av_codec;

    for (int i = 0; i < av_format_ctx->nb_streams; ++i)
    {
        av_codec_params = av_format_ctx->streams[i]->codecpar;
        av_codec = const_cast<AVCodec *>(avcodec_find_decoder(av_codec_params->codec_id));
        if (!av_codec)
        {
            continue;
        }

        if (av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            video_stream_index = i;
            width = av_codec_params->width;
            height = av_codec_params->height;
            time_base = av_format_ctx->streams[i]->time_base;
            break;
        }
    }

    if (video_stream_index == -1)
    {
        printf("Couldn't find  valid video stream inside file\n");
        return false;
    }

    av_codec_ctx = avcodec_alloc_context3(av_codec);

    if (!av_codec_ctx)
    {
        printf("Couldn't create AVCodecContext\n");
        return false;
    }

    if (avcodec_parameters_to_context(av_codec_ctx, av_codec_params) < 0)
    {
        printf("Couldn't initialize AVCodecContext\n");
        return false;
    }

    if (avcodec_open2(av_codec_ctx, av_codec, NULL) < 0)
    {
        printf("Couldn't open codec\n");
        return false;
    }

    av_frame = av_frame_alloc();

    if (!av_frame)
    {
        printf("Couldn't allocate AVFrame\n");
        return false;
    }

    av_packet = av_packet_alloc();

    if (!av_packet)
    {
        printf("Couldn't allocate AVPacket\n");
        return false;
    }

    return true;
}