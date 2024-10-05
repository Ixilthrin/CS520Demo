#include "bmp.h"

BMP::BMP()
{
} 

BMP::~BMP()
{
    if (colorValues)
        free(colorValues);
}
// Return -1 on error.
int BMP::readWithCString(char * bmpPath)
{
    readWithString(bmpPath);
    return 0;
}

// Return -1 on error.
int BMP::readWithString(char *path)
{
    FILE *file;
    file = fopen(path, "rb");
    printf("file = %d\n", (int) file);
    printf("Read the file\n");
    int result = readWithFilePointer(file);
    fclose(file);
    return result;
}

// Return -1 on read error.
int BMP::readWithFilePointer(FILE * file)
{   
    // First two bytes are "BM"
    int c;
    printf("BM = %d\n", c);
    c = getc(file);  // 'B'
    printf("%d\n", c);;
    //printf("%c\n", (char) c);
    
    c = getc(file);  // 'M'
    
    printf("%d\n", c);
    
    // Next 4 bytes are the file size in little endian order.
    fileSize = readInt(4, file);
    printf("File size is %d\n", fileSize);
    //printf("filesize = %d\n", fileSize);
    
    // Next 4 bytes are reserved.
    firstReserved = readInt(4, file);
    
    // Next 4 bytes is the picture offset.
    pictureOffset = readInt(4, file);
    
    // Next 4 bytes is the header size.
    headerSize = readInt(4, file);
    
    // Next 4 bytes is the image width.
    width = readInt(4, file);
    printf ("width = %d\n", width);
    // Next 4 bytes is the image height.
    height = readInt(4, file);
    printf ("height = %d\n", height);
    // Next 2 bytes is the number of bit planes.
    bitPlanes = readInt(2, file);
    //printf ("bitPlanes = %d\n", bitPlanes);
    // Next 2 bytes is the color depth in bits per pixel.
    colorDepth = readInt(2, file);
    //printf ("colorDepth = %d\n", colorDepth);
    // Next 4 bytes is the compression type
    // Normally 0.
    // 1 indicates run length encoding of 8 bits per pixel.
    // 2 indicates run length encoding of 4 bits per pixel.
    compression = readInt(4, file);
    //printf ("compression = %d\n", compression);
    // Next 4 bytes is the compressed image size.
    compressedImageSize = readInt(4, file);
    //printf ("compressedImageSize = %d\n", compressedImageSize);
    // Next 4 bytes is the horizontal resolution.
    // pixels per meter
    horizontalResolution = readInt(4, file);
    //printf ("horizontalResolution = %d\n", horizontalResolution);
    // Next 4 bytes is the vertical resolution.
    // pixels per meter
    verticalResolution = readInt(4, file);
    //printf ("verticalResolution = %d\n", verticalResolution);
    // Next 4 bytes is the number of colors used.
    // NCL: value = 0 for full color set
    colorsUsed = readInt(4, file);
    //printf ("colorsUsed = %d\n", colorsUsed);
    // Next 4 bytes is the number of important colors.
    // NIC: value = 0 implies all colors are important.
    importantColors = readInt(4, file);
    //printf ("importantColors = %d\n", importantColors);
    // Next is the color pallete
    // NYI: For now just read the bytes and throw away.
    // 1 byte each for blue, green, red. 1 byte reserved 
    unsigned int paletteLength = colorsUsed * 4;
    for (int p = 0; p < paletteLength; ++p)
    {
        getc(file);
    }
    // Image: left to right, top to bottum order
    int bytesPerPixel = colorDepth / 8;
    printf("bytesPerPixel is %d\n", bytesPerPixel);
    int horizontalPadding = (4 - ((width * bytesPerPixel) % 4)) % 4;
    int sizeOfAllocation = sizeof(unsigned char) * bytesPerPixel * height * width;
    colorValues = (unsigned char *)
        malloc(sizeOfAllocation);
    printf("Size of colorValues is %d\n", sizeOfAllocation);
    int colorValueIndex = 0;
    int row = 0;
    int column = 0;
    for (row = height; row > 0; --row)
    {
        for (column = 0; column < width; ++column) 
        {
            // read the blue value, green value, red value
            unsigned char nextThree[3];
            for (int d = 0; d < 3; ++d)
            {
                nextThree[d] = (unsigned char) getc(file);
            }
            colorValues[colorValueIndex++] = nextThree[2];
            //printf("red = %d\n", (unsigned int) nextThree[2]);
            colorValues[colorValueIndex++] = nextThree[1];
            //printf("green = %d\n", (unsigned int) nextThree[1]);
            colorValues[colorValueIndex++] = nextThree[0];
            //printf("blue = %d\n", (unsigned int) nextThree[0]);
        }
        // Read and throw away the padding.
        unsigned int paddingLength = horizontalPadding * bytesPerPixel;
        for (int pad = 0; pad < paddingLength; ++pad)
        {
            getc(file);
        }
    }
    //printf("done\n");
    return 0;
}

// Reads little endian
int BMP::readInt(const int byteLength, FILE *file) 
{
    int bytes[byteLength];
    for (int k = 0; k < byteLength; ++k)
    {
       bytes[k] = getc(file); 
    }
    int intValue = 0;
    int i = 0;
    int j = 0;
    for (i = 0; i < byteLength; i++) 
    {
        int c = bytes[i];
        for (j = 0; j < i; ++j)
        {
            // Shift 1 byte
            c = c << 8;
        }
        intValue += c;
    }
    return intValue;
}

int BMP::getColorDepth()
{
    return colorDepth;
}

unsigned char * BMP::getColorValues()
{
    return colorValues;
}

