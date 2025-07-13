#include "cstring"

class GBAScreen 
{

public:
    GBAScreen(){}

    inline void fill(unsigned short color)
    {
        memset((unsigned short*)vram,color, width*height*sizeof(unsigned short));
    }
    inline void writeAt( unsigned int heightPos, unsigned int widthPos, unsigned short color )
    {
        vram[heightPos*width + widthPos] = color;
    }

    inline void clear()
    {
        memset((unsigned short*)vram,0, width*height*sizeof(unsigned short));
    }

    static const unsigned int height = 160;
    static const unsigned int width  = 240;

private:

    volatile unsigned char  *ioram = (unsigned char*)  0x04000000;
	volatile unsigned short *vram  = (unsigned short *)0x06000000;

};