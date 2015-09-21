import sys
import simple_ffmpeg

def main():
    infile = sys.argv[1]
    outfile = sys.argv[2]

    simple_ffmpeg.sff_register_all()

    source = simple_ffmpeg.open_source(infile, 1, 1)
    simple_ffmpeg.sff_dump_format(source, infile)

    output = simple_ffmpeg.open_output(outfile, None, None, None, 1, 1)
    simple_ffmpeg.sff_dump_format(output, outfile)

    tctx = simple_ffmpeg.build_transcoding_context(source, output)

    simple_ffmpeg.sff_write_header(output)

    simple_ffmpeg.sff_write_trailer(output)

if __name__ == "__main__":
    main()