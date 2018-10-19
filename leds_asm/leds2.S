#define GPM4BASE 0x11000000
#define GPM4CON  0x2e0
#define GPM4DAT  0x2e4

#define UDELAY 0x43e26480

.text
.align 2
.global _start

_start:
	@保存现场
	mov ip, sp
	push {fp, ip, lr, pc}
	sub fp, ip, #4

	@设置GPM4[0:3]引脚为输出功能
	ldr r0, =GPM4BASE
	ldr r1, [r0, #GPM4CON]
	ldr r2, =0xffff
	bic r1, r1, r2
	ldr r2, =0x1111
	orr r1, r1, r2
	str r1, [r0, #GPM4CON]


	@r1对应led的编号
	mov r1, #0
loop:
	@亮序号为r1的灯
	ldr r0, =GPM4BASE
	ldrb r2, [r0, #GPM4DAT]
	mov r3, #1
	lsl r3, r3, r1
	bic r2, r2, r3
	strb r2, [r0, #GPM4DAT]

	bl udelay

	ldr r0, =GPM4BASE
	ldrb r2, [r0, #GPM4DAT]
	mov r3, #1
	lsl r3, r3, r1
	orr r2, r2, r3
	strb r2, [r0, #GPM4DAT]

	add r1, #1
	cmp r1, #4
	moveq r1, #0
	b loop

	@恢复现场
	sub sp, fp, #12
	ldm sp, {fp, sp, pc}

udelay:
	stmfd sp!, {r0-r12, lr}
	
	ldr r0, =500000
	mov lr, pc
	ldr pc, =UDELAY

	ldmfd sp!, {r0-r12, pc}	
