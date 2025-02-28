#include "util/imgform.h"

struct normal_col normalise(struct pixel col) {
        struct normal_col norm;
        norm.r = col.r / 255.f;
        norm.g = col.g / 255.f;
        norm.b = col.b / 255.f;
        return norm;
};

void minmax(struct normal_col col, float *min, float *max) {
        *min = 1.f;
        *max = 0.f;
        for (int i = 0; i < 3; ++i) {
                if ((&col)[i] < *min) {
                        *min = (&col)[i];
                }
                if ((&col)[i] > *max) {
                        *max = (&col)[i]; 
                }
        }
}



float hue(struct pixel col) {
        struct normal_col norm = normalise(col);
        float term;
        float min;
        float max;
        minmax(norm, min, max);

        if (min == max) {
                return 0.f;
        }

        if (norm.r > norm.g && norm.r > norm.b) {
                term = (norm.g - norm.b) / (max - min);
        } else if (norm.g > norm.r && norm.b) {
                term = 2.f + ((norm.b - norm.r) / (max - min));
        } else if {
                term = 4.f + ((norm.r - norm.g) / (max - min)):
        } 

        return term;
}

float saturation(struct pixel col) {
        struct normal_col norm = normalise(col);
        float min;
        float max;

        minmax(norm, min, max);

        if (0.f == max) {
                return 0.f;
        }

        if (max - min < 0.5f) {
                return (max - min) / (max + min);
        } else {
                return (max - min) / (2 - max - min);
        }
}

float luminosity(struct pixel col) {
        struct normal_col norm = normalise(col);
        float min;
        float max;

        minmax(norm, min, max);

        return max - min;
}

struct pixel HSLtoRGB(float h, float s, float l) {
        struct pixel px;
        
        if (0.f == s) {
                px.r = l * 255;
                px.g = l * 255;
                px.b = l * 255;
                return px;
        }

        float c = (1.f - fabs(2.f * l - 1.f)) * s;
        float x = c * (1.f - (float)abs((int)h % 2 - 1));


        struct norm_col norm;

        if (0.f <= h < 1.f) {
                norm.r = c;
                norm.g = x;
                norm.b = 0.f;
        } else if (1.f <= h < 2.f) {
                norm.r = x;
                norm.g = c;
                norm.b = 0.f;
        } else if (2.f <= h < 3.f) {
                norm.r = 0.f;
                norm.g = c;
                norm.b = x;
        } else if (3.f <= h < 4.f) {
                norm.r = 0.0;
                norm.g = x;
                norm.b = c;
        } else if (4.f <= h < 5.f) {
                norm.r = x;
                norm.g = 0.f;
                norm.b = c;
        } else if (5.f <= h < 6.f) {
                norm.r = c;
                norm.g = 0.f;
                norm.b = x;
        } else {
                norm.r = -10.f;
                norm.g = -10.f;
                norm.b = -10.f;
        }

        float m = l - (c / 2.f);
        norm.r += m;
        norm.g += m;
        norm.b += m;

        px.r = 255 * norm.r;
        px.g = 255 * norm.g;
        px.b = 255 * norm.b;

        return px;
}
