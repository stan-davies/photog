#ifndef PPMIO_H
#define PPMIO_H

#include "imgform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE 0

int read_img(char *path, struct img *read);

int write_img(char *path, struct img write);

#endif
