#include "ppmio.h"

int read_img(char *path, struct img *read) {
        FILE *f = fopen(path, "r");
        if (!f) {
                return FALSE;
        }

        size_t        f_len = 0;
        char         *ln    = NULL;
        ssize_t       ln_len;
        struct pixel *px;
        int           p     = -1;
        int           dimf  = FALSE;

        while ((ln_len = getline(&ln, &f_len, f)) != -1) {
                ++p;
                if (DIM_LNN == p) {
                        sscanf(ln, "%d %d", &(read->w), &(read->h));
                        read->data = calloc(read->w * read->h, sizeof(struct pixel));
                        dimf = TRUE;
                } else if (p < DAT_BEG) {
                        continue;
                } else if (p - DAT_BEG > read->w * read->h) {
                        break;
                } else if (dimf) {
                        px = &(read->data[p - DAT_BEG]);
                        sscanf(ln, "%d %d %d", &(px->r), &(px->g), &(px->b));
                } else {
                        printf("problem\n");
                }
        }

        fclose(f);
        free(ln);
        return TRUE;
}

int write_img(char *path, struct img write) {
        FILE *f = fopen(path, "w");

        if (!f) {
                return FALSE;
        }

        fprintf(f, "P3\n%d %d\n255\n", write.w, write.h);
        
        struct pixel px;
        for (int p = 0; p < write.w * write.h; ++p) {
                px = write.data[p];
                fprintf(f, "%d %d %d\n", px.r, px.g, px.b);
        }

        fclose(f);
        return TRUE;
}


