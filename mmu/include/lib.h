#ifndef TINY4412_LIB_H_
#define TINY4412_LIB_H_

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

extern u32 read32(u32 reg);
extern u16 read16(u32 reg);
extern u8 read8(u32 reg);
extern void write8(u8 val, u32 reg);
extern void write16(u16 val, u32 reg);
extern void write32(u32 val, u32 reg);

#define udelay  ((void (*)(int))0x43e26480)
#define printf(...) (((int (*)(const char *, ...))0x43e11a2c)(__VA_ARGS__))

#endif








