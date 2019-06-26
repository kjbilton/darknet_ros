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
  return mat;
}
