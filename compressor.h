#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define CHUNK 16384

// Header file allows other source files to use the compress_file function

/*
    Parameters:
        source: Path to the source file to compress
        dest: Path to the destination file where the compressed data will be written
    Returns: if compression succeeds, -1 otherwise
*/
int compress_file(const char *source, const char *dest);

#endif
