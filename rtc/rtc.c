
#include <rtc.h>

//101 1001
static u32 bcd2bin(u32 n)
{
	return ((n&0xf) + ((n>>4)&0xf)*10);
}

/*59 --> 89 --> 101 1001*/
static u32 bin2bcd(u32 n)
{
	return (n%10) | ((n/10) << 4);	
}

void rtc_get_time(struct rtc_tm *t)
{
	u8 tmp;

	tmp = read32(BCDYEAR)&0xff;
	t->year = bcd2bin(tmp);

	tmp = read32(BCDMON)&0x1f;
	t->mon = bcd2bin(tmp);
	
	tmp = read32(BCDDAY)&0x3f;
	t->mday = bcd2bin(tmp);

	tmp = read32(BCDHOUR)&0x3f;
	t->hour = bcd2bin(tmp);

	tmp = read32(BCDMIN)&0x7f;
	t->min = bcd2bin(tmp);

	tmp = read32(BCDSEC)&0x7f;
	t->sec = bcd2bin(tmp);

	tmp = read32(BCDDAYWEEK)&0x7;
	t->wday = bcd2bin(tmp);
}
void rtc_set_time(const struct rtc_tm *t)
{
	u32 tmp;

	/*开启对时间的写权限*/
	tmp = read32(RTCCON);
	tmp |= 1;
	write32(tmp, RTCCON);

	tmp = bin2bcd(t->year);
	write32(tmp, BCDYEAR);

	tmp = bin2bcd(t->mon);
	write32(tmp, BCDMON);
	
	tmp = bin2bcd(t->mday);
	write32(tmp, BCDDAY);

	tmp = bin2bcd(t->hour);
	write32(tmp, BCDHOUR);

	tmp = bin2bcd(t->min);
	write32(tmp, BCDMIN);

	tmp = bin2bcd(t->sec);
	write32(tmp, BCDSEC);

	tmp = bin2bcd(t->wday);
	write32(tmp, BCDDAYWEEK);
	
	/*关闭对时间的写权限*/
	tmp = read32(RTCCON);
	tmp &= ~1;
	write32(tmp, RTCCON);
}
