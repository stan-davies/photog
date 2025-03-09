#include <stdio.h>
#include "util/ppmio.h"
#include "translate/translate.h"

#define MAX_PATH_LEN 32

int main(int argc, char **argv) {
        struct img image;

        printf("get going!\n");
        
        if (!read_img("a.ppm", &image)) {
                printf("Could not read.\n");
        }

        printf("read...\n");

        translate_process(&image);

        printf("translating\n");
        
        if (!write_img("o.ppm", image)) {
                printf("Could not write.\n");
        }

        printf("written\n");

        return 0;
}
