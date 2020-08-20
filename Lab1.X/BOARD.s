	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_BOARD_Init
	.p2align	4, 0x90
_BOARD_Init:                            ## @BOARD_Init
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_BOARD_End
	.p2align	4, 0x90
_BOARD_End:                             ## @BOARD_End
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi3:
	.cfi_def_cfa_offset 16
Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi5:
	.cfi_def_cfa_register %rbp
	xorl	%edi, %edi
	callq	_exit
	.cfi_endproc

	.globl	_BOARD_GetPBClock
	.p2align	4, 0x90
_BOARD_GetPBClock:                      ## @BOARD_GetPBClock
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi6:
	.cfi_def_cfa_offset 16
Lcfi7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi8:
	.cfi_def_cfa_register %rbp
	movl	$20000000, %eax         ## imm = 0x1312D00
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_BOARD_GetSysClock
	.p2align	4, 0x90
_BOARD_GetSysClock:                     ## @BOARD_GetSysClock
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi9:
	.cfi_def_cfa_offset 16
Lcfi10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi11:
	.cfi_def_cfa_register %rbp
	movl	$80000000, %eax         ## imm = 0x4C4B400
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_SERIAL_Init
	.p2align	4, 0x90
_SERIAL_Init:                           ## @SERIAL_Init
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi12:
	.cfi_def_cfa_offset 16
Lcfi13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi14:
	.cfi_def_cfa_register %rbp
	popq	%rbp
	retq
	.cfi_endproc


.subsections_via_symbols
