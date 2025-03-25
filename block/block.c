#include "block.h"

void block_process(struct img *i) {
        struct pixel highlight = { 255, 0, 0 };
        float lum;

        for (int p = 0; p < i->w * i->h; ++p) {
                lum = luminosity(i->data[p]);
                if (lum > THRESHOLD) {
                        i->data[p] = highlight;
                }
        }
}
