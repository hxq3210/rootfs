
.align 2
.text
.global _start

_start:
	stmfd sp!, {r0-r12, lr}

	bl entry 

	ldmfd sp!, {r0-r12, pc}





	




