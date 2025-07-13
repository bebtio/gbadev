#include "GBAScreen.hpp"
#include <gba.h>
#include <gba_console.h>

int main(void)
{
    GBAScreen screen;

	// Write into the I/O registers, setting video display parameters.
	volatile unsigned char *ioram = (unsigned char *)0x04000000;
	ioram[0] = 0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
	ioram[1] = 0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)

	// Write pixel colours into VRAM
	volatile unsigned short *vram = (unsigned short *)0x06000000;
	// Wait forever
    float pos = 0;
    float vel = 0.1;
    
    int count = 0;


    float r = .0005;
    float x = 0;

    float T = 0;
    float f = 0.01;

    unsigned char c = 0;
    screen.drawLine(0,0,159,159);
    while(true)
    {
        c += 1;
        screen.drawPixelAt(GBAScreen::height/2, GBAScreen::width/2, 0xffff);

    }
        


	return 0;
}