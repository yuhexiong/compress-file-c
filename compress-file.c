#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compressor.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("\033[1;31mError: Incorrect number of arguments. Usage: %s <source file> <destination file>\033[0m\n", argv[0]);
        return 1;
    }

    const char *source = argv[1];
    const char *dest = argv[2];

    int ret = compress_file(source, dest);
    if (ret == 0) {
        printf("\033[1;32mFile compressed successfully.\033[0m\n");
    } else {
        printf("\033[1;31mError compressing file.\033[0m\n");
    }

    return ret;
}
