#include <lcd.h>

static void lcd_gpio_set(void)
{
	u32 val;

	write32(0x22222222, GPF0CON);
	write32(0x22222222, GPF1CON);
	write32(0x22222222, GPF2CON);

	val = read32(GPF3CON);
	val &= ~0xffff;
	val |= 0x2222;
	write32(val, GPF3CON);
}

static void window1_init(void)
{
	u32 val, sz;

	val = (1 << 15) | (0xb << 2) | (0x1 << 0);
	sz = 800*480;
	
	/*设置了window1使用BUF0作为要显示的数据，设置窗口支持的数据格式，使能窗口*/
	write32(val, WINCON1);

	/*设置window0显示区域的左上角坐标*/
	write32(0, VIDOSD1A);

	/*设置window0显示区域的右下角坐标*/
	val = (799 << 11) | (479 << 0);
	write32(val, VIDOSD1B);

	val = read32(VIDOSD1C);
	val &= ~(0xffffff);
	val |= 0xffffff;
	write32(val, VIDOSD1C);

	/*设置window0要显示的图像所占内存空间的大小，单位为字*/
	write32(sz, VIDOSD1D);

	/*设置了window1要显示的数据所在内存的起始地址和结束地址*/
	write32(WIN1FRAMBUF0, VIDW01ADD0B0);
	write32(WIN1FRAMBUF0 + sz*4, VIDW01ADD1B0);

	/*窗口0选择通道0，通道0选择窗口0*/
	val = read32(WINCHMAP2);
	val &= ~((0x7 << 19) | (0x7 << 3));
	val |= ((0x2 << 19) | (0x2 << 3));
	write32(val, WINCHMAP2);
	
	/*禁用本地通道0， 使能DMA的通道0*/
	val = read32(SHADOWCON);
	val &= ~(1 << 6);
	val |= 0x1 << 1;
	write32(val, SHADOWCON);

	/*设置window1关键颜色为红色*/
	write32(1 << 25, W1KEYCON0);
	write32(0xff0000, W1KEYCON1);
}

static void window0_init(void)
{
	u32 val, sz;

	val = (1 << 15) | (0xb << 2) | (0x1 << 0);
	sz = 800*480;
	
	/*设置了window0使用BUF0作为要显示的数据，设置窗口支持的数据格式，使能窗口*/
	write32(val, WINCON0);

	/*设置window0显示区域的左上角坐标*/
	write32(0, VIDOSD0A);

	/*设置window0显示区域的右下角坐标*/
	val = (799 << 11) | (479 << 0);
	write32(val, VIDOSD0B);

	/*设置window0要显示的图像所占内存空间的大小，单位为字*/
	write32(sz, VIDOSD0C);

	/*设置了window0要显示的数据所在内存的起始地址和结束地址*/
	write32(WIN0FRAMBUF0, VIDW00ADD0B0);
	write32(WIN0FRAMBUF0 + sz*4, VIDW00ADD1B0);

	/*窗口0选择通道0，通道0选择窗口0*/
	val = read32(WINCHMAP2);
	val &= ~((0x7 << 16) | (0x7 << 0));
	val |= ((0x1 << 16) | (0x1 << 0));
	write32(val, WINCHMAP2);
	
	/*禁用本地通道0， 使能DMA的通道0*/
	val = read32(SHADOWCON);
	val &= ~(1 << 5);
	val |= 0x1 << 0;
	write32(val, SHADOWCON);
}

void lcd_init(void)
{
	u32 val;
	/*设置LCD和DISPLAY CONTROLER相连的GPIO为显示控制器专用*/
	lcd_gpio_set();

	/*P880*/
	val = read32(LCDBLK_CFG);
	val |= 1 << 1;
	write32(val, LCDBLK_CFG);

	/*CMU提供给显示控制器的时钟设置*/
	/*CLK_FIMD0选择MPLL_USER_T*/
	val = read32(CLK_SRC_LCD0);
	val &= ~0xf;
	val |= 0x6;
	write32(val, CLK_SRC_LCD0);

	/*选择时钟的分频因子为7*/
	val = read32(CLK_DIV_LCD);
	val &= ~0xf;
	val |= 0x7;
	write32(val, CLK_DIV_LCD);

	/*设置水平、垂直同步信号翻转，打点时钟为上升边沿有效*/
	val = (1 << 9) | (1 << 7) | (1 << 6) | (1 << 5); //bit 9 ??
	write32(val, VIDCON1);

	/*设置垂直同步信号的时序*/
	val =(12 << 16) | (21 << 8) | (9 << 0);
	write32(val, VIDTCON0);

	/*设置水平同步信号的时序*/
	val =(25 << 16) | (209 << 8) | (19 << 0);
	write32(val, VIDTCON1);

	/*和显示控制器相连接的LCD的分辨率*/
	val = (479 << 11) | (799);
	write32(val, VIDTCON2);

	window0_init();
	window1_init();

	/*对CMU提供的时钟进行分频得到33.3MHz， 同时使能显示*/
	val = (0x2 << 6) | (1 << 1) | (1 << 0);
	write32(val, VIDCON0);
}

void draw_point(int x, int y, int col, int win)
{
	if (win == 0) {
		*(int *)(WIN0FRAMBUF0 + (y*800 + x)*4) = col;
	} else {
		*(int *)(WIN1FRAMBUF0 + (y*800 + x)*4) = col;
	}
}


