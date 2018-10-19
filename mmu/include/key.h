#ifndef TINY4412_KEY_H_
#define TINY4412_KEY_H_

#include <lib.h>

#define GPX3CON 0x11000c60
#define GPX3DAT 0x11000c64

extern void key_init(void);
extern int key_check_downup(void);

#endif
