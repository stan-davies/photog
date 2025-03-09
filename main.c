#include <stdio.h>
#include "util/ppmio.h"
#include "translate/translate.h"

#define MAX_PATH_LEN 32

int main(int argc, char **argv) {
        /*
        struct pixel px = { 214, 157, 188 };
        float h = hue(px);
        float s = saturation(px);
        float l = luminosity(px);
        struct pixel new_px = HSLtoRGB(h, s, l);
        printf("hsl %.2f %.2f %.2f\n", h, s, l);
        printf("We got (%d, %d, %d)\n", new_px.r, new_px.g, new_px.b);
}
*/
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
