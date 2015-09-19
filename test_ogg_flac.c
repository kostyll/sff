#include <stdio.h>

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>

#include "general.h"

AVStream * add_video_output(AVFormatContext * fmt_ctx, AVCodecContext * cctx, char *outfile){

    AVStream * stream = NULL;

    AVCodec * vcodec = NULL;
    AVCodecContext * vcodec_ctx = NULL;

    vcodec = avcodec_find_encoder(AV_CODEC_ID_THEORA);
    if (vcodec == NULL) die("Cannot find video encoder THEORA\n");

    stream = avformat_new_stream(fmt_ctx, vcodec);

    vcodec_ctx = stream->codec;

    vcodec_ctx->codec_id = AV_CODEC_ID_THEORA;
    vcodec_ctx->codec_type = AVMEDIA_TYPE_VIDEO;
    vcodec_ctx->bit_rate = 1000000;
    vcodec_ctx->width = 800;
    vcodec_ctx->height = 600;
    vcodec_ctx->time_base = (AVRational){1, 25};
    vcodec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;

    if (avcodec_open2(vcodec_ctx, vcodec, NULL) < 0) die("Cannot open THEORA encoder\n");

    return stream;
}

AVStream * add_audio_output(AVFormatContext * fmt_ctx, AVCodecContext * cctx, char *outfile){
    AVStream * stream = NULL;

    AVCodec * acodec = NULL;
    AVCodecContext * acodec_ctx = NULL;

    acodec = avcodec_find_encoder(AV_CODEC_ID_FLAC);
    if (acodec == NULL) die("Cannot find video encoder FLAC\n");

    stream = avformat_new_stream(fmt_ctx, acodec);
    acodec_ctx = stream->codec;

    acodec_ctx->sample_fmt = AV_SAMPLE_FMT_S32;
    acodec_ctx->codec_type = AVMEDIA_TYPE_AUDIO;
    acodec_ctx->codec_id = AV_CODEC_ID_FLAC;
    acodec_ctx->bit_rate = 64000;
    acodec_ctx->sample_rate = 48000;
    acodec_ctx->channels = 2;

    if (avcodec_open2(acodec_ctx, acodec, NULL) < 0) die("Cannot open FLAC encoder\n");

    return stream;
}

int process_video_packet(
    InputSource * source,
    Output * output,
    TranscodingContext * tctx
){
    int frame_finished;

    avcodec_decode_video2(source->vctx, tctx->ivframe, &frame_finished, &tctx->curr_packet);
    tctx->ivframe->pts = av_rescale_q_rnd(
        tctx->curr_packet.pts,
        source->video_st->time_base,
        source->vctx->time_base,
        AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX
    );
    if (frame_finished){
        int frame_encoded;
        tctx->ovframe->pts = tctx->ivframe->pts;

        sws_scale(
            tctx->sws_ctx,
            (uint8_t const * const *)tctx->ivframe->data,
            tctx->ivframe->linesize,
            0,
            source->vctx->height,
            tctx->ovframe->data,
            tctx->ovframe->linesize
        );

        tctx->ovframe->pts = av_rescale_q_rnd(
                tctx->ivframe->pts,
                source->vctx->time_base,
                output->vctx->time_base,
                AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX
            );
        av_init_packet(&tctx->target_packet);
        tctx->target_packet.data = NULL;
        tctx->target_packet.size = 0;

        avcodec_encode_video2(output->vctx, &tctx->target_packet, tctx->ovframe, &frame_encoded);
        if (frame_encoded){
            tctx->target_packet.stream_index = output->video;
            tctx->target_packet.pos = -1;
            tctx->target_packet.pts = av_rescale_q_rnd(
                    tctx->target_packet.pts,
                    output->vctx->time_base,
                    output->video_st->time_base,
                    AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX
                );
            tctx->target_packet.dts = 0;
            if (av_interleaved_write_frame(output->ctx, &tctx->target_packet) != 0)
                die("Error while writing video packet\n");
            av_free_packet(&tctx->curr_packet);
            av_free_packet(&tctx->target_packet);
        }

        return 0;
    }
    return 0;
}

int process_audio_packet(
    InputSource * source,
    Output * output,
    TranscodingContext * tctx
){
    fprintf(stdout, "processing audio packet\n");
}

int main(int argc, char ** argv){
    if (argc != 3){
        fprintf(stderr, "Usage %s <infile> <outfile>\n", argv[0]);
        return 0;
    }
    char * outfile = NULL;
    outfile = argv[2];

    // Initialization
    av_register_all();
    avformat_network_init();

    //Opening input source
    InputSource * source = NULL;
    source = open_source(argv[1], 1, 1);


    //Creating output
    Output * output;
    output = open_output(
        outfile,
        add_video_output,
        add_audio_output,
        NULL,
        1,
        1
    );

    av_dump_format(output->ctx, 0, outfile, 1);

    avformat_write_header(output->ctx, NULL);

    TranscodingContext * trans_ctx = NULL;
    trans_ctx = build_transcoding_context(source, output);
    if (trans_ctx == NULL) die("Cannot build TranscodingContext\n");

    int ret;

    while(av_read_frame(source->ctx, &trans_ctx->curr_packet) >= 0){
        fprintf(stdout, "packet.pts = %d\n", trans_ctx->curr_packet.pts);
        if (trans_ctx->curr_packet.stream_index == source->video){
            ret = process_video_packet(
                    source,
                    output,
                    trans_ctx
                );
        } else if (trans_ctx->curr_packet.stream_index == source->audio){
            ret = process_audio_packet(
                    source,
                    output,
                    trans_ctx
                );
        }
    }

    av_write_trailer(output->ctx);

    avformat_close_input(&source->ctx);
    avformat_close_input(&output->ctx);

    return 0;
}
