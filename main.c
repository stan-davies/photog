#include <stdio.h>
#include "util/ppmio.h"
#include "stretch/stretch.h"

#define MAX_PATH_LEN 32

int main(int argc, char **argv) {
        struct img image;

        printf("get going!\n");
        
        if (!read_img("r.ppm", &image)) {
                printf("Could not read.\n");
        }

        printf("read...\n");

        stretch_process(&image);

        printf("processed\n");
        
        if (!write_img("o.ppm", image)) {
                printf("Could not write.\n");
        }

        printf("written\n");

        return 0;
}
