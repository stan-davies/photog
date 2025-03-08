#include "translate.h"

void translate_process(struct img *i) {
        float old_hue;
        float old_sat;
        float old_lum;
        float new_hue;
        float new_sat;
        float new_lum;
        for (int p = 0; p < i->w * i->h; ++p) {
                old_hue = hue(i->data[p]);
                new_hue = transform_hue(old_hue);
                old_sat = saturation(i->data[p]);
                new_lum = old_sat;
                old_lum = luminosity(i->data[p]);
                new_sat = old_lum;
                i->data[p] = HSLtoRGB(new_hue, new_sat, new_lum);
        }
}

float transform_hue(float h) {
        float x = 2.4337f * h - 0.7f;
        float f = -1.f * powf(x, 5.f); 
        f      +=  2.f * powf(x, 4.f);
        f      += 0.5f * powf(x, 3.f);
        f      += -2.f * powf(x, 2.f);
        return f + 1.f;
}

