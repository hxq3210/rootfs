#include <key.h>

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

