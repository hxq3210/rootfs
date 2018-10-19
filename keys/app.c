#include <led.h>
#include <key.h>

void do_handler(int n, int stat)
{
	u8 val;

	if (stat == DOWN) {
		led_reverse_control(n-1);
	}

	printf("key %d is %s.\n", n, stat?"down":"up");
}

void app_start(void)
{
	int i;

	led_init();
	key_init();

	while (1) {
		key_check_dnup(do_handler);
	}

#if 0

	while (1) {
		i = 0;
		while (i <= 3) {
			led_on(i);
			udelay(500000);
			i++;
		}

		i--;
		while (i >= 0) {
			led_off(i);
			udelay(500000);
			i--;
		}

		for (j = 0; j < 2; j++) {
			for (i = 0; i <= 3; i++) {
				led_on(i);
			}
			udelay(500000);
			for (i = 0; i <= 3; i++) {
				led_off(i);
			}
			udelay(500000);
		}
	}
#endif
}
