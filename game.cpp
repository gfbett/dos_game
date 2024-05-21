#include "video.h"
#include "log.h"
#include "keyb.h"
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>



int ctrlbrk_handler(void) {
    shutdownKeyboardDetector();
    return 0;
}


int main(void){
    ctrlbrk(ctrlbrk_handler);
    initLog();
    startKeyboardDetector();
    startGraphicsMode();
    randomize();
           
    clearScreen(49);
	fillRect(100,100,50,30,30);
    switchBuffer();
	getch();
	   
    for(int z = 0; z< 500;z++) {
        unsigned char color = z;
    	for (int i = 0; i < 16; i++) {
			for(int j = 0; j < 16; j++) {
	    		int x = 20 * j;
				int y = 12 * i;
				fillRect(x, y, 20, 12, color);
				color = color < 256? color+1: 0;
			}
		}    
		switchBuffer();
    }
    getch();


    shutdownGraphicsMode();
    shutdownKeyboardDetector();
    closeLog();

    return 0;
}
