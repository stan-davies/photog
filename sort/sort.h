#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include "util/imgform.h"

struct px_ref {
        int index;
        float lum;
};

void sort_process(struct img *i);

void sort_pixels(struct px_ref *chunk, int pxs);

#endif
