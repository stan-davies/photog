#include "resize.h"

void resize_process(struct img *i) {
        struct rect whole = { 0, 0, i->w, i->h };
        quadrise(i, whole);
}

void quadrise(struct img *i, struct rect parent) {
        struct rect child;
        child.d = parent.d / 2;
        if (1 == child.d) {
                return;
        }

        struct pixel col;

        for (int q = 0; q < 4; ++q) {
                child.x = parent.x + ((q % 2) * (parent.d / 2));
                child.y = parent.y + ((q / 2) * (parent.d / 2));
                if (rand() % (100 - 50 + 1) + 50 > CUTOFF) {
                        quadrise(i, child);
                } else {
                        col = pick_sat(&i, child);
                        clear_quad(i, child, col);
                }
        }
}

struct pixel pick_sat(struct img i, struct rect region) {
        struct pixel col;
        float max_sat = 0.f;
        float cur_sat;
        int p;
        for (int o = 0; o < region.w * region.h; ++o) {
                p = reg_to_img(&i, region, o);
                cur_sat = saturation(i.data[p]);
                if (cur_sat > max_sat) {
                        max_sat = cur_sat;
                        col = i.data[p];
                }
        }
        return col;
}
                
void clear_quad(struct img *i, struct rect region, struct pixel col) {
        for (int o = 0; o < region.w * region.h; ++o) {
                i->data[reg_to_img(*i, region, o)] = col;
        }
}

int reg_to_img(struct img i, struct rect r, int p) {
        return r.y * i.w + r.x + ((p / r.d) * i.w) + (p % r.d);
}
