#include <key.h>

void key_init(void)
{
	u32 tmp;

	/*设置GPX3[2:5]引脚为输入功能*/
	tmp = ioread32(GPX3CON);
	tmp &= ~(0xffff << 8);
	iowrite32(tmp, GPX3CON);
}

void key_check_dnup(void (*handler)(int n, int stat))
{
	u8 stat;
	int n;
	/*等待按下*/
	do {
		stat = ioread8(GPX3DAT);
		stat >>= 2;
		stat &= 0xf;
	} while (stat == 0xf);

	udelay(30000);
	
	do {
		stat = ioread8(GPX3DAT);
		stat >>= 2;
		stat &= 0xf;
	} while (stat == 0xf);


	switch (stat) {
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
		default:
			break;		
	}

	/*处于按下某个按键的按下状态*/
	handler(n, DOWN);

	
	do {
		stat = ioread8(GPX3DAT);
		stat >>= 2;
		stat &= 0xf;
	} while (stat != 0xf);

	
	/*处于按下某个按键的抬起状态*/
	handler(n, UP);
}
