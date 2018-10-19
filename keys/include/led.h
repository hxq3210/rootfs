#ifndef MILLET_LED_H_
#define MILLET_LED_H_

#include <lib.h>

extern void led_init(void);
extern void led_on(int n);
extern void led_off(int n);
extern void led_reverse_control(int n);

#define GPM4CON 0x110002e0
#define GPM4DAT 0x110002e4

#endif
