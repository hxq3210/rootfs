#include <lib.h>

u32 read32(u32 reg)
{
	return *((volatile u32 *)reg);
}

u16 read16(u32 reg)
{
	return *((volatile u16 *)reg);
}

u8 read8(u32 reg)
{
	return *((volatile u8 *)reg);
}

void write32(u32 val, u32 reg)
{
	*((volatile u32 *)reg) = val;
}

void write16(u16 val, u32 reg)
{
	*((volatile u16 *)reg) = val;
}

void write8(u8 val, u32 reg)
{
	*((volatile u8 *)reg) = val;
}
