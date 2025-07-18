#include "cstring"
#include "cmath"
#include "tonc_math.h"
#include <vector>
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

    inline void drawLine( unsigned int startX, unsigned int startY, 
                          unsigned int stopX,  unsigned int stopY,
                          unsigned short color = 0xffff )

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
            drawPixelAt(startY + dy, startX + dx, color);

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


    void drawRect(unsigned int x1, unsigned int y1,
                  unsigned int x2, unsigned int y2,
                  unsigned short color = 0xffff
                 )
    {
        drawLine(x1, y1, x2, y1, color);
        drawLine(x1, y2, x2, y2, color);
        drawLine(x1, y1, x1, y2, color);
        drawLine(x2, y1, x2, y2, color);
    }

    void drawRectAt(
                        unsigned int x1, unsigned int y1, 
                        unsigned int width, unsigned int height,
                        unsigned short color = 0xffff
                   )
    {
        drawRect(x1,y1, x1+width, y1+height, color);        
    }

    void drawCircle( 
                        unsigned int radius,
                        unsigned int x,
                        unsigned int y,
                        unsigned short color = 0xffff )
    {
        // Rotate the line positions.
        int xPos = 0;
        int yPos = 0;

        for(unsigned int deg = 1; deg < 360; deg++ )
        {
            xPos = x + (radius) * (cos( deg * 3.14159 / 180));
            yPos = y + (radius) * (sin( deg * 3.14159 / 180));
            drawPixelAt(
                yPos,
                xPos,
                color);
        }
    }

    static const unsigned int height = 160;
    static const unsigned int width  = 240;

private:

    volatile unsigned char  *ioram = (unsigned char*)  0x04000000;
	volatile unsigned short *vram  = (unsigned short *)0x06000000;

};