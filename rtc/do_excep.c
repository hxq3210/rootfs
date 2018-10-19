#include <lib.h>

#define DEFINE_DO_SVC(n) \
	void do_svc_##n(void)\
	{\
		printf("svc #%d ...\n", n);\
	}

void do_unde(void)
{
	printf("undefine instrunction exception occur...\n");
}

DEFINE_DO_SVC(9527)
DEFINE_DO_SVC(7788)

void do_svc(u32 num)
{
	switch (num) {
		case 9527:
			do_svc_9527();
			break;
		case 7788:
			do_svc_7788();
			break;
		default:
			break;
	}
}


void do_prefetch_abt(void)
{
	printf("prefetch abort exception ocurr...\n");
}

void do_data_abt(void)
{
	printf("data abort exception ocurr...\n");
}



