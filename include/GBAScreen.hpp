#include "cstring"
#include "cmath"
class GBAScreen 
{

public:
    GBAScreen(){}

    inline void fill(unsigned short color)
    {
        memset((unsigned short*)vram,color, width*height*sizeof(unsigned short));
    }
    inline void drawPixelAt( unsigned int heightPos, unsigned int widthPos, unsigned short color )
    {
        vram[heightPos*width + widthPos] = color;
    }

    inline void clear()
    {
        memset((unsigned short*)vram,0, width*height*sizeof(unsigned short));
    }

    inline void drawLine( unsigned int startY, unsigned int startX, 
                          unsigned int stopY,  unsigned int stopX )

    {
        float sizeX     = (float)stopX  - (float)startX;
        float sizeY     = (float)stopY - (float)startY;
        float magnitude = sqrt(sizeX*sizeX + sizeY*sizeY);

        float normX = sizeX/magnitude;
        float normY = sizeY/magnitude;

        float dx = 0;
        float dy = 0;

        bool xDone = false;
        bool yDone = false;

        while( true )
        {
            drawPixelAt(startY + dy, startX + dx, 0x310);

            if( (int)(startX + dx) != (int)stopX )
            {
                dx  += normX;
            }
            else
            {
                xDone = true;
            }

            if( (int)(startY + dy) != (int)stopY )
            {
                dy += normY;
            }
            else
            {
                yDone = true;
            }

            if( xDone && yDone )
            {
                break;
            }
        }
    }


    static const unsigned int height = 160;
    static const unsigned int width  = 240;

private:

    volatile unsigned char  *ioram = (unsigned char*)  0x04000000;
	volatile unsigned short *vram  = (unsigned short *)0x06000000;

};