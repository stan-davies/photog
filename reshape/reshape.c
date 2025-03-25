#include "reshape.h"

void reshape_process(struct img *i) {
        struct rect whole = { 0, 0, i->w, i->h };
        srand(time(NULL));
        quadrise(i, whole);
}

void quadrise(struct img *i, struct rect parent) {
        struct rect child;
        int hdiv;
        int vdiv;
        int s = select_div(parent.w, parent.h, &vdiv, &hdiv);
        struct pixel col;
        if (0 == s) {
                return;
        } else if (s < 0) {
                col = pick_sat(*i, child);
                clear_quad(i, child, col);
                return;
        }

        int d = log2f((float)i->h) - log2f((float)parent.h);

        for (int q = 0; q < 4; ++q) {
                if (q % 2 == 0) {
                        child.w = hdiv;
                        child.x = parent.x;
                } else {
                        child.w = parent.w - hdiv;
                        child.x = parent.x + hdiv;
                }
                if (q / 2 == 0) {
                        child.h = vdiv;
                        child.y = parent.y;
                } else {
                        child.h = parent.h - vdiv;
                        child.y = parent.y + vdiv;
                }
                if (rand() % 100 + 1 > (int)powf(d, 1.7) + 15) {
                        quadrise(i, child);
                } else {
                        col = pick_sat(*i, child);
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
                p = reg_to_img(i, region, o);
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
        return r.y * i.w + r.x + ((p / r.w) * i.w) + (p % r.w);
}

int select_div(int pw, int ph, int *vdiv, int *hdiv) {
        int v;
        int h;
        float scl;
        int c = 0;
        do {
                v = ph / (rand() % (6 - 2 + 1) + 2);
                h = pw / (rand() % (6 - 2 + 1) + 2);
                scl = h / v;
                c++;
                if (c > 50) {
                        return -1;
                }
        } while (v < 1 || h < 1 || scl > MAX_RAT || scl < 1.f / MAX_RAT);
        *vdiv = v;
        *hdiv = h;
        return h > 1 && v > 1;
}
