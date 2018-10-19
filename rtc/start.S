
.align 2
.text
.global _start

_start:
	b reset   				@0x0
	ldr pc, _undef_instruction		@0x4
	ldr pc, _svc_excep			@0x8
	ldr pc, _prefetch_abort			@0xc
	ldr pc, _data_abort			@0x10
	nop					@0x14
	ldr pc, _irq_excep			@0x18
	ldr pc, _fiq_excep			@0x1c
_undef_instruction	: .word undef_instruction
_svc_excep		: .word svc_excep
_prefetch_abort		: .word prefetch_abort
_data_abort		: .word data_abort
_irq_excep		: .word irq_excep
_fiq_excep		: .word fiq_excep

reset:	
	stmfd sp!, {r0-r12, lr}
	bl entry 
	ldmfd sp!, {r0-r12, pc}

undef_instruction:
	stmfd sp!, {r0-r12, lr}
	bl do_unde
	ldmfd sp!, {r0-r12, pc}^

svc_excep:
	stmfd sp!, {r0-r12, lr}
	sub lr, lr, #4
	ldr r0, [lr]
	and r0, r0, #0xffffff
	bl do_svc
	ldmfd sp!, {r0-r12, pc}^

prefetch_abort:
	stmfd sp!, {r0-r12, lr}
	bl do_prefetch_abt
	ldmfd sp!, {r0-r12, pc}^

data_abort:
	sub lr, lr, #4
	stmfd sp!, {r0-r12, lr}
	bl do_data_abt
	ldmfd sp!, {r0-r12, pc}^
	
irq_excep:
	stmfd sp!, {r0-r12, lr}
	bl do_irq
	ldmfd sp!, {r0-r12, lr}
	subs pc, lr, #4
fiq_excep:
	
_end:
_start_add	: .word _start
_end_add	: .word _end

.global _start_add
.global _end_add

	




