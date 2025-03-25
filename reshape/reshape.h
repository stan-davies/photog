#ifndef RESIZE_H
#define RESIZE_H

#include <stdlib.h>
#include <time.h>
#include "util/imgform.h"

#define CUTOFF 30
#define MAX_RAT 3

struct rect {
        int x;
        int y;
        int w;
        int h;
};

void reshape_process(struct img *i);

void quadrise(struct img *i, struct rect parent);

struct pixel pick_sat(struct img i, struct rect region);

void clear_quad(struct img *i, struct rect region, struct pixel col);

int reg_to_img(struct img i, struct rect r, int p);

int select_div(int pw, int ph, int *vdiv, int *hdiv);

#endif
