
#include <irq.h>

static handler_t isr[160];

/*中断响应函数*/
void do_irq(void)
{
	int irqid;
	handler_t handler;

	irqid = read32(ICCIAR_CPU0)&0x3ff; 
	handler = isr[irqid];	
	handler();
	write32(irqid, ICCEOIR_CPU0); //清楚GIC已经转发给CPU核心的中断
}

/*
   	1.根据中断源对应的中断号设置GIC的寄存器；
 	2.将具体与中断号对应的中断处理函数与中断号绑定起来;
	3.将CPSR寄存器的第I位清零，使能核心对中断的响应
 */
void gic_cpu0_init(u32 irqid, int level, handler_t handler)
{
	u32 tmp;

	if (irqid > 159) {
		return;
	}

	/*使能GIC和CPU0的接口*/
	write32(0x1, ICCICR_CPU0);

	/*设置CPU0所能接收的中断源的优先级阈值*/
	write32(0xff, ICCPMR_CPU0);

	/*使能GIC控制器对所有中断的监视和转发*/
	write32(0x1, ICDDCR);

	/*设置irqid中断号的优先级*/
	tmp = read32(ICDIPR0_CPU0 + (irqid/4)*4);
	tmp &= ~(0xff << (irqid%4)*8);
	tmp |= (level << (irqid%4)*8);
	write32(tmp, ICDIPR0_CPU0 + (irqid/4)*4);

	/*设置irqid中断号的优先级*/
	tmp = read32(ICDIPTR0_CPU0 + (irqid/4)*4);
	tmp &= ~(0xff << (irqid%4)*8);
	tmp |= (0x1 << (irqid%4)*8);
	write32(tmp, ICDIPTR0_CPU0 + (irqid/4)*4);

	/*使能中断源的ID为irqid的中断*/
	tmp = read32(ICDISER0_CPU0 + (irqid/32)*4);
	tmp |= 0x1 << (irqid%32);
	write32(tmp, ICDISER0_CPU0 + (irqid/32)*4);

	isr[irqid] = handler;

	/*使能核心对中断的响应，将CPSR的第I位清零*/
	__asm__ __volatile__ (
		"mrs r0, cpsr\n"		
		"bic r0, r0, #0x80\n"
		"msr cpsr, r0\n"
	);
}
