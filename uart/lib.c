#include <lib.h>

u32 ioread32(u32 add)
{
	return *((u32 volatile *)add);
}

void iowrite32(u32 v, u32 add)
{
	*((u32 volatile *)add) = v;
}

u8 ioread8(u32 add)
{
	return *((u8 volatile *)add);
}

void iowrite8(u8 v, u32 add)
{
	*((u8 volatile *)add) = v;
}
