#ifndef TINY4412_UART_H_
#define TINY4412_UART_H_

#include <lib.h>

#define GPA0CON		0x11400000

#define ULCONn		0x13800000 
#define UCONn 		0x13800004 
#define UFCONn		0x13800008 
#define UMCONn		0x1380000C 
#define UTRSTATn	0x13800010 
#define UERSTATn	0x13800014 
#define UFSTATn 	0x13800018 
#define UMSTATn 	0x1380001C 
#define UTXHn 		0x13800020 
#define URXHn 		0x13800024 
#define UBRDIVn 	0x13800028 
#define UFRACVALn 	0x1380002C 
#define UINTPn 		0x13800030 
#define UINTSPn 	0x13800034 
#define UINTMn 		0x13800038 

extern void uart0_init(void);
extern int ugetchar(void);
extern void uputchar(int ch);
extern char *ugets(char *buf);
extern void uputs(const char *buf);
extern void uprintf(const char *fmt, ...);

#endif
