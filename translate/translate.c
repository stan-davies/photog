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
                new_sat = old_sat;
                old_lum = luminosity(i->data[p]);
                new_lum = old_lum;
                i->data[p] = HSLtoRGB(new_hue, new_sat, new_lum);
        }
}

float transform_hue(float h) {
        /*
        float x = h / 360.f;
        if (x < 0.3f) {
                return 1.f - expf(2.f * x - 0.6f);
        } else if (x > 0.7f) {
                return 0.5f + expf(-2.f * x + 0.7f);
        } else {
                return powf(4.f * x - 2.f, 3.f) + 0.5f;
        }
        */
        /*
        if (h / 360.f > 2.f / 3.f) {
                return -0.1f * sinhf(2.f * h) + 0.39f;
        }
        float x = 2.4337f * (1.6f * (h / 360.f)) - 0.7f;
        float f = -1.f * powf(x, 5.f); 
        f      +=  2.f * powf(x, 4.f);
        f      += 0.5f * powf(x, 3.f);
        f      += -2.f * powf(x, 2.f);
        f      -= sinf(2.4337f * 1.6f * h);
        f      *= -0.8f;
        f      -= 0.3f;
        return 1.05f - 0.5f * f + powf(h, 6.f);
        */
        return h;
}
