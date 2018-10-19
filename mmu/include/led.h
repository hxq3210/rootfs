#ifndef TINY4412_LED_H_
#define TINY4412_LED_H_

#include <lib.h>

#define GPM4CON 0x110002e0
#define GPM4DAT 0x110002e4

extern void led_init(void);
extern void led_on(int n);
extern void led_off(int n);

#endif
