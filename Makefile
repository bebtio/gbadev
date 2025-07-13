DEVKITPRO_INCLUDES = -I/opt/devkitpro/libgba/include \
                     -I/opt/devkitpro/devkitARM/arm-none-eabi/include \
                     -I/opt/devkitpro/devkitARM/arm-none-eabi/include/c++/15.1.0

INCLUDES= -I./include ${DEVKITPRO_INCLUDES} 

all: test

test: game.gba
	gbafix game.gba

game.gba: main.elf 
	arm-none-eabi-objcopy -v -O binary main.elf game.gba

main.elf: main.o
	arm-none-eabi-c++ main.o -mthumb-interwork -mthumb -specs=gba.specs -o main.elf

main.o: main.cpp
	arm-none-eabi-c++ -c main.cpp ${INCLUDES} -mthumb-interwork -mthumb -O2 -o main.o



.PHONE: clean

clean:
	@rm -f *.elf;
	@rm -f *.o;
	@rm -f *.gba;
