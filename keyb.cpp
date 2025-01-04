#include "keyb.h"
#include <dos.h>
#include <stdio.h>
#include "log.h"

unsigned char normal_keys[0x60];
unsigned char extended_keys[0x60];

static void interrupt (*old_keyb_int)(...) = NULL;
static void interrupt keyb_interrupt(...) {
    static unsigned char buffer;
    unsigned char rawcode;
    unsigned char make_break;
    int scancode;

    rawcode = inp(0x60); /* read scancode from keyboard controller */
    make_break = !(rawcode & 0x80); /* bit 7: 0 = make, 1 = break */
    scancode = rawcode & 0x7F;
    if (buffer == 0xE0) { /* second byte of an extended key */
        if (scancode < 0x60) {
            extended_keys[scancode] = make_break;
        }
        buffer = 0;
    } else if (buffer >= 0xE1 && buffer <= 0xE2) {
        buffer = 0; /* ingore these extended keys */
    } else if (rawcode >= 0xE0 && rawcode <= 0xE2) {
        buffer = rawcode; /* first byte of an extended key */
    } else if (scancode < 0x60) {
        normal_keys[scancode] = make_break;
    }
    outp(0x20, 0x20);
    (*old_keyb_int)();
}

void startKeyboardDetector() {
    old_keyb_int = getvect(0x09);
    setvect(0x09, keyb_interrupt);
}

void shutdownKeyboardDetector() {
    if (old_keyb_int != NULL) {
        setvect(0x09, old_keyb_int);
        old_keyb_int = NULL;
    }
}

int keyPressed(char scancode) {
    if(normal_keys[scancode] == 1) {
        return 1;
    } else {
        return 0;
    }
}
