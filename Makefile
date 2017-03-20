#Makefile: PhotoLab


CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -c
LFLAGS = -Wall

DESIGN = PhotoLab PhotoLabTest

all: PhotoLab PhotoLabTest
PhotoLab: PhotoLab
PhotoLabTest: PhotoLabTest


IMAGES = bw.ppm vflip.ppm hmirror.ppm shuffle.ppm \
		 edge.ppm colorfilter.ppm light.ppm \
		overlay_peter.ppm poster.ppm overlay_spider.ppm cutPaste.ppm mandelbrot.ppm \
   bigresize.ppm smallresize.ppm rotate.ppm

clean:
	rm -f *.o *.jpg $(DESIGN) $(IMAGES)

	
#compilation rules

FileIO.o   : FileIO.c FileIO.h Constants.h Image.h
	gcc -Wall -ansi -c FileIO.c -o FileIO.o
	
Image.o : Image.c Image.h
	gcc -Wall -ansi -c Image.c -o Image.o
	
Imagedebug.o : Image.c Image.h
	gcc -Wall -ansi -DDEBUG -c Image.c -o Imagedebug.o
        
FileIOdebug.o : FileIO.c FileIO.h Constants.h Image.h
	gcc -Wall -ansi -DDEBUG -c FileIO.c -o FileIOdebug.o
         
DIPs.o     : DIPs.c DIPs.h Constants.h Image.h
	gcc -Wall -ansi -c DIPs.c -o DIPs.o
	
DIPsdebug.o : DIPs.c DIPs.h Constants.h Image.h
	gcc -Wall -ansi -DDEBUG -c DIPs.c -o DIPsdebug.o
         
Advanced.o : Advanced.c Advanced.h Constants.h Image.h
	gcc -Wall -ansi -c Advanced.c -o Advanced.o
	
Advanceddebug.o : Advanced.c Advanced.h Constants.h Image.h
	gcc -Wall -ansi -c -DDEBUG Advanced.c -o Advanceddebug.o

PhotoLab.o : PhotoLab.c FileIO.h Constants.h Advanced.h DIPs.h Image.h
	gcc -Wall -ansi -c PhotoLab.c -g -o PhotoLab.o
	
PhotoLabTest.o : PhotoLab.c FileIO.h Constants.h Advanced.h DIPs.h Image.h
	gcc -Wall -ansi -DDEBUG -g -c PhotoLab.c -o PhotoLabTest.o 
  
PhotoLab   : FileIO.o DIPs.o Advanced.o PhotoLab.o Image.o

PhotoLabTest: FileIOdebug.o DIPsdebug.o Advanceddebug.o PhotoLabTest.o Imagedebug.o