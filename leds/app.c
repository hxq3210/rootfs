#include <led.h>

void app_start(void)
{
	int i, j;

	led_init();

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
}
