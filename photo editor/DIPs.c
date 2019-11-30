/* DIPS.c *
 *  */
#include <time.h>
#include "Constants.h"
#include "DIPs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Image.h"
#include <assert.h>
IMAGE *BlackNWhite(IMAGE *image){
	assert(image);
	int x, y, tmp;

	for (y = 0; y < ImageHeight(image); y++)
	{
		for (x = 0; x < ImageWidth(image); x++)
		{
			tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
			SetPixelR(image, x, y, tmp);
			SetPixelG(image, x, y, tmp);
			SetPixelB(image, x, y, tmp);
		}
	}
	return image;
}
IMAGE *Negative(IMAGE *image){
	assert(image);
	int x, y;
	for (x = 0; x < ImageWidth(image); x++)
		for (y = 0; y < ImageHeight(image); y++){
			SetPixelR(image, x, y, MAX_PIXEL - GetPixelR(image, x, y));
			SetPixelG(image, x, y, MAX_PIXEL - GetPixelG(image, x, y));
			SetPixelB(image, x, y, MAX_PIXEL - GetPixelB(image, x, y));
		}
	return image;
}
IMAGE *ColorFilter (IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) {
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    int x, y;
    for (y = 0; y < image->H; y++){
        for (x = 0; x < image->W; x++){
            if (abs(GetPixelR(image, x, y) - target_r) <= threshold
                    && abs(GetPixelG(image, x, y) - target_g) <= threshold
                    && abs(GetPixelB(image, x, y) - target_b) <= threshold) {
                SetPixelR(image, x, y, replace_r);
                SetPixelG(image, x, y, replace_g);
                SetPixelB(image, x, y, replace_b);
            }
        }
    }
return image;
}
IMAGE *Edge(IMAGE *image){
	assert(image);

	int             x, y, m, n, a, b;
	unsigned char   tmpR[ImageWidth(image)][ImageHeight(image)];
	unsigned char   tmpG[ImageWidth(image)][ImageHeight(image)];
	unsigned char   tmpB[ImageWidth(image)][ImageHeight(image)];
	for (y = 0; y < ImageHeight(image); y++){
		for (x = 0; x < ImageWidth(image); x++) {
			tmpR[x][y] = GetPixelR(image, x, y);
			tmpG[x][y] = GetPixelG(image, x, y);
			tmpB[x][y] = GetPixelB(image, x, y);
		}
	}
	int sumR = 0;   /* sum of the intensity differences with neighbors */
	int sumG = 0;
	int sumB = 0;
	int i, j, k;
	for (y = 1; y < ImageHeight(image) - 1; y++){
		for (x = 1; x < ImageWidth(image) - 1; x++){
			for (n = -1; n <= 1; n++){
				for (m = -1; m <= 1; m++) {
					a = (x + m >= ImageWidth(image)) ? ImageWidth(image) - 1 : (x + m < 0) ? 0 : x + m;
					b = (y + n >= ImageHeight(image)) ? ImageHeight(image) - 1 : (y + n < 0) ? 0 : y + n;
					sumR += (tmpR[x][y] - tmpR[a][b]);
					sumG += (tmpG[x][y] - tmpG[a][b]);
					sumB += (tmpB[x][y] - tmpB[a][b]);
				}
			}
			i = (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR;
			j = (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG;
			k = (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB;
			SetPixelR(image, x, y, i);
			SetPixelG(image, x, y, j);
			SetPixelB(image, x, y, k);
			sumR = sumG = sumB = 0;
		}
	}
	/* set all four borders to 0 */
	for (y = 0; y < ImageHeight(image); y++) {
		SetPixelR(image, 0, y, 0);
		SetPixelG(image, 0, y, 0);
		SetPixelB(image, 0, y, 0);
		SetPixelR(image, ImageWidth(image) - 1, y, 0);
		SetPixelG(image, ImageWidth(image) - 1, y, 0);
		SetPixelB(image, ImageWidth(image) - 1, y, 0);

	}
	for (x = 0; x < ImageWidth(image); x++) {
		SetPixelR(image, x, 0, 0);
		SetPixelG(image, x, 0, 0);
		SetPixelB(image, x, 0, 0);
		SetPixelR(image, x, ImageWidth(image) - 1, 0);
		SetPixelG(image, x, ImageWidth(image) - 1, 0);
		SetPixelB(image, x, ImageWidth(image) - 1, 0);


	}
	return image;
}
IMAGE *VMirror(IMAGE *image){
	assert(image);
	int x, y;
	for (y = 0; y < ImageHeight(image) / 2; y ++) {
		for (x = 0; x < ImageWidth(image); x ++) {
			SetPixelR(image, x, ImageHeight(image) - 1 - y, GetPixelR(image, x, y));
			SetPixelG(image, x, ImageHeight(image) - 1 - y, GetPixelG(image, x, y));
			SetPixelB(image, x, ImageHeight(image) - 1 - y, GetPixelB(image, x, y));

		}
	}

	return image;
}
IMAGE *Shuffle(IMAGE *image){

	assert(image);
	unsigned char TempR[ImageWidth(image)][ImageHeight(image)], TempG[ImageWidth(image)][ImageHeight(image)], TempB[ImageWidth(image)][ImageHeight(image)];
	for (int i = 0; i < ImageWidth(image); i++)
		for (int j = 0; j < ImageHeight(image); j++){
			TempR[i][j] = GetPixelR(image, i, j);
			TempG[i][j] = GetPixelG(image, i, j);
			TempB[i][j] = GetPixelB(image, i, j);
		}
	srand(time(NULL)); /*seed rand to time */
	int b;
	int original[16];
	for (int i = 0; i < 16; i++)
		original[i] = (i+1);
	int generate[16];
	for (int i = 0; i < 16; i++){
		b = 1;
		while(b == 1){/*sets a new value for g[i] and checks that there's no duplicate */
			generate[i] = (rand() % 16);
			for (int j = 0; j < 16; j++){
				if (i == j)
					continue;
				else if (generate[j] == generate[i]){
					b = 1;
					break;
				}
				else
					b = 0;
			}

		}
		printf("%d is  %d\n", i , generate[i]);
	}

	for (int i = 0; i < 16; i++){
		for(int c = 0; c < 150; c++)
			for(int r = 0; r < 100; r++){
				SetPixelR(image, (i%4)*150+c, (i/4)*100+r, TempR[(generate[i]%4)*150+c][(generate[i]/4)*100+r]);
				SetPixelG(image, (i%4)*150+c, (i/4)*100+r, TempG[(generate[i]%4)*150+c][(generate[i]/4)*100+r]);
				SetPixelB(image, (i%4)*150+c, (i/4)*100+r, TempB[(generate[i]%4)*150+c][(generate[i]/4)*100+r]);




			}

	}
	return image;
}
IMAGE *VFlip(IMAGE *image){
	assert(image);
	unsigned char TempR[ImageWidth(image)][ImageHeight(image)],TempG[ImageWidth(image)][ImageHeight(image)],TempB[ImageWidth(image)][ImageHeight(image)];
	for (int i = 0; i < ImageWidth(image); i++)
		for (int j = 0; j < ImageHeight(image); j++){
			TempR[i][j] = GetPixelR(image, i , j);
			TempG[i][j] = GetPixelG(image, i , j);
			TempB[i][j] = GetPixelB(image, i , j);

		}
	for (int i = 0; i < ImageWidth(image); i++)
		for (int j = 0; j< ImageHeight(image); j++){
			SetPixelR(image, i, j, TempR[i][ImageHeight(image) - 1 - j]);
			SetPixelG(image, i, j, TempG[i][ImageHeight(image) - 1 - j]);
			SetPixelB(image, i, j, TempB[i][ImageHeight(image) - 1 - j]);

		}
	return image;
}
IMAGE *AddBorder(IMAGE *image, const char color, int border_width){
		assert(image);	
		int col[3];

		if (strcmp(color, "yellow") == 0){
			col[0] = 255;
			col[1] = 255;
			col[2] = 0;

		}


		else if (strcmp(color, "black") == 0){
			col[0] = 0;
			col[1] = 0;
			col[2] = 0;
		}

		else if (strcmp(color, "white") == 0){
			col[0] = 255;
			col[1] = 255;
			col[2] = 255;
		}

		else if (strcmp(color, "red") == 0){
			col[0] = 255;
			col[1] = 0;
			col[2] = 0;
		}

		else if (strcmp(color, "green") == 0){
			col[0] = 0;
			col[1] = 255;
			col[2] = 0;
		}

		else if (strcmp(color, "blue") == 0){
			col[0] = 0;
			col[1] = 0;
			col[2] = 255;
		}

		else if (strcmp(color, "cyan") == 0){
			col[0] = 0;
			col[1] = 255;
			col[2] = 255;
		}
		else if (strcmp(color, "pink") == 0){
			col[0] = 255;
			col[1] = 192;
			col[2] = 203;
		}

		else if (strcmp(color, "orange") == 0){
			col[0] = 255;
			col[1] = 165;
			col[2] = 0;
		}

		else
			printf("error");

		for (int i = 0; i < ImageWidth(image); i++)
			for (int j = 0; j < border_width; j++){
				SetPixelR(image, i, j, col[0]);
				SetPixelG(image, i, j, col[1]);
				SetPixelB(image, i, j, col[2]);

			}
		for (int i = 0; i < (border_width*9/16); i++)
			for (int j = border_width; j < (ImageHeight(image) - 1 - border_width); j++){
				SetPixelR(image, i, j, col[0]);
				SetPixelG(image, i, j, col[1]);
				SetPixelB(image, i, j, col[2]);

			}
		for (int i = (ImageWidth(image) - (border_width*9/16)-1); i < ImageWidth(image); i++)
			for (int j = border_width; j < (ImageHeight(image) - 1 - border_width); j++){

				SetPixelR(image, i, j, col[0]);
				SetPixelG(image, i, j, col[1]);
				SetPixelB(image, i, j, col[2]);

			}
		for (int i = 0; i < ImageWidth(image); i++)
			for (int j = (ImageHeight(image) - 1 - border_width); j < ImageHeight(image); j++){


				SetPixelR(image, i, j, col[0]);
				SetPixelG(image, i, j, col[1]);
				SetPixelB(image, i, j, col[2]);

			}
		return image;
	}
