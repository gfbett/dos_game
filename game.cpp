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
    switchBuffer();
    
    for(int z = 0; z< 100;z++) {
        unsigned char color = z;
        for(int j=0;j<200;j++) {
            char prevcolor = color;
            for(int i=0;i<320;i++) {
                if (i!= 0 && i %20 == 0) {
                    color = color + 1;
                    color = color % 256;
                }
                putPixel(i, j, color);
            }
            if (j != 0 && j % 12 == 0) {
                color += 16;
                color = color % 256;
            } else {
                color = prevcolor;
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
