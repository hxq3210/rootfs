#ifndef MILLET_UART_H_
#define MILLET_UART_H_

#include <lib.h>

/* 设置ＵＡＲＴ的协议配置:　115200, 8N1*/
void uart0_init(void);
void u0_putchar(int n);
int u0_getchar(void);
void u0_puts(const char *buf);
char* u0_gets(char *buf);
//void u0_pri0tf(co0st char *, ...);

#define ULCON0 		0x13800000 
#define UCON0  		0x13800004 
#define UFCON0 		0x13800008 
#define UMCON0 		0x1380000C 
#define UTRSTAT0	0x13800010 
#define UERSTAT0	0x13800014 
#define UFSTAT0 	0x13800018 
#define UMSTAT0 	0x1380001C 
#define UTXH0 		0x13800020 
#define URXH0 		0x13800024 
#define UBRDIV0 	0x13800028 
#define UFRACVAL0 	0x1380002C 
#define UINTP0 		0x13800030 
#define UINTSP0 	0x13800034 
#define UINTM0 		0x13800038

#define GPA0CON		0x11400000

#endif
