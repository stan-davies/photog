#include "sort.h"

void sort_process(struct img *i) {
        struct px_ref *refs = calloc(i->w * i->h, sizeof(struct px_ref));

        struct px_ref curr;
        printf("referise!\n");
        for (int p = 0; p < i->w * i->h; ++p) {
                printf("\r%d", p);
                curr.index = p;
                curr.lum = luminosity(i->data[p]);
                refs[p] = curr;
        }

        int p_max;
        printf("\nlets go!\n");
        for (int r = 0; r < i->h; ++r) {
                printf("\r%d", r);
                int acc = 0;
                int keep = TRUE;
                while (keep) {
                        p_max = rand() % (100 - 50 + 1) + 50; 
                        if (i->w - acc < p_max) {
                                printf("BREAK");
                                p_max = i->w - acc;
                                keep = FALSE;
                        }
                        acc += p_max;

                        struct px_ref *chunk = calloc(p_max, sizeof(struct px_ref)); 

                        for (int p = 0; p < p_max; ++p) {
                                chunk[p] = refs[r * i->w + acc + p];
                        }

                        sort_pixels(&chunk, p_max);

                        for (int p = 0; p < p_max; ++p) {
                                refs[r * i->w + acc + p] = chunk[p];
                        }
                
                        free(chunk);
                        chunk = NULL;
                }
        }
        printf("\n");


        struct img new_i;
        new_i.w = i->w;
        new_i.h = i->h;
        new_i.data = calloc(new_i.w * new_i.h, sizeof(struct pixel));
        for (int p = 0; p < i->w * i->h; ++p) {
                new_i.data[p] = i->data[refs[p].index];
        }

        *i = new_i;
}

void sort_pixels(struct px_ref **chunk, int pxs) {
        struct px_ref tmp;
        int swap_made;
        int beg = (*chunk)[0].index;
        do {
                swap_made = FALSE;
                for (int p = 0; p < pxs - 1; ++p) {
                        if ((*chunk)[p].lum > (*chunk)[p + 1].lum) {
                                tmp = (*chunk)[p];
                                (*chunk)[p] = (*chunk)[p + 1];
                                (*chunk)[p + 1] = tmp;
                                swap_made = TRUE;
                        }
                }
        } while (swap_made);

/*
        for (int p = 0; p < pxs; ++p) {
                (*chunk)[p].index = beg + pxs - p - 1;
        }
        */
}
