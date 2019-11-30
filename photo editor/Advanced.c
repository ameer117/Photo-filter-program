#include "Advanced.h"
#include "Image.h"
#include "Constants.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
IMAGE *AddNoise(IMAGE *image, int percentage){
	assert(image);
	int x, y;
	int pixels =(percentage*ImageWidth(image)*ImageHeight(image))/100;
	srand(time(NULL));
	for (int i = 0; i < pixels; i++){
		x = rand() % ImageWidth(image);
		y = rand() % ImageHeight(image);
		SetPixelR(image, x, y, 255);
		SetPixelG(image, x, y, 255);
		SetPixelB(image, x, y, 255);
	}
	return image;

}
IMAGE *Sharpen(IMAGE *image){
	assert(image);
	int a, b, c;
	unsigned char tempR[ImageWidth(image)][ImageHeight(image)], tempG[ImageWidth(image)][ImageHeight(image)], tempB[ImageWidth(image)][ImageHeight(image)];
        unsigned char R[ImageWidth(image)][ImageHeight(image)], G[ImageWidth(image)][ImageHeight(image)], B[ImageWidth(image)][ImageHeight(image)];
	for (int i = 0; i < image->H; i++)
		for(int j = 0; j < image->W; j++){
			R[i][j] = GetPixelR(image, i, j);
			G[i][j] = GetPixelG(image, i, j);
			B[i][j] = GetPixelB(image, j, j);
}
	for (int i = 0; i < ImageHeight(image); i++)
		for (int j = 0; j < ImageWidth(image); j++){
			tempR[j][i] = 0;
			tempG[j][i] = 0;
			tempB[j][i] = 0;
		}
	for (int i = 1; i < ImageWidth(image) - 1; i++)
		for (int j = 1; j < ImageHeight(image) - 1; j++){
			a = 9*R[i][j] - R[i-1][j-1] - R[i-1][j] - R[i-1][j+1] - R[i][j-1] - R[i][j+1] - R[i+1][j-1] - R[i+1][j] - R[i+1][j+1];
			if (a > 255)
				tempR[i][j] = 255;
			else if (a < 0)
				tempR[i][j] = 0;
			else
				tempR[i][j] = a;
			b = 9*G[i][j] - G[i-1][j-1] - G[i-1][j] - G[i-1][j+1] - G[i][j-1] - G[i][j+1] - G[i+1][j-1] - G[i+1][j] - G[i+1][j+1];
			if (b > 255)
				tempG[i][j] = 255;
			else if (b < 0)
				tempG[i][j] = 0;
			else
				tempG[i][j] = b;
			c = 9*B[i][j] - B[i-1][j-1] - B[i-1][j] - B[i-1][j+1] - B[i][j-1] - B[i][j+1] - B[i+1][j-1] - B[i+1][j] - B[i+1][j+1];
			if (c > 255)
				tempB[i][j] = 255;
			else if (c < 0)
				tempB[i][j] = 0;

			else
				tempB[i][j] = c;
		}
	for (int x = 1; x < ImageWidth(image) -1; x++)
		for (int y = 1; y < ImageHeight(image) -1; y++){
			SetPixelR(image, x, y, tempR[x][y]);
			SetPixelG(image, x, y, tempG[x][y]);
			SetPixelB(image, x, y, tempB[x][y]);
		}
return image;

}
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits){
	assert(image);
	unsigned char R[ImageWidth(image)][ImageHeight(image)], G[ImageWidth(image)][ImageHeight(image)],B[ImageWidth(image)][ImageHeight(image)];
	for (int i = 0; i < ImageWidth(image); i++)
		for(int j = 0; j < ImageHeight(image); j++){
			R[i][j] = GetPixelR(image, i, j);
			G[i][j] = GetPixelG(image, i, j);
			B[i][j] = GetPixelB(image, i, j);			
		}
	for (int i = 0; i < ImageWidth(image); i++)
		for (int j = 0; j < ImageHeight(image); j++)
		{
			R[i][j] >>= rbits;
			R[i][j] <<= rbits;
			G[i][j] >>= gbits;
			G[i][j] <<= gbits;
			B[i][j] >>= bbits;
			B[i][j] <<= bbits;

		}
	for (int x = 0; x < ImageWidth(image); x++)
		for (int y = 0; y < ImageHeight(image); y++){
			for (int i = 0; i < rbits - 1; i++)
				R[x][y] |= 1<<i;
			for (int i = 0; i < gbits - 1; i++)
				G[x][y] |= 1<<i;
			for (int i = 0; i < bbits - 1; i++)
				B[x][y] |= 1<<i;
		}
	for (int x = 0; x < ImageWidth(image); x++)
		for (int y = 0; y < ImageHeight(image); y++){
			SetPixelR(image, x, y, R[x][y]);
			SetPixelG(image, x, y, G[x][y]);
			SetPixelB(image, x, y, B[x][y]);			
		}
	return image;
}
IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount){

	assert(image);
	{
		int a, b, c;
		unsigned char tempR1[ImageWidth(image)][ImageHeight(image)], tempG1[ImageWidth(image)][ImageHeight(image)], tempB1[ImageWidth(image)][ImageHeight(image)];
		for (int x = 0; x < ImageWidth(image); x++)
			for (int y = 0; y < ImageHeight(image); y++)
			{
				tempR1[x][y] = GetPixelR(image, x, y) / 2;
				tempG1[x][y] = GetPixelG(image, x, y) / 2;
				tempB1[x][y] = GetPixelB(image, x, y) / 2;
			}
		for (int x = 0; x < ImageWidth(image); x++)
			for (int y = 0; y < ImageHeight(image); y++)
			{
				a = 0;
				b = 0;
				c = 0;
				if (BlurAmount + x > ImageWidth(image))
					BlurAmount = ImageWidth(image) - x;
				for (int i = 0; (i < BlurAmount); i++)
				{
					a += GetPixelR(image, (x+i), y);
					b += GetPixelG(image, x+i, y);
					c += GetPixelB(image, x+i, y);
				}
				a /= (2*BlurAmount);
				b /= (2*BlurAmount);
				c /= (2*BlurAmount);
				tempR1[x][y] += a;
				tempG1[x][y] += b;
				tempB1[x][y] += c;
				if (tempR1[x][y] > 255)
					tempR1[x][y] = 255;
				if (tempG1[x][y] > 255)
					tempG1[x][y] = 255;
				if (tempB1[x][y] > 255)
					tempB1[x][y] = 255;
			}
		for (int y = 0; y < ImageHeight(image); y++)
			for (int x = 0; x < ImageWidth(image); x++)
			{
				SetPixelR(image, x, y, tempR1[x][y]);
				SetPixelG(image, x, y, tempG1[x][y]);
				SetPixelB(image, x, y, tempB1[x][y]);
			}
	}
	return image;
}
IMAGE *Crop(IMAGE *image, int x, int y,int W, int H){
	assert(image);
	if (W > ImageWidth(image))
		W = ImageWidth(image);


	if (H > ImageHeight(image))
		H = ImageHeight(image);

	IMAGE *crop = NULL;
	crop = CreateImage((W-x),(H-y));
	for (int i = 0; i < W-x; i++)
		for (int j = 0; y < H-x; j++){
			SetPixelR(crop, i, j, GetPixelR(image, i+x, j+y));
			SetPixelG(crop, i, j, GetPixelG(image, i+x, j+y));
			SetPixelB(crop, i, j, GetPixelB(image, i+x, j+y));
		}
	DeleteImage(image);
	image = NULL;
	return crop;			
}


IMAGE *Resize(IMAGE *image, int percentage){
	assert(image);
	int NW, NH;
	NW = image->W*(percentage/100.00);
	NH = image->H*(percentage/100.00);
	IMAGE *resize = CreateImage(NW, NH);
	if (percentage > 100)
		for(int i = 0; i < resize->W; i++)
			for (int j = 0; i < resize->H; j++){
				SetPixelR(resize, i, j, GetPixelR(image,i*(percentage/100.00), j*(percentage/100.00)));
				SetPixelG(resize, i, j, GetPixelG(image,i*(percentage/100.00), j*(percentage/100.00)));
				SetPixelB(resize, i, j, GetPixelB(image,i*(percentage/100.00), j*(percentage/100.00)));
			}
	else if (percentage < 100)
		for(int i = 0; i < resize->W; i++)
			for (int j = 0; j < resize->H; j++){
				int a,b,c,counter = 0;
				for(int x = i/(percentage/100.00); x <= (i+1)/(percentage/100.00);x++)
					for (int y = j/(percentage/100.00); y <= (j+1)/(percentage/100.00);y++){
						a+= GetPixelR(image, x, y);
						b+= GetPixelG(image, x, y);
						c+= GetPixelB(image, x, y); 
						counter++;
					}
				SetPixelR(resize, i, j, a/counter);
				SetPixelG(resize, i, j, b/counter);
				SetPixelB(resize, i, j, c/counter);  
			}
	else
		DeleteImage(resize);
	return image; //try to change this to return resize possibly

	DeleteImage(image);
	return resize;
}
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast){
	assert(image);
	if (brightness > 255)
		brightness = 255;
	if (brightness < -255)
		brightness = -255;
			if (contrast > 255)
				contrast = 255;
	if (contrast < -255)
		contrast = 255;
	int valueR, valueG, valueB;
	double factor = (double)(259*(contrast + 255))/(double)(255*(259-contrast));
	for (int i = 0; i < image->W; i++)
		for (int j = 0; j < image->H; j++){
			valueR = (int)(factor * (GetPixelR(image,i,j) - 128) + 128) + brightness;
			valueG = (int)(factor * (GetPixelG(image,i,j) - 128) + 128) + brightness;
			valueG = (int)(factor * (GetPixelB(image,i,j) - 128) + 128) + brightness;
			valueR = (valueR > 255) ? 255: (valueR < 0) ? 0: valueR;
			valueG = (valueG > 255) ? 255: (valueG < 0) ? 0: valueG;
			valueB = (valueB > 255) ? 255: (valueB < 0) ? 0: valueB;
			SetPixelR(image, i, j, valueR);
			SetPixelG(image, i, j, valueG);
			SetPixelB(image, i, j, valueB);
		}
	return image;
}
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image){
	int val1, val2, val3;
	for (int i = 0; i < image->W; i++)
		for (int j = 0; j < image->H; j++){
			if (GetPixelR(watermark_image, i%(watermark_image->W), j%(watermark_image->H)) == 0 && GetPixelG(watermark_image, i%(watermark_image->W), j%(watermark_image->H)) == 0 && GetPixelB(watermark_image, i%(watermark_image->W), j%(watermark_image->H)) == 0){			
				val1 = GetPixelR(image, i, j) * 1.45;
				val2 = GetPixelG(image, i, j) * 1.45;
				val3 = GetPixelB(image, i, j) * 1.45;					
				val1 = (val1 > 255) ? 255: val1;
				val2 = (val2 > 255) ? 255: val2;
				val3 = (val3 > 255) ? 255: val3;
				SetPixelR(image, i, j, val1);
				SetPixelG(image, i, j, val2);
				SetPixelB(image, i, j, val3);


			}

		}
	return image;

}


