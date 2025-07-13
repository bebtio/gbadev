#include "GBAScreen.hpp"
#include <gba.h>
#include <gba_console.h>
#include <cmath>

int main(void)
{
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

    while(true)
    {
        // Draw the line.
        screen.drawLine(
        GBAScreen::height/2,
        GBAScreen::width/2,
        GBAScreen::height/2+y,
        GBAScreen::width/2+x, 0xffff);
        
        // Rotate the line positions.
        deg += 0.8;
        x = r*cos( deg * 3.14159 / 180.0 );
        y = r*sin( deg * 3.14159 / 180.0 );

        screen.drawPixelAt(GBAScreen::height/2, GBAScreen::width/2, 0xff00);
        
        // Reset the drawing when the circle comes... full circle.
        if( deg > 360 )
        {
            screen.clear();
            deg = 0;
        }
    }

	return 0;
}