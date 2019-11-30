/* Advanced.h */
#include "Image.h"
#ifndef ADVANCED_H
#define ADVANCED_H

IMAGE *AddNoise(IMAGE *image, int n);

IMAGE *Sharpen(IMAGE *image);

IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits);

IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount);

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H);

IMAGE *Resize(IMAGE *image, int percentage);

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast);

IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image);

#endif
