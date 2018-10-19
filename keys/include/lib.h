#ifndef MILLET_LIB_H_
#define MILLET_LIB_H_

typedef unsigned int u32;
typedef unsigned char u8;

#define udelay(n) (((void (*)(u32))0x43e26480)(n))
#define printf(...) (((int (*)(const char *, ...))0x43e11a2c)(__VA_ARGS__))

extern u32 ioread32(u32 add);
extern void iowrite32(u32 v, u32 add);

extern u8 ioread8(u32 add);
extern void iowrite8(u8 v, u32 add);

#endif
