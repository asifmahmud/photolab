#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "DIPs.h"
#include "Constants.h"
#include "Image.h"

int Range(int value, int from, int to){
	if (value < from || value > to)
		return 0;

	else
		return 1;

}

int in(int array[16], int value){
	int i;

	for (i = 0; i < 16; i++){
		if (array[i] == value)
			return 1;
	}
	return 0;
}

void append(int array[16], int value_1, int value_2){

	int i;
	for (i = 0; i < 16; i++){
		if (array[i] == 99)
			array[i] = value_1;
		array[i + 1] = value_2;
		break;
	}

}



IMAGE *BlackNWhite(IMAGE *image){
	int i, j = 0;

	for (i = 0; i < image->Width; i++){
		for (j = 0; j < image->Height; j++){
			int mod_value = (GetPixelR(image, i, j) + GetPixelG(image, i, j) + GetPixelB(image, i, j)) / 3;
			SetPixelR(image, i, j, mod_value);
			SetPixelG(image, i, j, mod_value);
			SetPixelB(image, i, j, mod_value);
		}
	}
	return image;

}


IMAGE *VFlip(IMAGE *image){
	unsigned int i, j;
	unsigned int r_temp, b_temp, g_temp;
  
	for (i = 0; i < (image->Width); i++){
		for (j = 0; j < (image->Height) / 2; j++){
			r_temp = GetPixelR(image, i, image->Height - 1 - j);
			g_temp = GetPixelG(image, i, image->Height - 1 - j);
			b_temp = GetPixelB(image, i, image->Height - 1 - j);
			
			SetPixelR(image, i, image->Height - 1 - j, GetPixelR(image, i, j));
			SetPixelG(image, i, image->Height - 1 - j, GetPixelG(image, i, j));
			SetPixelB(image, i, image->Height - 1 - j, GetPixelB(image, i, j));
			
			SetPixelR(image, i, j, r_temp);
			SetPixelG(image, i, j, g_temp);
			SetPixelB(image, i, j, b_temp);
		}
	}
  
	return image;
}


IMAGE *HMirror(IMAGE *image){
	int i, j;
	for (i = 0; i < (image->Width / 2); i++){
		for (j = 0; j < image->Height; j++){
			SetPixelR(image, i, j, GetPixelR(image, image->Width - 1 - i, j));
			SetPixelG(image, i, j, GetPixelG(image, image->Width - 1 - i, j));
			SetPixelB(image, i, j, GetPixelB(image, image->Width - 1 - i, j));
		}
	}
	return image;

}

IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b,
				   int threshold, int replace_r, int replace_g, int replace_b){

	int i, j;
	for (i = 0; i < image->Width; i++){
		for (j = 0; j < image->Height; j++){
			if (Range(GetPixelR(image, i, j), target_r - threshold, target_r + threshold) &&
				Range(GetPixelG(image, i, j), target_g - threshold, target_g + threshold) &&
				Range(GetPixelB(image, i, j), target_b - threshold, target_b + threshold)) {

				SetPixelR(image, i, j, replace_r);
				SetPixelG(image, i, j, replace_g);
				SetPixelB(image, i, j, replace_b);

			}
		}
	}
	return image;
}



IMAGE *Edge(IMAGE *image) {
	int i, j = 0;
	unsigned char *temp_r = (unsigned char*)malloc(sizeof(unsigned char) * (image->Width * image->Height));
	unsigned char *temp_g = (unsigned char*)malloc(sizeof(unsigned char) * (image->Width * image->Height));
	unsigned char *temp_b = (unsigned char*)malloc(sizeof(unsigned char) * (image->Width * image->Height));

	/* Creating temporary image */

	for (i = 0; i < image->Width; i++){
		for (j = 0; j < image->Height; j++){
			*(temp_r + (i + j * image->Width)) = GetPixelR(image, i, j);      
			*(temp_g + (i + j * image->Width)) = GetPixelG(image, i, j);
			*(temp_b + (i + j * image->Width)) = GetPixelB(image, i, j);
		}
	}


	for (i = 1; i < image->Width - 1; i++){
		for (j = 1; j < image->Height - 1; j++){
			int r_sum = GetPixelR(image, i, j+1) +
				GetPixelR(image, i, j-1) +
				GetPixelR(image, i+1, j) +
				GetPixelR(image, i-1, j) +
				GetPixelR(image, i+1, j-1) +
				GetPixelR(image, i+1, j+1) +
				GetPixelR(image, i-1, j+1) +
				GetPixelR(image, i-1, j-1);

			int g_sum = GetPixelG(image, i, j+1) +
				GetPixelG(image, i, j-1) +
				GetPixelG(image, i+1, j) +
				GetPixelG(image, i-1, j) +
				GetPixelG(image, i+1, j-1) +
				GetPixelG(image, i+1, j+1) +
				GetPixelG(image, i-1, j+1) +
				GetPixelG(image, i-1, j-1);

			int b_sum = GetPixelB(image, i, j+1) +
				GetPixelB(image, i, j-1) +
				GetPixelB(image, i+1, j) +
				GetPixelB(image, i-1, j) +
				GetPixelB(image, i+1, j-1) +
				GetPixelB(image, i+1, j+1) +
				GetPixelB(image, i-1, j+1) +
				GetPixelB(image, i-1, j-1);

			int replace_r = 8 * GetPixelR(image, i, j) - (r_sum);
			int replace_g = 8 * GetPixelG(image, i, j) - (g_sum);
			int replace_b = 8 * GetPixelB(image, i, j) - (b_sum);

			if (replace_r < 0)
				replace_r = 0;
			else if (replace_r > 255)
				replace_r = 255;

			if (replace_g < 0)
				replace_g = 0;
			else if (replace_g > 255)
				replace_g = 255;

			if (replace_b < 0)
				replace_b = 0;
			else if (replace_b > 255)
				replace_b = 255;

			*(temp_r + (i + j * image->Width)) = replace_r;
			*(temp_g + (i + j * image->Width)) = replace_g;
			*(temp_b + (i + j * image->Width)) = replace_b;

		}
	}

	for (i = 1; i < image->Width - 1; i++){
		for (j = 1; j < image->Height - 1; j++){
			SetPixelR(image, i, j, *(temp_r + (i + j * image->Width)));
			SetPixelG(image, i, j, *(temp_g + (i + j * image->Width)));
			SetPixelB(image, i, j, *(temp_b + (i + j * image->Width)));

		}

	}
	free(temp_r);
	temp_r = NULL;
	free(temp_g);
	temp_g = NULL;
	free(temp_b);
	temp_b = NULL;
	return image;
}



/*Shuffle the image*/
IMAGE *Shuffle(IMAGE *image)
{
	int block_cnt    = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
	int block_width  = image->Width/SHUFF_WIDTH_DIV;
	int block_height = image->Height/SHUFF_HEIGHT_DIV;
	int *block       = (int*)malloc(sizeof(int) * (SHUFF_WIDTH_DIV * SHUFF_HEIGHT_DIV));
	int i, j;
	

	srand(time(NULL));
	/* Initialize block markers to not done (-1) */
	for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
		for (j = 0; j < SHUFF_HEIGHT_DIV; j++) {
			*(block + (i + (j*SHUFF_WIDTH_DIV))) = -1;
		}
	}

	while (block_cnt > 0) {
		/* Generate a random pair of blocks */
		int dest_height = rand() % SHUFF_HEIGHT_DIV;
		int dest_width  = rand() % SHUFF_WIDTH_DIV;
		int src_height  = rand() % SHUFF_HEIGHT_DIV;
		int src_width   = rand() % SHUFF_WIDTH_DIV;

		/* Check if these blocks are already swaped, if not swap blocks */
		if ((*(block + (dest_width + (dest_height*SHUFF_WIDTH_DIV))) == -1) && (*(block + (src_width + (src_height*    SHUFF_WIDTH_DIV))) == -1)) {
			/* Swap blocks */
			for (i = 0; i < block_height; i++) {
				/* Init src and dest height offset */
				int h_dest = ((dest_height * block_height) + i) % image->Height;
				int h_src  = ((src_height * block_height) + i) % image->Height; 
				
				or (j = 0; j < block_width; j++) {
					int temp;
					/* Init src and dest width offset */
					int w_src  = ((src_width * block_width) + j) % image->Width; 
					int w_dest = ((dest_width * block_width) + j) % image->Width;

					temp = GetPixelR(image, w_dest, h_dest);
					SetPixelR(image, w_dest, h_dest, GetPixelR(image, w_src, h_src));
					SetPixelR(image, w_src, h_src, temp);
				  
					temp = GetPixelG(image, w_dest, h_dest);
					SetPixelG(image, w_dest, h_dest, GetPixelG(image, w_src, h_src));
					SetPixelG(image, w_src, h_src, temp);
				  
					temp = GetPixelB(image, w_dest, h_dest);
					SetPixelB(image, w_dest, h_dest, GetPixelB(image, w_src, h_src));
					SetPixelB(image, w_src, h_src, temp);

				}
			}
			/* Set marker as done */
			*(block + (dest_width + (dest_height*SHUFF_WIDTH_DIV))) = 1;
			*(block + (src_width + (src_height*SHUFF_WIDTH_DIV))) = 1;
			/* Decrease block count */
			block_cnt -= 2; /* Two blocks are swapped */
		}
		
	}
	free(block);
	block = NULL;
	return image;

}
