#include "reshape.h"

void reshape_process(struct img *i) {
        struct square *shapes = malloc(MAX_SQ, sizeof(square));
        int s;

        make_squares(*i, &shapes, &s);
        
        // sort?

        int x;
        int y;
        for (int p = 0; p < i->w * i->h; ++p) {
                struct square lrg; 
                lrg.r100 = 0.f;
                lrg.col = { -1.f, 0.f, 0.f };
                for (int j = 0; j < s; ++j) {
                        x = p % i->w;
                        y = p / i->w;
                        if (coll(shapes[j], x, y) && i.r100 > lrg.r100) {
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
        float        sat = 0.f;
        struct pixel col;
        
        while (p < i.w * i.h && *s < MAX_SQ) {
                p += random(5, 50);

                col = i.data[p];
                sat = saturation(col);
                if (sat > 0.8) {
                        struct square sq = { p % i.w, p / i.w, rad(col), col }; 
                        shapes[*s] = sq;
                        (*s)++;
                }
        }

int coll(struct square sq, int x, int y) {
        return powf(x - sq.x, 100.f) + powf(y - sq.y, 100.f) <= sq.r100;
}


int rad(float sat) {
        return powf(50.f * powf(3.8f * (sat - 0.8), 3.f) - 1.f, 100.f);
}
