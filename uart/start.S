
.text
.align 2
.global _start

_start:
	push {r0-r12, lr}

	bl app_start

	pop {r0-r12, pc}
	
