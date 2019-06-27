#include "darknet_ros/batch.h"

matrix imgs_to_letterbox_matrix(image **imgs, int n_imgs, int w, int h){

  image *letterbox_im = calloc(n_imgs, sizeof(image));

  for (int i = 0; i<n_imgs; i++)
    letterbox_im[i] = letterbox_image((*imgs)[i], w, h);

  matrix mat = imgs_to_matrix(letterbox_im, n_imgs);
  for (int i=0; i < n_imgs; i++) {
    free_image(letterbox_im[i]);
  }

  return mat;
}

matrix imgs_to_matrix(image *imgs, int n_imgs){
	int im_size = 3 * imgs[0].w * imgs[0].h;
	matrix mat = make_matrix(n_imgs, im_size);

	for (int i = 0; i < mat.rows; i++) {
	  image *imr = &(imgs[i]);
	  memcpy(mat.vals[i], imr->data, mat.cols * sizeof(float));
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
