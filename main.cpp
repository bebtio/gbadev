#include "GBAScreen.hpp"
#include <cmath>

extern "C"
{
#include "tonc.h"
}

int main(void)
{

    // Initialize TTE for Mode 3 with default font and settings
    GBAScreen screen;

	// Write into the I/O registers, setting video display parameters.
	volatile unsigned char *ioram = (unsigned char *)0x04000000;
	ioram[0] = 0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
	ioram[1] = 0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)

	// Write pixel colours into VRAM
	volatile unsigned short *vram = (unsigned short *)0x06000000;


    // Define radius and initial position of line.
    int r = 50;
    float deg = 0;
    int x = r*cos( deg * 3.14159 / 180.0 );
    int y = r*sin( deg * 3.14159 / 180.0 );

    int xPos = 50;
    int yPos = 50;
    int xVel = 1;
    int yVel = 1;


    int radius = 20;
    while(true)
    {

        //screen.drawRectAt(xPos, yPos, 10, 10);
       
        for(int i = 0; i < 100; i++)
        {

        }

        if( xPos + radius > 239 )
        {
            xVel = -1;
        }
        else if( xPos - radius <= 0 )
        {
            xVel = 1;
        }

        if( yPos + radius > 159 )
        {
            yVel = -1;
        }
        else if( yPos - radius <= 0 )
        {
            yVel = 1;
        }

        xPos = xPos + xVel;
        yPos = yPos + yVel;


        screen.clear();
        screen.drawCircle(radius, xPos, yPos);
        screen.update();
    }

	return 0;
}