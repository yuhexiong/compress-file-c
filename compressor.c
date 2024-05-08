#include "compressor.h"

int compress_file(const char *source, const char *dest) {
    FILE *src_file = fopen(source, "rb");
    if (!src_file) {
        fprintf(stderr, "Error: Cannot open source file %s\n", source);
        return -1;
    }

    FILE *dest_file = fopen(dest, "wb");
    if (!dest_file) {
        fclose(src_file);
        fprintf(stderr, "Error: Cannot create destination file %s\n", dest);
        return -1;
    }

    int ret;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    // Initialize zlib stream
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        fclose(src_file);
        fclose(dest_file);
        fprintf(stderr, "\033[1;31mError: deflateInit failed\033[0m\n");
        return ret;
    }

    // compress the file
    do {
        strm.avail_in = fread(in, 1, CHUNK, src_file);
        if (ferror(src_file)) {
            deflateEnd(&strm);
            fclose(src_file);
            fclose(dest_file);
            fprintf(stderr, "\033[1;31mError: Reading source file\033[0m\n");
            return -1;
        }
        strm.next_in = in;

        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, Z_FINISH);
            if (ret == Z_STREAM_ERROR) {
                deflateEnd(&strm);
                fclose(src_file);
                fclose(dest_file);
                fprintf(stderr, "\033[1;31mError: deflate error\033[0m\n");
                return -1;
            }
            fwrite(out, 1, CHUNK - strm.avail_out, dest_file);
        } while (strm.avail_out == 0);
    } while (ret != Z_STREAM_END);

    // clean up
    deflateEnd(&strm);
    fclose(src_file);
    fclose(dest_file);

    return 0;
}
