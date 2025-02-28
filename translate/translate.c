#include "translate.h"

void translate_process(struct img *i) {
        float old_hue;
        float old_sat;
        float old_lum;
        float new_hue;
        float new_sat;
        float new_lum;
        for (int p = 0; p < i->w * i->h; ++p) {
                old_hue = hue(img->data[p]);
                new_hue = transform_hue(old_hue);
                old_sat = saturation(img->data[p]);
                new_lum = old_sat;
                old_lum = luminosity(img->data[p]);
                new_sat = old_lum;
                img->data[p] = HSLtoRGB(new_hue, new_sat, new_lum);
        }
}

float transform_hue(float h) {

