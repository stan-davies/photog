#ifndef RESHAPE_H
#define RESHAPE_H

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "util/imgform.h"

#define MAX_SQ 500 
#define SAMPLES 10
#define TRUE   1
#define FALSE  0

#define MIN_SAT 0.2f
#define MIN_LUM 0.4f

struct square {
        int x;
        int y;
        int r;
        struct pixel col;
};

void reshape_process(struct img *i);

void make_squares(struct img i, struct square **shapes, int *s);

int coll(struct square sq, int x, int y);

int overlap(struct square s1, struct square s2);

int rad(float sat);

struct pixel saturate(struct pixel px);

#endif
