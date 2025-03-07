#include "sort.h"

void sort_process(struct image *i) {
        struct px_ref *refs = calloc(i->w * i->h, sizeof(struct px_ref));

        struct px_ref curr;
        for (int p = 0; p < i->w * i->h; ++p) {
                curr.index = p;
                curr.lum = luminosity(i->data[p]);
                refs[p] = curr;
        }

        int p_max;
        int acc = 0;
        for (int r = 0; r < i->h; ++r) {
                p_max = rand() % 105 + 55; 
                if (i->w - acc < p) {
                        p_max = i->w - acc;
                }
                acc += p_max;

                struct px_refs *chunk = calloc(p_max, sizeof(struct px_ref)); 

                // sort

                for (int p = 0; p < p_max; ++p) {
                        refs[r * i->w + acc + p] = chunk[p];
                }
                free(chunk);
                chunk = NULL;
        }


        struct img new_i;
        new_i.w = i->w;
        new_i.h = i->h;
        new_i.data = calloc(new_i.w * new_i.h, sizeof(struct pixel));
        for (int p = 0; p < i->w * i->h; ++p) {
                new_i.data[p] = i->data[refs[p].index];
        }

        *i = new_i;
}
