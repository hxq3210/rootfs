
#include <timer.h>
#include <irq.h>
#include <lcd.h>

#define USPERSEC 1000000UL
#define LIMIT_UP 	50
#define LIMIT_DOWN 	0

int freq;
int flag = 1;

int pic_num;

void set_hz(u32 hz)
{
	u32 cnt;

	cnt = USPERSEC/hz;
	write32(cnt, TCNTB0);
	write32(cnt>>1, TCMPB0);
}

void do_timer0(void)
{
	u32 tmp;

	tmp = read32(TINT_CSTAT);
	if (tmp & (1 << 5)) {
		if (flag == 1) {
			freq++;
			if (freq > LIMIT_UP) {
				flag = 0;
				freq--;
			} 
		} else {
			freq--;
			if (freq <= LIMIT_DOWN) {
				flag = 1;
				freq++;
			}
		}

		set_hz(freq);

		write32(tmp, TINT_CSTAT);	
	}
}


void pwm0_init(u32 hz)
{
	u32 tmp;
	u32 cnt;

	freq = hz;

	/*设置GPD0的0引脚为TOUT0专用*/
	tmp = read32(GPD0CON);
	tmp &= ~0xf;
	tmp |= 0x2;
	write32(tmp, GPD0CON);

	/*设置TIMER0的第一级分频因子:99*/	
	tmp = read32(TCFG0);
	tmp &= ~0xff;
	tmp |= 99;
	write32(tmp, TCFG0);

	/*设置TIMER0的第二级分频因子: 1/1*/	
	tmp = read32(TCFG1);
	tmp &= ~0xf;
	write32(tmp, TCFG1);

	cnt = USPERSEC/hz;
	write32(cnt, TCNTB0);
	write32(cnt>>1, TCMPB0);

	/*清TCON的第4位*/
	tmp = read32(TCON);
	tmp &= ~0xf;
	write32(tmp, TCON);

	/*设置手动更新和自动加载*/
	tmp = read32(TCON);
	tmp |= (1 << 1) | (1 << 3);
	write32(tmp, TCON);

	tmp = read32(TCON);
	tmp &= ~(1 << 1);
	write32(tmp, TCON);

	tmp = read32(TCON);
	tmp |= (1 << 0);
	write32(tmp, TCON);

	/*使能timer0的中断*/
	tmp = read32(TINT_CSTAT);
	tmp |= 1 << 0;
	write32(tmp, TINT_CSTAT);

#define TIMER0_ID 69
	gic_cpu0_init(TIMER0_ID, 0, do_timer0);
}

void do_timer4(void)
{
	u32 tmp;

	tmp = read32(TINT_CSTAT);
	if (tmp & (1 << 9)) {
		pic_num++;
		if (pic_num >= 20) {
			pic_num = 0;
		}
		printf("please enjoy pic%d ...\n", pic_num);
		change_win0_add(WIN0FRAMBUF0 + pic_num*SZ*4);	
		write32(tmp, TINT_CSTAT);	
	}
}

void timer4_init(u32 us)
{
	u32 tmp;

	pic_num = 0;

	/*设置TIMER4的第一级分频因子:99*/	
	tmp = read32(TCFG0);
	tmp &= ~(0xff << 8);
	tmp |= 99 << 8;
	write32(tmp, TCFG0);

	/*设置TIMER0的第二级分频因子: 1/1*/	
	tmp = read32(TCFG1);
	tmp &= ~(0xf << 16);
	write32(tmp, TCFG1);

	write32(us, TCNTB4);

	/*清TCON的20,21,22位*/
	tmp = read32(TCON);
	tmp &= ~(0x7 << 20);
	write32(tmp, TCON);

	/*设置手动更新和自动加载*/
	tmp = read32(TCON);
	tmp |= (1 << 21) | (1 << 22);
	write32(tmp, TCON);

	tmp = read32(TCON);
	tmp &= ~(1 << 21);
	write32(tmp, TCON);

	tmp = read32(TCON);
	tmp |= (1 << 20);
	write32(tmp, TCON);

	/*使能timer4的中断*/
	tmp = read32(TINT_CSTAT);
	tmp |= 1 << 4;
	write32(tmp, TINT_CSTAT);

#define TIMER4_ID 73 
	gic_cpu0_init(TIMER4_ID, 0, do_timer4);
}
