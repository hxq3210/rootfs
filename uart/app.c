#include <led.h>
#include <key.h>

#define N 64

void app_start(void)
{
	int val;
	char buf[N];

	uart0_init();

#if 0
	while ((val = u0_getchar()) != 'q') {
		u0_putchar(val);
		u0_putchar('\n');
	}

	u0_puts("please input a string:\n");
	u0_puts(u0_gets(buf));
	u0_putchar('\n');
#endif
	u0_printf("hello, world!\n");
	u0_printf("hello, world! %d\n", 2018);
	u0_printf("hello, worl%c! %d\n", 'd', 2018);
	u0_printf("hello, world! 0x%x\n", 65535);
	u0_printf("%s! 0x%x\n", "hello, world", 65535);

}
