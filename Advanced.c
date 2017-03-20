#include <stdio.h>
#include <time.h>
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"

unsigned char pow(unsigned char a, unsigned char b){
	unsigned char i;
	unsigned char temp = 1;
	for (i = 0; i < b; i++){
		temp *= a;
	}
	return temp;
}



IMAGE *Posterize( IMAGE *image, unsigned int pbits){
	int i, j;
	for (i = 0; i < image->Width; i++){
		for (j = 0; j < image->Height; j++){
			char temp = pow(2, pbits - 1) - 1;
			
      SetPixelR(image, i, j, GetPixelR(image, i, j) & ~(1 << pbits - 1));
      SetPixelR(image, i, j, GetPixelR(image, i, j) | temp);
			
      SetPixelG(image, i, j, GetPixelG(image, i, j) & ~(1 << pbits - 1));
      SetPixelG(image, i, j, GetPixelG(image, i, j) | temp);
			
      SetPixelB(image, i, j, GetPixelB(image, i, j) & ~(1 << pbits - 1));
      SetPixelB(image, i, j, GetPixelB(image, i, j) | temp);
		}
	}
 return image;
}
 
/* add noise to image */
IMAGE *FillLight( IMAGE *image, int number, int lightWidth)
{
    int x, y, i, h;
    int colorChoice;	
    
    int WIDTH = image->Width;
    int HEIGHT = image->Height;
    
    srand( 0 );

    for ( i = 0; i < number; i++ )
    {
        x = ( rand()%(WIDTH-lightWidth)) + lightWidth/2;
        y = ( rand()%(HEIGHT-lightWidth))+ lightWidth/2;
        
	colorChoice = (rand()%3)+1;

	int red_flag, blue_flag, green_flag;
	red_flag = blue_flag = green_flag = 0;
	if(colorChoice == 1)
		red_flag = 1;
	else if(colorChoice == 2)
		green_flag = 1;
	else 
		blue_flag = 1;
	
	for(h = -lightWidth/2; h < lightWidth/2; h++){
    SetPixelR(image, x+h, y, 255*red_flag);
    SetPixelR(image, x, y+h, 255*red_flag);
    SetPixelR(image, x+h, y+h, 255*red_flag);
    SetPixelR(image, x-h, y+h, 255*red_flag);
		
    SetPixelG(image, x+h, y, 255*green_flag);
    SetPixelG(image, x, y+h, 255*green_flag);
    SetPixelG(image, x+h, y+h, 255*green_flag);
    SetPixelG(image, x-h, y+h, 255*green_flag);

    SetPixelB(image, x+h, y, 255*blue_flag);
    SetPixelB(image, x, y+h, 255*blue_flag);
    SetPixelB(image, x+h, y+h, 255*blue_flag);
    SetPixelB(image, x-h, y+h, 255*blue_flag);
	}
 }
 return image;
}


/* Overlay with another image */
IMAGE *Overlay( char fname[SLEN],IMAGE *image,int x_offset,int y_offset){
	
	int i, j;
	unsigned char *temp_r = (unsigned char*)malloc(sizeof(unsigned char) * (image->Width * image->Height));
  unsigned char *temp_g = (unsigned char*)malloc(sizeof(unsigned char) * (image->Width * image->Height));
  unsigned char *temp_b = (unsigned char*)malloc(sizeof(unsigned char) * (image->Width * image->Height));		
	IMAGE *temp_image = ReadImage(fname);
  /*temp_r = temp_image->R;
  temp_g = temp_image->G;
  temp_b = temp_image->B; */
  
  for (i = 0; i < temp_image->Width; i++){
      for (j = 0; j < temp_image->Height; j++){
          temp_r[(i + j * temp_image->Width)] = GetPixelR(temp_image, i, j); 
          temp_g[(i + j * temp_image->Width)] = GetPixelG(temp_image, i, j); 
          temp_b[(i + j * temp_image->Width)] = GetPixelB(temp_image, i, j); 
      }
  }
	
	
	for (i = 0; i < temp_image->Width; i++){
		for (j = 0; j < temp_image->Height; j++){
			if (temp_r[(i + j * temp_image->Width)] < 250 && 
          temp_g[(i + j * temp_image->Width)] < 250 && 
          temp_b[(i + j * temp_image->Width)] < 250){
				if (i + x_offset < image->Width && j + y_offset < image->Height){
          SetPixelR(image, i + x_offset, j + y_offset, temp_r[(i + j * temp_image->Width)]);  
					SetPixelG(image, i + x_offset, j + y_offset, temp_g[(i + j * temp_image->Width)]);
					SetPixelB(image, i + x_offset, j + y_offset, temp_b[(i + j * temp_image->Width)]);
				}
		}
	
	}
 }
  free(temp_r);
  free(temp_g);
  free(temp_b);
  DeleteImage(temp_image);
	return image;
}


/* Resize */
IMAGE *Resize( unsigned int percentage, IMAGE *image){
      int i, j;
      if (percentage == 100)
         return image;
         
      else {
           double p_divide = percentage/100.00; 
           double new_width  = (image->Width) * (percentage/100.00);
           double new_height = (image->Height) * (percentage/100.00);
           IMAGE* new_image = CreateImage((int)new_width, (int)new_height);

           if (percentage > 100) {
              for (i = 0; i < new_image->Width; i++){
                  for (j = 0; j < new_image->Height; j++){
                      SetPixelR(new_image, i, j, GetPixelR(image, (100*i)/(percentage), (100*j)/(percentage)));
                      SetPixelG(new_image, i, j, GetPixelG(image, (100*i)/(percentage), (100*j)/(percentage)));
                      SetPixelB(new_image, i, j, GetPixelB(image, (100*i)/(percentage), (100*j)/(percentage)));
                  }
              }
           }
           else if (percentage < 100){
                int k, l;
                for (i = 0; i < new_image->Width; i++){
                    for (j = 0; j < new_image->Height; j++){
                        int sum_r = 0;
                        int sum_g = 0;
                        int sum_b = 0;
                        int x1 = (int) (i/p_divide);
                        int y1 = (int) (j/p_divide);
                        int x2 = (int) ((i+1)/p_divide);
                        int y2 = (int) ((j+1)/p_divide);
                        int to_divide = ((x2 - x1)) * ((y2 - y1));
                        
                        for (k = x1; k < x2; k++){
                            for (l  = y1; l < y2; l++){
                                sum_r += GetPixelR(image, k, l);
                                sum_g += GetPixelG(image, k, l); 
                                sum_b += GetPixelB(image, k, l); 
                            }
                        }
                        SetPixelR(new_image, i, j, sum_r/to_divide);
                        SetPixelG(new_image, i, j, sum_g/to_divide);
                        SetPixelB(new_image, i, j, sum_b/to_divide);
                    }
                }
           
           } 
                     
           DeleteImage(image);
           image = NULL;
           return new_image;
      }

}

/* Rotate */
IMAGE *Rotate(IMAGE *image){
      int i, j;
      unsigned int new_width = image->Height;
      unsigned int new_height = image->Width;
      IMAGE *new_image = CreateImage(new_width, new_height);
      for (i = 0; i < new_image->Width; i++) {
          for (j = 0; j < new_image->Height; j++) {
              SetPixelR(new_image, i, j, GetPixelR(image, j, image->Height-1-i)); 
              SetPixelG(new_image, i, j, GetPixelG(image, j, image->Height-1-i));
              SetPixelB(new_image, i, j, GetPixelB(image, j, image->Height-1-i)); 
          }
      }
       DeleteImage(image);
       image = NULL;
      return new_image;
}


/* Mandelbrot */
IMAGE *Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration){

      IMAGE *image = CreateImage(W, H);
      const unsigned char palette[MAX_COLOR][3] = {
      /* r g b*/
      { 0, 0, 0 }, /* 0, black */
      { 127, 0, 0 }, /* 1, brown */
      { 255, 0, 0 }, /* 2, red */
      { 255, 127, 0 }, /* 3, orange */
      { 255, 255, 0 }, /* 4, yellow */
      { 127, 255, 0 }, /* 5, light green */
      { 0, 255, 0 }, /* 6, green */
      { 0, 255, 127 }, /* 7, blue green */
      { 0, 255, 255 }, /* 8, turquoise */
      { 127, 255, 255 }, /* 9, light blue */
      { 255, 255, 255 }, /* 10, white */
      { 255, 127, 255 }, /* 11, pink */
      { 255, 0, 255 }, /* 12, light pink */
      { 127, 0, 255 }, /* 13, purple */
      { 0, 0, 255 }, /* 14, blue */
      { 0, 0, 127 } /* 15, dark blue */
      };

      int i, j;
      for (i = 0; i < W; i++){
          for (j = 0; j < H; j++){
              double x0 = (i - W/2.0)*4.0/W;
              double y0 = (j - H/2.0)*4.0/H;
                 
              double x = 0.0;
              double y = 0.0;
              
              int iteration = 0;
              
              while (((x*x + y*y) < 2*2) && (iteration < max_iteration)){
                    double xtemp = x*x - y*y + x0;
                    y = 2*x*y + y0;
                    x = xtemp;
                    iteration++;
              }
              
              int color = iteration % 16;
              
              SetPixelR(image, i, j, palette[color][0]);
              SetPixelG(image, i, j, palette[color][1]);
              SetPixelB(image, i, j, palette[color][2]);
          }
      }
      return image;

}












