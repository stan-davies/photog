#include "stretch.h"

void stretch_process(struct img *i) {
        struct pixel col;
        int proc;

        for (int r = 0; r < i->h; ++r) {
                proc = 0;
                col = i->data[r * i->w];
                for (int c = 0; c < i->w; ++c) {
                        proc++;
                        if (proc > rand() % (200 - 40 + 1) + 1) {
                                col = i->data[r * i->w + c];
                                proc = 0;
                        }

                        i->data[r * i->w + c] = col;
                }
        }
}
