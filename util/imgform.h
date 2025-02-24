#ifndef IMGFORM_H
#define IMGFORM_H

#define IMG_DIM 1
#define DAT_BEG 3

struct pixel {
        int r;
        int g;
        int b;
};

struct img {
        int w;
        int h;
        struct pixel *data;
};

#endif
