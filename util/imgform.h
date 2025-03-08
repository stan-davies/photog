#ifndef IMGFORM_H
#define IMGFORM_H

#include "math.h"
#include "stdlib.h"

#define DIM_LNN 1
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

struct normal_col {
        float r;
        float g;
        float b;
};

struct normal_col normalise(struct pixel col);

void minmax(struct normal_col col, float *min, float *max);

float hue(struct pixel col); 

float saturation(struct pixel col);

float luminosity(struct pixel col);

struct pixel HSLtoRGB(float h, float s, float l);

#endif
