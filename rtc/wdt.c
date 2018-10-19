#include <wdt.h>
#include <irq.h>

void do_wdt(void)
{
	printf("watch dog hehe...\n");
	write32(9527, WTCLRINT);
}

void wdt_init_reset(int s)
{
	u32 tmp;

	tmp = 3052*s;
	write32(tmp, WTCNT);
	//write32(tmp, WTDAT);

	tmp = (255 << 8) | (1 << 5) | (3 << 3) | (1 << 0);
	write32(tmp, WTCON);	
#define AUTOMATIC_WDT_RESET_DISABLE	0x10020408
#define MASK_WDT_RESET_REQUEST		0x1002040c
	write32(0, AUTOMATIC_WDT_RESET_DISABLE);
	write32(0, MASK_WDT_RESET_REQUEST);

}

void wdt_init_timer(int s)
{
	u32 tmp;

	tmp = 3052*s;
	write32(tmp, WTCNT);
	write32(tmp, WTDAT);

	tmp = (255 << 8) | (1 << 5) | (3 << 3) | (1 << 2);
	write32(tmp, WTCON);	
#define WDTIRQ  75
	gic_cpu0_init(WDTIRQ, 0, do_wdt);		
}
