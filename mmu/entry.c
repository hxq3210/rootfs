#include <led.h>
#include <key.h>
#include <lib.h>
#include <uart.h>
#include <backlight.h>
#include <lcd.h>
#include <mmu.h>

#define MMU_MAP_TABLE 0x66000000

void entry(void)
{

	int *t = (int *)MMU_MAP_TABLE;
	int *p = (void *)0x7ab95270;

	*p = 0x95273856;

	mmu_create_descriptor(t, 0xfff00000, 0x7ab00000);
	mmu_create_descriptor(t, 0xabc00000, 0x7ab00000);
	mmu_create_descriptor(t, 0xbbc00000, 0x7ab00000);
	mmu_create_descriptor(t, 0xcbc00000, 0x7ab00000);

	mmu_init(t);

	printf("*p	= %#x\n", *p);
	printf("*((int *)0xfff95270)	= %#x\n", *((int *)0xfff95270));
	printf("*((int *)0xabc95270)	= %#x\n", *((int *)0xabc95270));
	printf("*((int *)0xbbc95270)	= %#x\n", *((int *)0xbbc95270));
	printf("*((int *)0xcbc95270)	= %#x\n", *((int *)0xcbc95270));
}
