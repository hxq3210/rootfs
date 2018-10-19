#include <led.h>

void led_init(void)
{
	u32 tmp;
	u8 mpt;

	/*设置GPM4[0:3]引脚为输出*/
	tmp = ioread32(GPM4CON);
	tmp &= ~0xffff;
	tmp |= 0x1111;
	iowrite32(tmp, GPM4CON);

	/*默认通过GPM4[0:3]引脚输出高电平，led灭*/
	mpt = ioread8(GPM4DAT);
	mpt |= 0xf;
	iowrite8(mpt, GPM4DAT);
}

void led_on(int n)
{
	u8 tmp;

	if (n >= 0 && n <= 3) {
		tmp = ioread8(GPM4DAT);
		tmp &= ~(1 << n);
		iowrite8(tmp, GPM4DAT);
	}
}

void led_off(int n)
{
	u8 tmp;

	if (n >= 0 && n <= 3) {
		tmp = ioread8(GPM4DAT);
		tmp |= (1 << n);
		iowrite8(tmp, GPM4DAT);
	}
}


void led_reverse_control(int n)
{
	u8 tmp;

	if (n >= 0 && n <= 3) {
		tmp = ioread8(GPM4DAT);
		tmp ^= (1 << n);
		iowrite8(tmp, GPM4DAT);
	}
	
}
