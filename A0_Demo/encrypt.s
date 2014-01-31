	.file	"encrypt.c"
	.arch msp430g2553
	.cpu 430
	.mpy none

.global	key
	.section	.rodata
.LC0:
	.string	"____________________"
	.data
	.p2align 1,0
	.type	key,@object
	.size	key,2
key:
	.word	.LC0
.global	my_shell_cmds
	.section	.rodata
.LC1:
	.string	"help"
.LC2:
	.string	"list available commands"
.LC3:
	.string	"args"
.LC4:
	.string	"print back given arguments"
.LC5:
	.string	"encrypt"
.LC6:
	.string	"encrpy a string"
	.data
	.p2align 1,0
	.type	my_shell_cmds,@object
	.size	my_shell_cmds,2
my_shell_cmds:
	.byte	3
	.skip 1,0
	.word	.LC1
	.word	.LC2
	.word	shell_cmd_help
	.word	.LC3
	.word	.LC4
	.word	shell_cmd_argt
	.word	.LC5
	.word	.LC6
	.word	shell_cmd_encr
	.section	.rodata
.LC7:
	.string	"%s: %s\n\r"
	.text
	.p2align 1,0
.global	shell_cmd_help
	.type	shell_cmd_help,@function
/***********************
 * Function `shell_cmd_help' 
 ***********************/
shell_cmd_help:
	push	r4
	mov	r1, r4
	add	#2, r4
	sub	#4, r1
	mov	r15, -4(r4)
	mov	#0, -6(r4)
	jmp	.L2
.L3:
	mov	-6(r4), r14
	mov	r14, r15
	rla	r15
	add	r14, r15
	rla	r15
	add	#my_shell_cmds+4, r15
	mov	@r15, r13
	mov	-6(r4), r14
	mov	r14, r15
	rla	r15
	add	r14, r15
	rla	r15
	add	#my_shell_cmds+2, r15
	mov	@r15, r15
	push	r13
	push	r15
	push	#.LC7
	call	#cio_printf
	add	#6, r1
	add	#1, -6(r4)
.L2:
	mov.b	&my_shell_cmds, r15
	mov.b	r15, r15
	cmp	r15, -6(r4)
	jl	.L3
	mov	#0, r15
	add	#4, r1
	pop	r4
	ret
.Lfe1:
	.size	shell_cmd_help,.Lfe1-shell_cmd_help
;; End of function 

	.section	.rodata
.LC8:
	.string	"args given:\n\r"
.LC9:
	.string	" - %s\n\r"
	.text
	.p2align 1,0
.global	shell_cmd_argt
	.type	shell_cmd_argt,@function
/***********************
 * Function `shell_cmd_argt' 
 ***********************/
shell_cmd_argt:
	push	r4
	mov	r1, r4
	add	#2, r4
	sub	#4, r1
	mov	r15, -4(r4)
	mov	#.LC8, r15
	call	#cio_print
	mov	#0, -6(r4)
	jmp	.L5
.L6:
	mov	-6(r4), r15
	rla	r15
	rla	r15
	rla	r15
	rla	r15
	add	#2, r15
	add	-4(r4), r15
	push	r15
	push	#.LC9
	call	#cio_printf
	add	#4, r1
	add	#1, -6(r4)
.L5:
	mov	-4(r4), r15
	mov.b	@r15, r15
	mov.b	r15, r15
	cmp	r15, -6(r4)
	jl	.L6
	mov	#0, r15
	add	#4, r1
	pop	r4
	ret
.Lfe2:
	.size	shell_cmd_argt,.Lfe2-shell_cmd_argt
;; End of function 

	.section	.rodata
.LC10:
	.string	"ERROR, string to encrypt is too long\n\r"
.LC11:
	.string	"encrypted string: %s\n\r"
	.text
	.p2align 1,0
.global	shell_cmd_encr
	.type	shell_cmd_encr,@function
/***********************
 * Function `shell_cmd_encr' 
 ***********************/
shell_cmd_encr:
	push	r4
	mov	r1, r4
	add	#2, r4
	add	#llo(-26), r1
	mov	r15, -4(r4)
	mov	-4(r4), r15
	add	#2, r15
	mov	r15, r14
	mov	r14, r15
	sub	#1, r15
.L8:
	add	#1, r15
	cmp.b	#0, @r15
	jne	.L8
	sub	r14, r15
	cmp	#21, r15
	jlo	.L9
	mov	#.LC10, r15
	call	#cio_print
	mov	#llo(-1), r15
	jmp	.L10
.L9:
	mov	-4(r4), r14
	add	#2, r14
	mov	r4, r15
	add	#llo(-26), r15
	mov	#20, r13
	call	#strncpy
	mov	#0, -28(r4)
	jmp	.L11
.L13:
	mov	r4, r15
	add	#llo(-26), r15
	add	-28(r4), r15
	mov.b	@r15, r14
	mov	&key, r13
	mov	-28(r4), r15
	add	r13, r15
	mov.b	@r15, r15
	xor.b	r15, r14
	mov	r4, r15
	add	#llo(-26), r15
	add	-28(r4), r15
	mov.b	r14, @r15
	add	#1, -28(r4)
.L11:
	mov	-28(r4), r13
	mov	r4, r14
	add	#llo(-26), r14
	mov	r14, r15
	sub	#1, r15
.L12:
	add	#1, r15
	cmp.b	#0, @r15
	jne	.L12
	sub	r14, r15
	cmp	r15, r13
	jlo	.L13
	mov	r4, r15
	add	#llo(-26), r15
	push	r15
	push	#.LC11
	call	#cio_printf
	add	#4, r1
	mov	#0, r15
.L10:
	add	#26, r1
	pop	r4
	ret
.Lfe3:
	.size	shell_cmd_encr,.Lfe3-shell_cmd_encr
;; End of function 

	.p2align 1,0
.global	shell_process
	.type	shell_process,@function
/***********************
 * Function `shell_process' 
 ***********************/
shell_process:
	push	r4
	mov	r1, r4
	add	#2, r4
	sub	#2, r1
	mov	r15, -4(r4)
	mov	-4(r4), r14
	mov	#my_shell_cmds, r15
	call	#shell_process_cmds
	add	#2, r1
	pop	r4
	ret
.Lfe4:
	.size	shell_process,.Lfe4-shell_process
;; End of function 

	.section	.rodata
.LC12:
	.string	"$ "
.LC13:
	.string	"\n\n\r"
.LC14:
	.string	"ERROR, unknown command given\n\r"
.LC15:
	.string	"ERROR, an arguement is too lengthy\n\r"
.LC16:
	.string	"ERROR, too many arguements given\n\r"
.LC17:
	.string	"\n"
	.section	.init9,"ax",@progbits
	.p2align 1,0
.global	main
	.type	main,@function
/***********************
 * Function `main' 
 ***********************/
main:
	mov	r1, r4
	add	#2, r4
	add	#llo(-94), r1
	mov	#23168, &__WDTCTL
	mov.b	&__CALBC1_1MHZ, r15
	mov.b	r15, &__BCSCTL1
	mov.b	&__CALDCO_1MHZ, r15
	mov.b	r15, &__DCOCTL
	mov	#9600, r15
	call	#serial_init
	eint
.L25:
	mov	#0, -96(r4)
	mov	r4, r15
	add	#llo(-93), r15
	mov	#90, r14
	mov	r14, r13
	mov	#0, r14
	call	#memset
	mov	#.LC12, r15
	call	#cio_print
	call	#cio_getc
	mov.b	r15, -94(r4)
	jmp	.L16
.L19:
	cmp.b	#8, -94(r4)
	jne	.L17
	cmp	#0, -96(r4)
	jeq	.L18
	add	#llo(-1), -96(r4)
	mov	r4, r15
	add	#llo(-93), r15
	add	-96(r4), r15
	mov.b	#0, @r15
	mov.b	#8, r15
	call	#cio_printc
	mov.b	#32, r15
	call	#cio_printc
	mov.b	#8, r15
	call	#cio_printc
	jmp	.L18
.L17:
	mov	r4, r15
	add	#llo(-93), r15
	add	-96(r4), r15
	mov.b	-94(r4), @r15
	add	#1, -96(r4)
	mov.b	-94(r4), r15
	call	#cio_printc
.L18:
	call	#cio_getc
	mov.b	r15, -94(r4)
.L16:
	cmp.b	#13, -94(r4)
	jne	.L19
	mov	#.LC13, r15
	call	#cio_print
	mov	r4, r15
	add	#llo(-93), r15
	call	#shell_process
	cmp	#llo(-15), r15
	jeq	.L22
	cmp	#llo(-14), r15
	jeq	.L23
	cmp	#llo(-16), r15
	jeq	.L21
	jmp	.L26
.L23:
	mov	#.LC14, r15
	call	#cio_print
	jmp	.L24
.L22:
	mov	#.LC15, r15
	call	#cio_print
	jmp	.L24
.L21:
	mov	#.LC16, r15
	call	#cio_print
	jmp	.L24
.L26:
	nop
.L24:
	mov	#.LC17, r15
	call	#cio_print
	jmp	.L25
.LIRD0:
.Lfe5:
	.size	main,.Lfe5-main
;; End of function 

	.text
	.p2align 1,0
.global	Timer0_A0
	.type	Timer0_A0,@function
/***********************
 * Interrupt Vector 9 Service Routine `Timer0_A0' 
 ***********************/
Timer0_A0:
.global	__isr_9
__isr_9:
	push	r4
	mov	r1, r4
	add	#2, r4
	pop	r4
	reti
.Lfe6:
	.size	Timer0_A0,.Lfe6-Timer0_A0
;; End of function 

