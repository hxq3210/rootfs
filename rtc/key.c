#include <key.h>
#include <irq.h>

//设置gpio引脚GPX3[2:5]为输入功能
void key_init(void)
{
	u32 val;

	val = read32(GPX3CON);
	val &= ~(0xffff << 8);
	write32(val, GPX3CON);
}

int key_check_downup(void)
{
	u8 val;
	int n;

	val = read8(GPX3DAT);
	while(((val>>2)&0xf) == 0xf) {
		val = read8(GPX3DAT);
	}

	switch ((val>>2)&0xf) {
		case 0xe:
			n = 1;
			break;
		case 0xd:
			n = 2;
			break;
		case 0xb:
			n = 3;
			break;
		case 0x7:
			n = 4;
			break;
	}

	val = read8(GPX3DAT);
	while(((val>>2)&0xf) != 0xf) {
		val = read8(GPX3DAT);
	}

	return n;
}

/////////////////// EINT //////////////////////////////
static int key_stat = 0xf;

void do_key(void)
{
	u32 tmp;

	tmp = read32(EXT_INT43_PEND);
	write32(tmp, EXT_INT43_PEND);

	tmp >>= 2;
	tmp &= 0xf;

	switch (tmp) {
		case 1:
			if (key_stat&0x1) {
				printf("key 1 is down...\n");
			} else {
				printf("key 1 is up...\n");
			}
			key_stat ^= 1;
			break;
		case 2:
			if (key_stat&0x2) {
				printf("key 2 is down...\n");
			} else {
				printf("key 2 is up...\n");
			}
			key_stat ^= 2;
			break;
		case 4:
			if (key_stat&0x4) {
				printf("key 3 is down...\n");
			} else {
				printf("key 3 is up...\n");
			}
			key_stat ^= 4;
			break;
		case 8:
			if (key_stat&0x8) {
				printf("key 4 is down...\n");
			} else {
				printf("key 4 is up...\n");
			}
			key_stat ^= 8;
			break;
		default:
			break;
	}
}

void key_eint_init(void)
{
	u32 tmp;

	/*设置GPX3[2:5]引脚为外部中断专用*/
	tmp = read32(GPX3CON);
	tmp |= 0xffff << 8;
	write32(tmp, GPX3CON);

	/*设置GPX3[2:5]引脚的中断触发方式为双边沿*/
	tmp = read32(EXT_INT43CON);
	tmp &= ~(0xffff << 8);
	tmp |= 0x4444 << 8;
	write32(tmp, EXT_INT43CON);

	/*设置GPX3[2:5]引脚的滤波使能，数字滤波，滤波宽度*/
	tmp = read32(EXT_INT43_FLTCON0);
	tmp |= 0xffff << 16;
	write32(tmp, EXT_INT43_FLTCON0);
	tmp = read32(EXT_INT43_FLTCON1);
	tmp |= 0xffff << 0;
	write32(tmp, EXT_INT43_FLTCON1);

	/*使能4个按键对应的GPIO的外部中断*/
	tmp = read32(EXT_INT43_MASK);
	tmp &= ~(0xf << 2);
	write32(tmp, EXT_INT43_MASK);

#define KEYIRQ_ID 64	
	gic_cpu0_init(KEYIRQ_ID, 0, do_key);
}
