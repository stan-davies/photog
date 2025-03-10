#include "reshape.h"

void reshape_process(struct img *i) {
        struct square *shapes = calloc(MAX_SQ, sizeof(struct square));
        int s = 0;

        for (int m = 0; m < SAMPLES; ++m) {
                make_squares(*i, &shapes, &s);
        }
        
        printf("s %d\n", s);
        int x;
        int y;
        for (int p = 0; p < i->w * i->h; ++p) {
                struct square lrg; 
                lrg.r = 10000000;
                lrg.col.r = -1.f;
                for (int j = 0; j < s; ++j) {
                        x = p % i->w;
                        y = p / i->w;
                        if (coll(shapes[j], x, y) && shapes[j].r < lrg.r) {
                                lrg = shapes[j];
                        }
                }

                if (lrg.col.r < 0.f) {
                        continue;
                }

                i->data[p] = lrg.col;
        }
}

void make_squares(struct img i, struct square **shapes, int *s) {
        int          p   = 0;
        int          r   = 0;
        float        sat = 0.f;
        float        lum = 0.f;
        int          esc;
        int          rds;
        struct pixel col;
        struct square sq;

        srand(time(NULL));
        
        while (p < i.w * i.h && *s < MAX_SQ) {
                r += rand() % (50 - 20 + 1) + 20;
                p  = i.w * r + (rand() % (1000 - 20 + 1) + 20);
//                p = i.w * r + (rand() % (4 - 1 + 1) + 1) * 200;

                col = i.data[p];
                sat = saturation(col);
                lum = luminosity(col);
                if (sat > MIN_SAT) {
                        rds = rad(sat);
                } else if (lum > MIN_LUM) {
                        rds = rad(lum);
                } else {
                        continue;
                }

                sq.x = p % i.w;
                sq.y = p / i.w;
                sq.r = rds;
                sq.col = saturate(col);
                esc = FALSE;
                for (int q = 0; q < *s; ++q) {
                        if (overlap((*shapes)[q], sq)) {
                                esc = TRUE;
                                break;
                        }
                }
                if (!esc) {
                        (*shapes)[*s] = sq;
                        (*s)++;
                }
        }
}

int coll(struct square sq, int x, int y) {
        if (x < sq.x - sq.r || x > sq.x + sq.r) {
                return FALSE;
        }
        if (y < sq.y - sq.r || y > sq.y + sq.r) {
                return FALSE;
        }
        return TRUE;
}

int overlap(struct square s1, struct square s2) {
        int r = 2 * s1.r ? s1.r > s2.r : 2 * s2.r;
        if (abs(s1.x - s2.x) < r && abs(s1.y - s2.y) < r) {
                return TRUE;
        }
        return FALSE;
}

int rad(float sat) {
//        return powf(2.f, 0.07f * (100.f * sat)) + 30.f;
//        return powf(2.f, 0.08f * (100.f * sat)) + 5.f;
        return (powf(2.f * sat - 0.2f, 3.f) + 1.f) * 20.f;
}

struct pixel saturate(struct pixel px) {
        float h = hue(px);
        float s = saturation(px);
        float l = luminosity(px); 
        s *= 1.5f;
        if (s > 1.f) {
                s = 1.f;
        }
        return HSLtoRGB(h, s, l);
}
