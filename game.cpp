#include "video.h"
#include "log.h"
#include "keyb.h"
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <time.h>


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
           
    clearScreen(0);
    clock_t before=clock();
	int count = 0;
    for(int z = 0; z< 500;z++) {
        unsigned char color = z;
    	for (int i = 0; i < 16; i++) {
			for(int j = 0; j < 16; j++) {
	    		int x = 20 * j;
				int y = 12 * i;
				fillRect(x, y, 20, 12, color);
				color = color < 255? color+1: 0;
			}
		}    
		switchBuffer();
        count += 1;
    }
    clock_t after = clock();


    shutdownGraphicsMode();
    float seconds = (after - before)/CLK_TCK;
    int fps = (int) (count/seconds);
    printf("Elapsed seconds: %f - FPS:%d", seconds, fps);
    shutdownKeyboardDetector();
    closeLog();

    return 0;
}
