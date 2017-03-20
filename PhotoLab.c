/* Asif Mahmud 70556749

/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2014       */
/*                                                                   */
/* History:                                                          */
/* 10/07/14 Manjunath MV  updated for EECS22 assignment2 Fall2014    */
/* 10/03/13 Che-Wei Chang  updated for EECS22 assignment2 Fall2013   */
/* 10/02/12 Weiwei Chen  updated for EECS22 assignment2 Fall2012     */
/* 09/27/11 Weiwei Chen  updated for EECS22 assignment2 Fall2011     */
/* 11/11/04 Rainer Doemer:   update for EECS 10 formatting style     */
/* 11/10/04 Rustam Sengupta: initial template version                */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "FileIO.h"
#include "Advanced.h"
#include "DIPs.h"
#include "Constants.h"
#include "Image.h"


/* change */

/*** function declarations ***/

/* print a menu */
void	PrintMenu();

/* Test all functions */
void	AutoTest(IMAGE *image);



int	main(){
	/*
	* Two dimensional arrays to hold the current image data. One array
	* for each color component
	* */

	/*  Please replace the following code with proper menu  */
	/*	with function calls for DIP operations		*/
 	int		FileNotRead ; 
	IMAGE 	*image;

	char	fname[SLEN];

	int		choice;

	int		target_r ; 
	int		target_g ; 
	int		target_b ;
	int		threshold ;
	
	double	factor_r ; 
	double	factor_g ; 
	double	factor_b ;
	
	int x_offset, y_offset;
	int number 		= 0;
	int lightWidth 	= 0;
	int p_bits 		= 0;
	int m_width, m_height, max_iteration;
	unsigned int percentage;
	


	int   isDebug = 0;

	#ifdef DEBUG
		isDebug = 1;
		AutoTest(image);
	#endif

	if (!isDebug) {
		FileNotRead = 1 ; 
		PrintMenu();
		printf("please make your choice: ");
		scanf("%d", &choice);
		while (choice != 18){
			switch (choice){

			case 1:
				printf("Please input the file name to load: ");
				scanf("%s", fname);
				image = ReadImage(fname);
				break;
		  
			case 2:
				printf("Please input the file name to save: ");
				scanf("%s", fname);
				SaveImage(fname, image);
				break;
					
			case 3:
				image = BlackNWhite(image);
				printf("\"Black & White\" operation is done!\n");
				break;
		  
			case 4:
				image = VFlip(image);
				printf( "\"Vertically Flip\" operation is done!\n" );
				break;
					
			case 5:
				image = HMirror(image);
				printf("\"Horizontally Mirror\" operation is done!\n");
				break;
				  
			case 6:
				printf("Enter Red   component for the target color: ") ;
				scanf("%d", &target_r) ;
				printf("Enter Green component for the target color: ") ;
				scanf("%d", &target_g) ;
				printf("Enter Blue  component for the target color: ") ;
				scanf("%d", &target_b) ;
				printf("Enter threshold for the color difference: ") ;
				scanf("%d", &threshold) ;
				printf("Enter value for Red component in the target color: ") ;
				scanf("%lf", &factor_r) ;
				printf("Enter value for Green component in the target color: ") ;
				scanf("%lf", &factor_g) ;
				printf("Enter value for Blue  component in the target color: ") ;
				scanf("%lf", &factor_b) ;
				
				image = ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g,factor_b);
				printf("\"Color Filter\" operation is done!\n");
				break;
					
			case 8:
				image = Shuffle(image);
				printf("\"Shuffle\" operation is done!\n");
				break;
					
			case 7:
				image = Edge(image);
				printf("\"Edge\" operation is done!\n");
				break;
					
			case 17:
				AutoTest(image); 
				break;	
		  
			case 9:
				printf("Enter the number of posterization bits (1 to 8): ");
				scanf("%d", &p_bits);
				image = Posterize(image, p_bits);
				printf("\"Posterize\" operation is done!\n");
				break;
				
			case 10:
				printf("Please input number of lights: ");
				scanf("%d", &number);
				printf("Please input the width of each light: ");
				scanf("%d", &lightWidth);
				image = FillLight(image, number, lightWidth);
				printf("\"FillLight\" operation is done!\n");
				break;
				
			case 11:
				printf("Please input the file name for the second image: ");
				scanf("%80s", &fname);
				printf("Please input x coordinate of the overlay image: ");
				scanf("%d", &x_offset);
				printf("Please input y coordinate of the overlay image: ");
				scanf("%d", &y_offset);
				image = Overlay(fname, image, x_offset, y_offset);
				printf("\"Overlay\" operation is done!\n");
				break;
				  
			case 13:
				printf("Please input the resizing percentage (integer between 1 to 500): ");
				scanf("%d", &percentage);
				image = Resize(percentage, image);
				printf("\"Resizing the image\" operation is done!\n");
				break;
			
			case 14:
				image = Rotate(image);
				printf("\"Rotate 90 degree clockwise\" operation is done!\n");
				break;
				 
			case 15:
				printf("Please input the width of the mandelbrot image: ");
				scanf("%d", &m_width);
				printf("Please input the height of the mandelbrot image: ");
				scanf("%d", &m_height);
				printf("Please input the max iteration for the mandelbrot calculation: ");
				scanf("%d", &max_iteration);
				image = Mandelbrot(m_width, m_height, max_iteration);
				printf("\"Mandelbrot\" operation is done!\n");
				break;
					
			default:
				printf("Invalid selection!\n");
				break;
			}

			PrintMenu();
			printf("please make your choice: ");
			scanf("%d", &choice);
		}
	}

	return 0;
}


/* print a menu */
void PrintMenu(){
	printf("--------------------------------\n");
	printf(" 1:  Load a PPM image\n");
	printf(" 2:  Save an image in PPM and JPEG format\n");
	printf(" 3:  Change a color image to Black & White\n");
	printf(" 4:  Flip an image vertically\n");
	printf(" 5:  Mirror an image horizontally\n");
	printf(" 6:  Color filter an image\n");
	printf(" 7:  Sketch the edge of an image\n");
	printf(" 8:  Shuffle an image\n");
	printf(" 9:  Posterize an Image\n");
	printf(" 10: Fill Lights to an image \n");
	printf(" 11: Overlay an image\n");
	printf(" 12: Bonus, Cut and Paste operation on image\n");
	printf(" 13: Resize the image\n");
	printf(" 14: Rotate 90 degrees clockwise\n");
	printf(" 15: Generate the Mandelbrot image\n");
	printf(" 16: Bonus, Add border outside the image\n");
	printf(" 17: Test all functions\n");
	printf(" 18: Exit\n");
}


/* auto test*/
void AutoTest(IMAGE *image) {
	
	char fname[SLEN] = "RingMall";
	char sname[SLEN];


	image = ReadImage(fname);
	image = BlackNWhite(image);
	strcpy(sname, "bw");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("Black & White tested!\n\n");
	#endif
	DeleteImage(image);

	image = ReadImage(fname);
	image = VFlip(image);
	strcpy(sname, "vflip");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("VFlip tested!\n\n");
	#endif
	DeleteImage(image);


	image = ReadImage(fname);
	image = HMirror(image);
	strcpy(sname, "hmirror");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("HMirror tested!\n\n");
	#endif
	DeleteImage(image);

	image = ReadImage(fname);
	image = ColorFilter(image, 180, 180, 50, 70, 0,255,0);
	strcpy(sname, "colorfilter");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("ColorFilter tested!\n\n");
	#endif
	DeleteImage(image);

	image = ReadImage(fname);
	image = Edge(image);
	strcpy(sname, "edge");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("Edge tested!\n\n");
	#endif
	DeleteImage(image);


	image = ReadImage(fname);
	image = Shuffle(image);
	strcpy(sname, "shuffle");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("Shuffle tested!\n\n");
	#endif
	DeleteImage(image);

	image = ReadImage(fname);
	image = Posterize(image, 7);
	strcpy(sname, "poster");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("Posterize tested!\n\n");
	#endif
	DeleteImage(image);

	image = ReadImage(fname);
	image = FillLight(image, 200, 20);
	strcpy(sname, "light");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("FillLight tested!\n\n");
	#endif
	DeleteImage(image);

	image = ReadImage(fname);
	char fname_test[SLEN] = "Peter";
	image = Overlay(fname_test, image, 350, 300);
	strcpy(sname, "overlay_peter");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("Overlay with the same image sizes tested!\n\n");
	#endif
	DeleteImage(image);

	image = ReadImage(fname);
	char fname_test2[SLEN] = "Spider";
	image = Overlay(fname_test2, image, 90, -10);
	strcpy(sname, "overlay_spider");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("Overlay with the same image sizes tested!\n\n");
	#endif
	DeleteImage(image);

	image = ReadImage(fname);
	image = Resize(175, image);
	strcpy(sname, "bigresize");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("Resizing for big tested!\n\n");
	#endif
	DeleteImage(image);

	image = ReadImage(fname);
	image = Resize(60, image);
	strcpy(sname, "smallresize");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("Resizing for small tested!\n\n");
	#endif
	DeleteImage(image);

	image = ReadImage(fname);
	image = Rotate(image);
	strcpy(sname, "rotate");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("Rotate 90 degrees clockwise tested!\n\n");
	#endif
	DeleteImage(image);

	image = Mandelbrot(720, 538, 2000);
	strcpy(sname, "mandelbrot");
	SaveImage(sname, image);
	#ifdef DEBUG
	printf("Generate the mandelbrot image tested!\n\n");
	#endif
	DeleteImage(image);
}
