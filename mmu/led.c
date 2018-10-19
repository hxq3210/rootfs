#include <led.h>

void led_init(void)
{
	u32 val;

	/*设置GPM4[0:3]引脚为输出功能*/
	val = read32(GPM4CON);
	val &= ~0xffff;
	val |=  0x1111;
	write32(val, GPM4CON);
}

void led_on(int n)
{
	u8 val;

	if ((n >= 0) && (n <= 3)) {
		val = read8(GPM4DAT);	
		val &= ~(1 << n);
		write8(val, GPM4DAT);
	}
}

void led_off(int n)
{
	u8 val;

	if ((n >= 0) && (n <= 3)) {
		val = read8(GPM4DAT);	
		val |= (1 << n);
		write8(val, GPM4DAT);
	}
}
