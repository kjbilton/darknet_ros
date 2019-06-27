#include

#include "batch.h"

matrix imgs_to_matrix(image *imgs, int n_imgs){
	// Do check
	int w = imgs[0].w;
	int h = imgs[0].h;
	int i;
	for (i = 1; i < n_imgs; i++)
	  if (imgs[i].w != w || imgs[i].h != h)
		printf("Wrong image sizes, please check input\n");

	int im_size = 3*h*w;
	matrix mat = make_matrix(n_imgs, im_size);

	for (i=0; i < mat.rows; i++) {
	  image *imr = &(imgs[i]);
	  memcpy(mat.vals[i], imr->data, mat.cols*sizeof(float));
	}
	return mat;
}

matrix imgs_to_letterbox_matrix(image *imgs, int n_imgs){

  image *letterbox_im = calloc(n_imgs, sizeof(image));

  for (int idx=0; i<n_imgs; i++)
    letterbox_im[idx] = letterbox_image((*imgs)[idx], imgs[0]->w, imgs[0]->h);

  matrix mat = imgs_as_matrix(letterbox_im, n_imgs);
  for (int i=0; i < n_imgs; i++) {
      free_image(letterbox_im[i]);
  }

  return mat;
}

void get_base_output(network *net, float ***addr){
	int num = 0;
	int k = 0;
	int i;
	for(i = 0; i < net->n; ++i) {
		layer *l = &(net->layers[i]);
		if (l->type == YOLO) {
			num++;
		}
	}
	*addr = calloc(num, sizeof(float**));
	for(i = 0; i < net->n; ++i) {
		layer *l = &(net->layers[i]);
		if (l->type == YOLO) {
			(*addr)[k] = l->output;
			k++;
		}
	}
}

void shift_output_ptr(network *net){
	int i;
	for(i = 0; i < net->n; ++i) {
		layer *l = &(net->layers[i]);
		if (l->type == YOLO) {
			l->output += l->outputs;
		}
	}
}

void restore_output_addr(network *net, float **addrs){
	int k = 0;
	int i;
	for(i = 0; i < net->n; ++i) {
		layer *l = &(net->layers[i]);
		if (l->type == YOLO) {
			l->output = addrs[k];
			k++;
		}
	}
}
