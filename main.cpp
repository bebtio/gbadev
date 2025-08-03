#include "GBAScreen.hpp"



int main(void)
{

    // Initialize TTE for Mode 3 with default font and settings
    GBAScreen screen;

    // Define radius and initial position of line.


    int dx = 1;
    int dy = 1;

    int sz = 10;

    int x = screen.width-sz;
    int y = screen.height-sz;
    while(true)
    {
        key_poll();
        if(key_is_down(KEY_RIGHT))
        {
            x += dx;
        }

        if(key_is_down(KEY_LEFT))
        {
            x -= dx;
        }

        if(key_is_down(KEY_UP))
        {
            y -= dy;
        }

        if(key_is_down(KEY_DOWN))
        {
            y += dy;
        }


        if( x <= 0 )
        {
            x = 0;
        }

        if( y <= 0)
        {
            y = 0;
        }

        if( (x+sz) >= screen.width )
        {
            x = screen.width - sz  ;
        }

        if( (y+sz) >= screen.height )
        {
            y = screen.height - sz ;
        }
        screen.drawRectAt(x, y, sz,sz);
        screen.update();

        screen.clear();
    }

	return 0;
}