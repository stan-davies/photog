#include "imgform.h"

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
        if (col.r < *min) {
                *min = col.r;
        }
        if (col.g < *min) {
                *min = col.g;
        }
        if (col.b < *min) {
                *min = col.b;
        }

        if (col.r > *max) {
                *max = col.r;
        }
        if (col.g > *max) {
                *max = col.g;
        }
        if (col.b > *max) {
                *max = col.b;
        }
}

float hue(struct pixel col) {
        struct normal_col norm = normalise(col);
        float term;
        float min;
        float max;
        minmax(norm, &min, &max);

        if (min == max) {
                return 0.f;
        }

        if (norm.r == max) {
                term = (norm.g - norm.b) / (max - min);
                if (term < 0.f) {
                        term = 6.f - fabs(term);
                }
        } else if (norm.g == max) {
                term = 2.f + ((norm.b - norm.r) / (max - min));
        } else if (norm.b == max) {
                term = 4.f + ((norm.r - norm.g) / (max - min));
        } 

        return term * 60.f;
}

float saturation(struct pixel col) {
        struct normal_col norm = normalise(col);
        float min;
        float max;

        minmax(norm, &min, &max);

        if (0.f == max) {
                return 0.f;
        }

        return (max - min) / max;
}

float luminosity(struct pixel col) {
        struct normal_col norm = normalise(col);
        float min;
        float max;

        minmax(norm, &min, &max);

        return max;
}

struct pixel HSLtoRGB(float h, float s, float l) {
        float c = l * s;
        float k = h / 60;
        float r = k - (2.f * ((int)k / 2));
        float x = c * (1.f - fabs(r - 1.f));
        float m = l - c;

        struct normal_col npx;

        if (0.f <= h && h < 60.f) {
                npx.r = c;
                npx.g = x;
                npx.b = 0.f;
        } else if (60.f <= h && h < 120.f) {
                npx.r = x;
                npx.g = c;
                npx.b = 0.f;
        } else if (120.f <= h && h < 180.f) {
                npx.r = 0.f;
                npx.g = c;
                npx.b = x;
        } else if (180.f <= h && h < 240.f) {
                npx.r = 0.f;
                npx.g = x;
                npx.b = c;
        } else if (240.f <= h && h < 300.f) {
                npx.r = x;
                npx.g = 0.f;
                npx.b = c;
        } else if (300.f <= h && h < 360.f) {
                npx.r = c;
                npx.g = 0.f;
                npx.b = x;
        }

        struct pixel px;
        px.r = (npx.r + m) * 255;
        px.g = (npx.g + m) * 255;
        px.b = (npx.b + m) * 255;
        return px;
}

/*
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


        struct normal_col norm;

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
*/
