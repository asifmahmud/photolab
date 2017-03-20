#ifndef Advanced
#define Advanced
#include "Constants.h"
#include "Image.h"
#define MAX_COLOR 16


/* Posterize the image */
IMAGE *Posterize( IMAGE *image, unsigned int pbits);

/* Add noise to image */
IMAGE *FillLight( IMAGE *image, int number, int lightWidth);

/* Overlay with another image */
IMAGE *Overlay( char fname[SLEN],
IMAGE *image,
int x_offset,
int y_offset);

/* Resize */
IMAGE *Resize( unsigned int percentage, IMAGE *image);
/* Rotate */
IMAGE *Rotate(IMAGE *image);
/* Mandelbrot */
IMAGE *Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration);

#endif