#ifndef _KEYB_H_
#define _KEYB_H_

#define KEY_ALT 0x38
#define KEY_Q 0x10
#define KEY_W 0x11
#define KEY_A 0x1e
#define KEY_S 0x1f
#define KEY_D 0x20
#define KEY_I 0x17
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_ENTER 0x1C 

void startKeyboardDetector();
void shutdownKeyboardDetector();
int keyPressed(char scancode);

#endif