#include <uart.h>
#include <stdarg.h>

/*串口0的初始化*/
void uart0_init(void)
{
	u32 val;

	/*设置GPA0[0:1]引脚为串口0专用的收发引脚*/
	val = read32(GPA0CON);
	val &= ~0xff;
	val |= 0x22;
	write32(val, GPA0CON);

	/*设置串口传输数据的一帧对应的数据位为
	  8位，1位停止位，无奇偶校验位*/
	write32(0x3, ULCONn);

	/*选择串口收发的模式为polling模式*/
	write32(0x5, UCONn);

	/*选择传输的模式为非FIFO模式*/	
	write32(0x0, UFCONn);

	/*禁用硬件流控*/
	write32(0x0, UMCONn);

	/*设置波特率为115200， 根据手册1399的公式推出*/
	write32(53, UBRDIVn);
	write32(4, UFRACVALn);
}

void uputchar(int ch)
{
	/*等待发送缓存寄存器无要发送的数据*/
	while (!(read32(UTRSTATn) & 0x2)) {
		;
	}

	write8(ch, UTXHn);

	if (ch == '\n') {
		uputchar('\r');
	}
}

/*从串口接收一个字节的数据*/
int ugetchar(void)
{
	int val;

	/*等待串口控制器接收到有效数据*/
	while (!(read32(UTRSTATn) & 0x1)) {
		; 
	}

	val = read8(URXHn);
	if (val == '\r') {
		val = '\n';
	}

	uputchar(val);

	return val;
}


char *ugets(char *buf)
{
	int ch;

	char *tmp = buf;

	while ((ch = ugetchar()) != '\n') {
		*tmp++ = ch;
	}

	*tmp = '\0';

	return buf;
}

void uputs(const char *buf)
{
	while (*buf) {
		uputchar(*buf);
		buf++;
	}
}

/*93  --> "5d"*/
void xtoa(int n, char *buf)
{
	int i;
	if (n < 16) {
		if (n < 10) {
			buf[0] = '0' + n;
		} else {
			buf[0] = n - 10 + 'a';
		}
		buf[1] = '\0';

		return;
	}	

	xtoa(n/16, buf);

	for (i = 0; buf[i] != '\0'; i++);

	if ((n%16) < 10) {
		buf[i] = (n%16) + '0';
	} else {
		buf[i] = (n%16) - 10 + 'a';
	}

	buf[i+1] = '\0';
}

/*93 --> "93" */
void itoa(int n, char *buf)
{
	int i;

	if (n < 10) {
		buf[0] = n + '0';
		buf[1] = '\0';
		return;
	}

	itoa(n/10, buf);

	for (i = 0; buf[i] != '\0'; i++) {
		;
	}

	buf[i] = (n%10) + '0';
	buf[i+1] = '\0';
}

void uprintf(const char *fmt, ...)
{
	int val;
	va_list va;
	char buf[32];

	va_start(va, fmt);

	while (*fmt) {
		if (*fmt == '%') {
			fmt++;
			switch (*fmt) {
			case 'c':
				uputchar(va_arg(va, int));
				break;
			case 'd':
				val = va_arg(va, int);
				if (val < 0) {
					uputchar('-');
					val = 0 - val;
				}
				itoa(val, buf);
				uputs(buf);
				break;
			case 'x':
				val = va_arg(va, int);
				xtoa(val, buf);
				uputs(buf);
				break;
			case 's':
				uputs(va_arg(va, char *));
				break;
			default:
				break;
			}
		} else {
			uputchar(*fmt);
		}

		fmt++;
	}
}
