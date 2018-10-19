#ifndef MILLET_MMU_H_
#define MILLET_MMU_H_

#include <lib.h>

#define mmu_create_descriptor(t, v, p)  \
	t[v>>20] = ((p&0xfff00000) | 0x2)		

extern void mmu_init(int *t);

#endif
