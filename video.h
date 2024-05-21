#ifndef _VIDEO_H_
#define _VIDEO_H_

/*
    Funciones para manejo de video
*/
void startGraphicsMode();
void shutdownGraphicsMode();

void clearScreen(char color);
void putPixel(int x, int y, char color);
void fillRect(int x, int y, int width, int height, char color);
void switchBuffer();

#endif
