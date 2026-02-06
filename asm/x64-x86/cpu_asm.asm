PUBLIC asm_read_tsc
PUBLIC asm_get_sp
PUBLIC asm_pause

; Get CPU time
.code
asm_read_tsc PROC
	rdtsc
	shl rdx, 32
	or rax, rdx
	ret
asm_read_tsc ENDP

; Read segment reg
asm_read_fs PROC
	mov rax, fs
	ret
asm_read_fs ENDP

; Get Stack Ptr
asm_get_sp PROC
	mov rax, rsp
	ret
asm_get_sp ENDP

; Get Base Ptr
asm_get_bp PROC
	mov rax, rbp
	ret
asm_get_bp ENDP

; Read timestamp ctr
asm_rdtscp PROC
	rdtscp
	shl rdx, 32
	or rax, rdx
	ret
asm_rdtscp ENDP

; Pause CPU
asm_pause PROC
	pause
	ret
asm_pause ENDP

; Mem barrier
asm_mfence PROC
	mfence
	ret
asm_mfence ENDP

; Halt CPU, current testing device doesn't have right kernel level so disregard now
asm_halt PROC
	sti
	hlt
	ret
asm_halt ENDP

; Interrupt
asm_cli PROC
	cli ; clear
	ret
asm_cli ENDP

asm_sti PROC
	sti ; enable
	ret
asm_sti ENDP

; Flags
asm_read_flags PROC
	pushfq
	pop rax
	ret
asm_read_flags ENDP

asm_write_flags PROC
	push rax
	popfq
	ret
asm_write_flags ENDP

; Atomic
asm_xchg_r32 PROC
	xchg eax, [rdi] ; swaps rax with [rdi]
	ret
asm_xchg_r32 ENDP

asm_cmpxchg PROC
	lock cmpxchg [rdi], edx ; rax = expected, rdi = ptr, rdx = newval
	ret
asm_cmpxchg ENDP

asm_bsf PROC
	bsf eax, eax ; find first set bit
	ret
asm_bsf ENDP

asm_bsr PROC
	bsr eax, eax ; find last set bit
	ret
asm_bsr ENDP

END