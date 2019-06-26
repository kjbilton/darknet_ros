#ifndef BATCH_H
#define BATCH_H

#include "image.h"
#include "matrix.h"

matrix imgs_to_matrix(image *imgs, int n_images)
matrix imgs_to_letterbox_matrix(image *img);


#endif
