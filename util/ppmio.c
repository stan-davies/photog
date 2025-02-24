#include "ppmio.h"

int read_img(char *path, struct img *read) {
        FILE *f = fopen(path, "r");
        if (!f) {
                return FALSE;
        }

        size_t        f_len = 0;
        char         *ln    = NULL;
        ssize_t       ln_len;
        struct pixel  px;
        int           p     = 0;

        while ((ln_len = getline(&ln, &f_len, f)) != -1) {
                ++p;
                if (IMG_DIM == p) {
                        sscanf(ln, "%d %d", &read->w, &read->h);
                } else if (p < DAT_BEG) {
                        continue;
                } else if (p > read->w * read->h) {
                        break;
                }

                px = read->data[p];
                sscanf(ln, "%d %d %d", &px.r, &px.g, &px.b);
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
        for (int y = 0; y < write.h; ++y) {
                for (int x = 0; x < write.w; ++x) {
                        px = write.data[write.w * y + x]; 
                        fprintf(f, "%d %d %d\n", px.r, px.g, px.b);
                }
        }

        fclose(f);
        return TRUE;
}


