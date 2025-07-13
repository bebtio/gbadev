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

    inline void drawLine( unsigned int startHeightPos, unsigned int startWidthPos, 
                          unsigned int stopHeightPos,  unsigned int stopWidthPos )

    {
        float widthStep  = (float)stopWidthPos  - (float)startWidthPos;
        float heightStep = (float)stopHeightPos - (float)startHeightPos;
        float n = sqrt(widthStep*widthStep + heightStep*heightStep);

        widthStep = widthStep/n;
        heightStep = heightStep/n;

        float width  = 0;
        float height = 0;

        bool widthDone = false;
        bool heightDone = false;
        while( true )
        {
            if( (int)(startHeightPos + height) != (int)stopHeightPos )
            {
                height += heightStep;
            }
            else
            {
                heightDone = true;
            }

            if( (int)(startWidthPos + width) != (int)stopWidthPos )
            {
                width  += widthStep;
            }
            else
            {
                widthDone = true;
            }

            drawPixelAt(startHeightPos + height, startWidthPos + width, 0x310);

            if( widthDone && heightDone )
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