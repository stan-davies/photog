#include "util/ppmio.h"

#define MAX_PATH_LEN 32

int main(int argc, char **argv) {
        struct img image;
        image.w = 100;
        image.h = 100;
        
        char *path = calloc(MAX_PATH_LEN, sizeof(char));
        strcpy(path, "img.ppm");

        if (!read_img(path, &image)) {
                printf("Could not read.\n");
        }

        if (!write_img(path, image)) {
                printf("Could not write.\n");
        }

        free(path);

        return 0;
}
