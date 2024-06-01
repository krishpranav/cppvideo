/**
 * @file video_reader.hpp
 * @author Krisna Pranav
 * @brief video reader
 * @version 1.0
 * @date 2024-06-01
 *
 * @copyright Copyright (c) 2024 Krisna Pranav
 *
 */

#ifndef video_reader_hpp
#define video_reader_hpp

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <inittypes.h>
} // extern "C"

struct VideoReaderState
{
    int width, height;

    AVRational time_base;

    AVFormatContext *av_format_ctx;
    AVCodecContext *av_codec_ctx;

    int video_stream_index;

    AVFrame *av_frame;
    AVPacket *av_packet;

    SwsContext *sws_scaler_ctx;
}; // struct VideoReaderState

/**
 * @param state
 * @param filename
 * @return true
 * @return false
 */
bool video_reader_open(VideoReaderState *state, const char *filename);

/**
 * @param state
 * @param frame_buffer
 * @param pts
 * @return true
 * @return false
 */
bool video_reader_read_frame(VideoReaderState *state, uint8_t *frame_buffer, int64_t *pts);

/**
 * @param state
 * @param ts
 * @return true
 * @return false
 */
bool video_reader_seek_frame(VideoReaderState *state, int64_t ts);

/**
 * @param state
 */
void video_reader_close(VideoReaderState *state);

#endif