#include <vector.h>
#include <lib.h>
#include <mmu.h>

void create_excep_vector_table(void)
{
	mmu_create_descriptor((u32 *)T, 0xffff0000, VECTOR_BASE);
	mmu_init((u32 *)T);

	mymemcpy((void *)0xffff0000, (void *)_start_add, _end_add - _start_add);
}
