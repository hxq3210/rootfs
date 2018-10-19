#include <adc.h>
#include <irq.h>

void wait_adc_end(void)
{
	u32 tmp;

	do {
		tmp = read32(ADCCON);	
	} while (!(tmp & (1 << 15)));
}

void adc_startup(void)
{
	u32 tmp;

	tmp = read32(ADCCON);
	tmp |= 1;
	write32(tmp, ADCCON);
}

void adc_polling_init(void)
{
	u32 tmp;

	/*选择ADC的精度为12位，使能分频，分频因子为99+1:
	  分频后的工作频率为1MHz*/
	tmp = (1 << 16) | (1 << 14) | (99 << 6);
	write32(tmp, ADCCON);

	/*设置每次转换前的延时对应的PCLK的时钟周期总个数*/
	write32(0xffff, ADCDLY);
	
	/*选择让ADC控制器转换通道0的模拟信号*/
	write8(0x0, ADCMUX);
}

u32 adc_read_by_polling(void)
{
	u32 tmp;

	/*启动开始转换*/
	adc_startup();

	/*等待转换结束*/
	wait_adc_end();

	tmp = read32(ADCDAT);

	return tmp&0xfff;
}

void do_adc(void)
{
	u32 val;

	val = read32(ADCDAT);
	val &= 0xfff;

	printf("adc digital： %d, sample: %dmv\n", 
				val, (val*1800)/4095);

	write8(78, CLRINTADC);
}

void adc_irq_init(void)
{
	u32 tmp;
#define IESR2 0x10440020
	/*选择ADC的精度为12位，使能分频，分频因子为99+1:
	  分频后的工作频率为1MHz*/
	tmp = (1 << 16) | (1 << 14) | (99 << 6);
	write32(tmp, ADCCON);

	/*设置每次转换前的延时对应的PCLK的时钟周期总个数*/
	write32(0xffff, ADCDLY);
	
	/*选择让ADC控制器转换通道0的模拟信号*/
	write8(0x0, ADCMUX);

	tmp = read32(IESR2);
	tmp |= 1 << 19;
	write32(tmp, IESR2);
#define ADCIRQ_ID 42
	gic_cpu0_init(ADCIRQ_ID, 0, do_adc);
}
