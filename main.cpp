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

unsigned char checkKey(char key) {
    char color;
    if (keyPressed(key)) {
        color = 1;           
    } else {
        color = 4;
    }
    return color;
}

int main(void){
    ctrlbrk(ctrlbrk_handler);
    initLog();
    startKeyboardDetector();
    startGraphicsMode();
    randomize();
           
    clearScreen(0);
    unsigned char color;
    clock_t before=clock();
    int count = 0;
    while (1) {

        fillRect(0, 50, 50, 50, checkKey(KEY_A));
        fillRect(50, 50, 50, 50, checkKey(KEY_S));
        fillRect(100, 50, 50, 50, checkKey(KEY_D));
        fillRect(50, 0, 50, 50, checkKey(KEY_W));

        if (keyPressed(KEY_Q) && keyPressed(KEY_ALT)) {
            break;
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

