#include "Image.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
unsigned char GetPixelR(const IMAGE *image, unsigned int x, unsigned int y){
	assert(image != NULL);
	assert(x < image->W);
	assert(y < image->H);
	assert(image->R != NULL);
	return image->R[x + y*image->W];

}
unsigned char GetPixelG(const IMAGE *image, unsigned int x, unsigned int y){
	assert(image != NULL);
	assert(x < image->W);
	assert(y < image->H);
	assert(image->G != NULL);
	return image->G[x + y*image->W];
}

unsigned char GetPixelB(const IMAGE *image, unsigned int x, unsigned int y){
	assert(image != NULL);
	assert(x < image->W);
	assert(y < image->H);
	assert(image->B != NULL);
	return image->B[x + y*image->W];
}
void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r){

	assert(image != NULL);
	assert(x < image->W);
	assert(y < image->H);
	assert(image->R != NULL);

	image->R[x + y*image->W] = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g)
{
	assert(image != NULL);
	assert(x < image->W);
	assert(y < image->H);
	assert(image->G != NULL);
	image->G[x + y*image->W] = g;
}
void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b)
{

	assert(image != NULL);
	assert(x < image->W);
	assert(y < image->H);
	assert(image->B != NULL);

	image->B[x + y*image->W] = b;
}
unsigned int ImageWidth(const IMAGE *image){
	assert(image != NULL);
	return  image->W;
}
unsigned int ImageHeight(const IMAGE *image){
	assert(image != NULL);
	return image->H;
}

IMAGE *CreateImage(unsigned int w, unsigned int h){

	IMAGE *image = malloc(sizeof(IMAGE));
	assert(image);
	if(!image)
		perror("Out of memory!Aborting....");
	image->W = w;
	image->H = h;
	image->R = malloc(sizeof(unsigned char) * w * h);
	assert(image->R);
	image->G = malloc(sizeof(unsigned char) * w * h);
	assert(image->G);
	image->B = malloc(sizeof(unsigned char) * w * h);
	assert(image->B);
	return image;
}

void DeleteImage(IMAGE *image){
	assert(image);
	free(image->R);
	image -> R = NULL;
	free(image->G);
	image -> G = NULL;
	free(image->B);
	image -> B = NULL;
	free(image);
	image = NULL;

}
