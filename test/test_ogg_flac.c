#include <stdio.h>

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>

#include "general.h"
#include "transcode.h"

AVStream * add_video_output(AVFormatContext * fmt_ctx, AVCodecContext * cctx, char *outfile){

    AVStream * stream = NULL;

    AVCodec * vcodec = NULL;
    AVCodecContext * vcodec_ctx = NULL;

    vcodec = avcodec_find_encoder(AV_CODEC_ID_THEORA);
    if (vcodec == NULL) die("Cannot find video encoder THEORA");

    stream = avformat_new_stream(fmt_ctx, vcodec);

    vcodec_ctx = stream->codec;

    vcodec_ctx->codec_id = AV_CODEC_ID_THEORA;
    vcodec_ctx->codec_type = AVMEDIA_TYPE_VIDEO;
    vcodec_ctx->bit_rate = 1000000;
    vcodec_ctx->width = 800;
    vcodec_ctx->height = 600;
    vcodec_ctx->time_base = (AVRational){1, 25};
    vcodec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;

    if (avcodec_open2(vcodec_ctx, vcodec, NULL) < 0) die("Cannot open THEORA encoder");

    return stream;
}

AVStream * add_audio_output(AVFormatContext * fmt_ctx, AVCodecContext * cctx, char *outfile){
    AVStream * stream = NULL;

    AVCodec * acodec = NULL;
    AVCodecContext * acodec_ctx = NULL;

    acodec = avcodec_find_encoder(AV_CODEC_ID_FLAC);
    if (acodec == NULL) die("Cannot find video encoder FLAC");

    stream = avformat_new_stream(fmt_ctx, acodec);
    acodec_ctx = stream->codec;

    acodec_ctx->sample_fmt = AV_SAMPLE_FMT_S32;
    acodec_ctx->codec_type = AVMEDIA_TYPE_AUDIO;
    acodec_ctx->codec_id = AV_CODEC_ID_FLAC;
    acodec_ctx->bit_rate = 64000;
    acodec_ctx->sample_rate = 48000;
    acodec_ctx->channels = 2;

    if (avcodec_open2(acodec_ctx, acodec, NULL) < 0) die("Cannot open FLAC encoder");

    return stream;
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
    if (trans_ctx == NULL) die("Cannot build TranscodingContext");

    int ret;

    transcode(source, output, trans_ctx);

    av_write_trailer(output->ctx);

    avformat_close_input(&source->ctx);
    avformat_close_input(&output->ctx);

    return 0;
}
