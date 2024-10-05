#ifndef __BMP_H__
#define __BMP_H__

#include "main.h" 

class BMP
{
    int fileSize;
    int firstReserved;
    int pictureOffset;
    int headerSize;
    int width;
    int height;
    int bitPlanes;
    int colorDepth; // Number of bits, e.g. 24 bit color.
    int compression;
    int compressedImageSize;
    int horizontalResolution;
    int verticalResolution;
    int colorsUsed;
    int importantColors;
    // colorValues: left to right, top to bottum, red, green blue order
    // Each pixel is colorDepth / 8 bytes in length
    unsigned char *colorValues;
    int sizeOfColorValues;

public:
   BMP();
    ~BMP();
// Return -1 on error.
   int readWithCString (char *s);

// Return -1 on error.
   int readWithString(char *s);
// Return -1 on error
   int readWithFilePointer(FILE *file);
   int readInt(int byteLength, FILE *file);
   int getColorDepth();
   unsigned char * getColorValues();
    int getHeight() { return height; }
    int getWidth() { return width; }
};
 
#endif
