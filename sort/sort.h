#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <stdio.h>
#include "util/imgform.h"

#define TRUE  1
#define FALSE 0

struct px_ref {
        int index;
        float lum;
};

void sort_process(struct img *i);

void sort_pixels(struct px_ref **chunk, int pxs);

#endif
