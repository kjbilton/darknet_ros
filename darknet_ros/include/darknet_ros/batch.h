#ifndef BATCH_H
#define BATCH_H

#include "image.h"
#include "matrix.h"
#include "network.h"

matrix imgs_to_letterbox_matrix(image **imgs, int n_imgs, int w, int h);
matrix imgs_to_matrix(image *imgs, int n_imgs);

void shift_output_ptr(network *net);
void get_base_output(network *net, float ***addr);
void restore_output_addr(network *net, float **addrs);

#endif
