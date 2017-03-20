#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Image.h"


/* Get the color intensity of the Red channel of pixel (x, y) in image */
unsigned char GetPixelR(IMAGE *image, unsigned int x,  unsigned int y){
         assert(image);
         assert(image->R);
         assert(0 <= x && x <= image->Width && 0 <= y && y <= image->Height); 
         unsigned char temp = image->R[(x+ y*image->Width)];
         return temp;
}

/* Get the color intensity of the Green channel of pixel (x, y) in image */
unsigned char GetPixelG(IMAGE *image, unsigned int x,  unsigned int y){
         assert(image);
         assert(image->G);
         assert(0 <= x && x <= image->Width && 0 <= y && y <= image->Height); 
         unsigned char temp = image->G[(x+ y*image->Width)];
         return temp;

}


/* Get the color intensity of the Blue channel of pixel (x, y) in image */
unsigned char GetPixelB(IMAGE *image, unsigned int x,  unsigned int y){

         assert(image);
         assert(image->B);
         assert(0 <= x && x <= image->Width && 0 <= y && y <= image->Height);
         unsigned char temp = image->B[(x+ y*image->Width)];
         return temp;

}

/* Set the color intensity of the Red channel of pixel (x, y) in image with value r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r){

         assert(image);
         assert(image->R);
         assert(0 <= x && x <= image->Width && 0 <= y && y <= image->Height); 
         image->R[(x+ y*image->Width)] = r;

}

/* Set the color intensity of the Green channel of pixel (x, y) in image with value g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g){

         assert(image);
         assert(image->G);
         assert(0 <= x && x <= image->Width && 0 <= y && y <= image->Height);
         image->G[(x+ y*image->Width)] = g;
}

/* Set the color intensity of the Blue channel of pixel (x, y) in image with value b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b){

         assert(image);
         assert(image->B);
         assert(0 <= x && x <= image->Width && 0 <= y && y <= image->Height); 
         image->B[(x+ y*image->Width)] = b;
}


/* allocate the memory space for the image structure         */
/* and the memory spaces for the color intensity values.     */
/* return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height){
      
      IMAGE *image = (IMAGE *)malloc(sizeof(IMAGE));
      image->Width = Width;
      image->Height = Height;
      
      image->R = (unsigned char*)malloc(sizeof(unsigned char) * (Width * Height));
      image->G = (unsigned char*)malloc(sizeof(unsigned char) * (Width * Height));
      image->B = (unsigned char*)malloc(sizeof(unsigned char) * (Width * Height));
      
      int i, j;
      for (i = 0; i < Width; i++){
          for (j = 0; j < Height; j++) {
              image->R[(i+ j*image->Width)] = 0;
              image->G[(i+ j*image->Width)] = 0;
              image->B[(i+ j*image->Width)] = 0;
          }
      }
      
      if (image->R && image->G && image->B){
         return image;
      }
      else
          return NULL;
          
      
}


/* release the memory spaces for the pixel color intensity values */
/* deallocate all the memory spaces for the image                 */
void DeleteImage(IMAGE *image){
     assert(image);
     free(image->R);
     image->R = NULL;
     free(image->G);
     image->G = NULL;
     free(image->B); 
     image->B = NULL;
     free(image);
     image = NULL;
     
}
