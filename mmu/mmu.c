#include <mmu.h>

void mmu_section_map(int *t, int vadd_s, int vadd_e, int padd)
{
	while (vadd_s <= vadd_e) {
		mmu_create_descriptor(t, vadd_s, padd);
		vadd_s 	+= 0x100000;
		padd	+= 0x100000;
	}
}

void mmu_enable(int *t)
{
	__asm__ __volatile__ (
		//P1481
		
		"mcr p15, 0, %[t], c2, c0, 0\n" //转换表的地址写入c2

		"mvn r0, #0x0\n"
		"mcr p15, 0, r0, c3, c0, 0\n" //设置映射后的内存的访问为管理员权限
		
		"mrc p15, 0, r0, c1, c0, 0\n"
		"orr r0, r0, #1\n"
		"orr r0, r0, #(1 << 13)\n" //选择异常矢量基地址为高矢量地址0xffff0000,使能mmu
		"mcr p15, 0, r0, c1, c0, 0\n"

		:
		:[t]"r"(t)		
		:"r0"
	);
}

void mmu_init(int *t)
{
	mmu_section_map(t, 0x0, 0xcd00000, 0x0);
	mmu_section_map(t, 0xce00000, 0x14000000, 0xce00000);
	mmu_section_map(t, 0x40000000, 0x80000000, 0x40000000);

	mmu_enable(t);

	printf("lol...\n");
}	
