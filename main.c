#include <stdio.h>
#include "util/ppmio.h"
#include "reshape/reshape.h"

#define MAX_PATH_LEN 32

int main(int argc, char **argv) {
        struct img image;

        printf("get going!\n");
        
        if (!read_img("ds.ppm", &image)) {
                printf("Could not read.\n");
        }

        printf("read...\n");

        reshape_process(&image);
        /*
        for (int p = 0; p < image.w * image.h; ++p) {
                float s = saturation(image.data[p]);
                float l = luminosity(image.data[p]);
                int z = s * 255;
                image.data[p].r = z;
                image.data[p].g = z;
                image.data[p].b = z;
                if (s > 0.6f || l > 0.6f) {
                        image.data[p].g = 0;
                        image.data[p].b = 0;
                }
        }
        */

        printf("reshaped\n");
        
        if (!write_img("o.ppm", image)) {
                printf("Could not write.\n");
        }

        printf("written\n");

        return 0;
}
