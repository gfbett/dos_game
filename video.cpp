#include "video.h"
#include "log.h"
#include <dos.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

// Funciones internas
int * PIXEL_OFFSET;
void far * vscreen;
void far * videoMemory;

void setVideoMode(unsigned char mode) {
    //Usa la interrupción 10 para setear el modo gráfico
    //0 en la parte alta de AX, modo en la parte baja
    asm {
        mov ah, 0
        mov al, mode
        int 10h
    }
}


/*
    Precalcula los offsets de cada fila de pixeles para poder ir a la posición de memoria de un pixel 
    de forma rápida. Básicamente cada posición, que corresponde a una fila, contiene el número 320 x {nro de fila}
*/
void calculateOffsets() {
    log("Calculating offsets...");
    PIXEL_OFFSET = new int[320];
    for(int i=0;i<320;i++) {
	PIXEL_OFFSET[i] = i*320;
    }
}

void clearOffsets() {
    delete [] PIXEL_OFFSET;
}

void createBuffer() {
    log("Creating buffer...");
    videoMemory = MK_FP(0xA000, 0);
    vscreen = farmalloc(64000);
    if (!vscreen) {
        log("Error creando buffer");
        exit(1);
    }
}

void freeBuffer() {
    farfree((void *)vscreen);
}

void FlipScreen(void far* origen, void far* destino)
{
    unsigned int address1 = FP_SEG(origen);
    unsigned int address2 = FP_SEG(destino);
    asm {
        push ds
        mov ds, [address1]
        xor si, si
        mov es, [address2]
        xor di, di
        mov cx, 64000
        rep movsb
        pop ds
    }
}

//Funciones públicas

/*
    Inicializa el modo gráfico en modo 13h
    Además inicializa buffer para hacer el dibujado y precalcula offsets de memoria
*/
void startGraphicsMode() {
    log("Starting graphics mode...");
    createBuffer();
    calculateOffsets();
    setVideoMode(0x13);
}

/*
    Cambia el modo gráfico a modo texto, y elimina buffers y vectores precalculados
*/
void shutdownGraphicsMode() {
    log("Closing graphics mode...");
    setVideoMode(0x3);
    clearOffsets();
    freeBuffer();
}

/*
    Escribe un color específico a toda la memoria de video
*/
void clearScreen (char color )
{
    // address contiene el segmento de memoria del buffer
    // Se usan dos operaciones para copiar todo a la memoria:
    // rep repite la operacion las veces indicadas en el registro CX, en este caso 64000
    // stosb guarda el contenido de AL a la dirección ES:DI, incrementando DI después de cada copia
	unsigned int address = FP_SEG(vscreen);
    asm {
      	mov ax, [address]
      	mov es, ax
      	xor di, di // Inicializa a cero di
      	mov cx, 64000 
      	mov al, [color]
      	rep stosb 
    }
}

void fillRect(int x, int y, int width, int height, char color) {
	unsigned int address = FP_SEG(vscreen);

	int end = y + height;
	for (int i = y; i < end; i++) {	
   		unsigned int offset_pixel =  PIXEL_OFFSET[i] + x;
   		asm {
        	mov es, [address]
        	mov di, [offset_pixel]
   		    mov al, [color]
			mov cx, [width]
	        rep stosb 
 		}
	}
}


void switchBuffer() {
    FlipScreen(vscreen, videoMemory);
    //_fmemcpy(vscreen, videoMemory, 64000);

}

void putPixel(int x, int y, char color) {
    unsigned int offset_pixel =  PIXEL_OFFSET[y] + x;
    unsigned int address = FP_SEG(vscreen);
    asm {
        mov es, [address]
        mov di, [offset_pixel]
        mov al, [color]
        mov es:[di], al
    }
}
