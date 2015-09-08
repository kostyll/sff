#include <stdio.h>


#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>

#define STREAM_FRAME_RATE 25 /* 25 images/s */
#define STREAM_PIX_FMT PIX_FMT_YUV420P /* default pix_fmt */
#define STREAM_DURATION   5.0


AVFormatContext * open_input_source(char *source) {
    AVFormatContext * result = NULL;
    int err;
    
    // Open video file
    err = avformat_open_input(&result, source, NULL, NULL);
    if (err < 0) {
        fprintf(stderr, "ffmpeg: Unable to open input source%s\n", source);
    }

    // Retrieve stream information
    err = avformat_find_stream_info(result, NULL);
    if (err < 0) {
        fprintf(stderr, "ffmpeg: Unable to find stream info\n");
    }

    // Dump information about file onto standard error
    av_dump_format(result, 0, source, 0);

    return result;
}


int get_video_stream(AVFormatContext * fmt_ctx) {
    int video_stream;
    for (video_stream = 0; video_stream < fmt_ctx->nb_streams; ++video_stream){
        if (fmt_ctx->streams[video_stream]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            break;
        }
    }
    if (video_stream == fmt_ctx->nb_streams) {
        fprintf(stderr, "ffmpeg: Unable to find video stream\n");
        video_stream = -1;
    }
    return video_stream;
}

int get_audio_stream(AVFormatContext * fmt_ctx) {
    int audio_stream;
    for (audio_stream = 0; audio_stream < fmt_ctx->nb_streams; ++audio_stream){
        if (fmt_ctx->streams[audio_stream]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
            break;
        }
    }
    if (audio_stream == fmt_ctx->nb_streams) {
        fprintf(stderr, "ffmpeg: Unable to find audio stream\n");
        audio_stream = -1;
    }
    return audio_stream;
}


int main(int argc, char ** argv) {

    char * infile = NULL;
    char * outfile = NULL;
    int err;
    int ret;
    int i;

    if (argc != 3){
        fprintf(stderr, "Usage %s input_file output_file\n", argv[0]);
        return 0;
    } 

    infile = argv[1];
    outfile = argv[2];

    av_register_all();
    avcodec_register_all();

    AVInputFormat * ifmt = NULL;
    AVFormatContext * ifmt_ctx = NULL;

    AVOutputFormat * ofmt = NULL;
    AVFormatContext * ofmt_ctx = NULL;

    ifmt_ctx = open_input_source(infile);
    ifmt = ifmt_ctx->iformat;

    int video_stream = get_video_stream(ifmt_ctx);
    int audio_stream = get_audio_stream(ifmt_ctx);

    fprintf(stdout, "VideoStream = %d, AudioStream = %d\n", video_stream, audio_stream);

    AVStream *video_st = ifmt_ctx->streams[video_stream];
    AVStream *audio_st = ifmt_ctx->streams[audio_stream];

    AVCodecContext* ivcodec_ctx = ifmt_ctx->streams[video_stream]->codec;
    AVCodec* ivcodec = avcodec_find_decoder(ivcodec_ctx->codec_id);

    AVCodecContext* iacodec_ctx = ifmt_ctx->streams[audio_stream]->codec;
    AVCodec* iacodec = avcodec_find_decoder(iacodec_ctx->codec_id);

    err = avcodec_open2(ivcodec_ctx, ivcodec, NULL);
    if (err < 0) {
        fprintf(stderr, "ffmpeg: Unable to open video codec\n");
        return -1;
    }

    err = avcodec_open2(iacodec_ctx, iacodec, NULL);
    if (err < 0) {
        fprintf(stderr, "ffmpeg: Unable to open audio codec\n");
        return -1;
    }    

    AVFrame* frame = avcodec_alloc_frame();
    AVPacket packet;
    AVPacket packet_copy;
    AVPacket target_packet;

    avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, outfile);
    if (!ofmt_ctx) {
        fprintf(stderr, "Could not create output context\n");
        ret = AVERROR_UNKNOWN;
        return (-1);
    };
    ofmt = ofmt_ctx->oformat;


    // for (i = 0; i < ifmt_ctx->nb_streams; i++) {
    //     AVStream *in_stream = ifmt_ctx->streams[i];
    //     AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
    //     if (!out_stream) {
    //         fprintf(stderr, "Failed allocating output stream\n");
    //         ret = AVERROR_UNKNOWN;
    //         return (-1);
    //     }
    //     ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
    //     if (ret < 0) {
    //         fprintf(stderr, "Failed to copy context from input to output stream codec context\n");
    //         return (-1);
    //     }
    //     out_stream->codec->codec_tag = 0;
    //     if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
    //         out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
    // }
    // av_dump_format(ofmt_ctx, 0, outfile, 1);

    int vcodec_id, acodec_id;

    vcodec_id = av_guess_codec(ofmt, NULL, outfile, NULL, AVMEDIA_TYPE_VIDEO);
    acodec_id = av_guess_codec(ofmt, NULL, outfile, NULL, AVMEDIA_TYPE_AUDIO);

    fprintf(stdout, "VideoCodecID = %d, AudioCodecID = %d\n", vcodec_id, acodec_id);

    AVCodecContext* ovcodec_ctx = NULL;
    AVCodec* ovcodec = NULL;

    AVCodecContext* oacodec_ctx = NULL;
    AVCodec* oacodec = NULL;

    AVStream* ovstream = NULL;
    AVStream* oastream = NULL;

    ovcodec = avcodec_find_encoder(vcodec_id);
    oacodec = avcodec_find_encoder(acodec_id);

    ovstream = avformat_new_stream(ofmt_ctx, ovcodec);
    ovcodec_ctx = ovstream->codec;
    ovcodec_ctx->codec_id = vcodec_id;
    ovcodec_ctx->bit_rate = ivcodec_ctx->bit_rate;
    /* Resolution must be a multiple of two. */
    ovcodec_ctx->width    = ivcodec_ctx->width;
    ovcodec_ctx->height   = ivcodec_ctx->height;
    /* timebase: This is the fundamental unit of time (in seconds) in terms
     * of which frame timestamps are represented. For fixed-fps content,
     * timebase should be 1/framerate and timestamp increments should be
     * identical to 1. */
    ovcodec_ctx->time_base.den = STREAM_FRAME_RATE;
    ovcodec_ctx->time_base.num = 1;
    ovcodec_ctx->gop_size      = 12; /* emit one intra frame every twelve frames at most */
    ovcodec_ctx->pix_fmt       = STREAM_PIX_FMT;
    if (ovcodec_ctx->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
        /* just for testing, we also add B frames */
        ovcodec_ctx->max_b_frames = 2;
    }
    if (ovcodec_ctx->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
        /* Needed to avoid using macroblocks in which some coeffs overflow.
         * This does not happen with normal video, it just happens here as
         * the motion of the chroma plane does not match the luma plane. */
        ovcodec_ctx->mb_decision = 2;
    }

    oastream = avformat_new_stream(ofmt_ctx, oacodec);
    oacodec_ctx = oastream->codec;
    oacodec_ctx->sample_fmt  = oacodec->sample_fmts ?
    oacodec->sample_fmts[0] : AV_SAMPLE_FMT_FLTP;
    oacodec_ctx->bit_rate    = 64000;
    oacodec_ctx->sample_rate = 44100;
    oacodec_ctx->channels    = 2;
    oacodec_ctx->channel_layout = AV_CH_LAYOUT_STEREO;

    if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER) {
        ovstream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
        oastream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
    }

    err = avcodec_open2(ovcodec_ctx, ovcodec, NULL);
    if (err < 0) {
        fprintf(stderr, "ffmpeg: Unable to open video codec\n");
        return -1;
    }

    err = avcodec_open2(oacodec_ctx, oacodec, NULL);
    if (err < 0) {
        fprintf(stderr, "ffmpeg: Unable to open audio codec\n");
        return -1;
    }        

    int out_video_stream = get_video_stream(ofmt_ctx);
    int out_audio_stream = get_audio_stream(ofmt_ctx);

    AVStream * ovideo_st = NULL;
    AVStream * oaudio_st = NULL;

    ovideo_st = ofmt_ctx->streams[out_video_stream];
    oaudio_st = ofmt_ctx->streams[out_audio_stream];

    fprintf(stdout, "ovstream_ctx = %p\n", ovstream->codec);
    fprintf(stdout, "oastream_ctx = %p\n", oastream->codec);

    av_dump_format(ofmt_ctx, 0, outfile, 1);

    fprintf(stdout, "VideoStream = %d, AudioStream = %d\n", out_video_stream, out_audio_stream);    

    double audio_pts, video_pts;

    if (!(ofmt->flags & AVFMT_NOFILE)) {
        ret = avio_open(&ofmt_ctx->pb, outfile, AVIO_FLAG_WRITE);
        if (ret < 0) {
            fprintf(stderr, "Could not open output file '%s'", outfile);
            return (-1);
        }
    }    

    ret = avformat_write_header(ofmt_ctx, NULL);
    if (ret < 0) {
        fprintf(stderr, "Error occurred when opening output file\n");
        return (-1);
    };    

    while(av_read_frame(ifmt_ctx, &packet) >= 0) {
        // av_copy_packet(&packet_copy, &packet);

        // ret = av_interleaved_write_frame(ofmt_ctx, &packet_copy);
        // if (ret < 0) {
        //     fprintf(stderr, "Error muxing packet\n");
        // };

        // fprintf(stdout, "READ new PACKET\n");

        if (packet.stream_index == video_stream)
        {
            int frame_finished;
            int frame_encoded;
            // fprintf(stdout, "PACKAT FROM VIDEOSTREAM\n");

            avcodec_decode_video2(ivcodec_ctx, frame, &frame_finished, &packet);
            // fprintf(stdout, "DECODED\n");

            if (frame_finished == 1){
                av_init_packet(&target_packet);
                // fprintf(stdout, "FRAME_FINISHED\n");
                /* compute current audio and video time */
                if (oaudio_st)
                    audio_pts = (double)oaudio_st->pts.val * oaudio_st->time_base.num / oaudio_st->time_base.den;
                else
                    audio_pts = 0.0;

                if (ovideo_st)
                    video_pts = (double)ovideo_st->pts.val * ovideo_st->time_base.num / ovideo_st->time_base.den;
                else
                    video_pts = 0.0;

                // fprintf(stdout, "video_pts = %f, oudio_pts = %f \n", video_pts, audio_pts);

                // if ((!oaudio_st || audio_pts >= STREAM_DURATION) &&
                //     (!ovideo_st || video_pts >= STREAM_DURATION))
                //     break;

                /* write interleaved audio and video frames */
                // if (!ovideo_st || (ovideo_st && oaudio_st && audio_pts < video_pts)) {
                //     ;;
                // } else { };
                // fprintf(stdout, "Encoding ....\n");
                avcodec_encode_video2(ovcodec_ctx, &target_packet, frame, &frame_encoded);
                if (frame_encoded) {
                    fprintf(stdout, "video_pts = %f, oudio_pts = %f \n", video_pts, audio_pts);
                    target_packet.pts = av_frame_get_best_effort_timestamp(frame);
                    fprintf(stdout, "ENCODED with data_size = %d\n", target_packet.size);

                    av_write_frame(ofmt_ctx, &target_packet);
                    // av_interleaved_write_frame(ofmt_ctx, &target_packet);
                    fprintf(stdout, "WRITTEN\n");
                    av_free_packet(&target_packet);
                    // }
                }
                av_free_packet(&packet);

            }

        }

        // Free the packet that was allocated by av_read_frame
        
    }

    av_write_trailer(ofmt_ctx);

    // Free the YUV frame
    av_free(frame);

    // Close the codec
    avcodec_close(ivcodec_ctx);
    avcodec_close(iacodec_ctx);

    // Close the video file
    avformat_close_input(&ifmt_ctx);

    /* free the streams */
    for(i = 0; i < ofmt_ctx->nb_streams; i++) {
        av_freep(&ofmt_ctx->streams[i]->codec);
        av_freep(&ofmt_ctx->streams[i]);
    }

    printf("Finish!\n");
    return 0;
}