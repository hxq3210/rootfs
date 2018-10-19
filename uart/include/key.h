#ifndef MILLET_KEY_H_
#define MILLET_KEY_H_


#include <lib.h>

extern void key_init(void);
extern void key_check_dnup(void (*handler)(int n, int stat));

#define GPX3CON 0x11000c60
#define GPX3DAT 0x11000c64

enum {
	UP,DOWN
};

#endif
