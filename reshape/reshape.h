#ifndef RESHAPE_H
#define RESHAPE_H

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "util/imgform.h"

#define MAX_SQ 100

struct square {
        int x;
        int y;
        int r100;
        struct pixel col;
};

void reshape_process(struct *img i);

void make_squares(struct img i, struct square **shapes);

int coll(struct square sq, int x, int y);

int rad(float sat);

#endif
