	.file	"main.c"
	.text
	.globl	average_div
	.type	average_div, @function
average_div:
.LFB39:
	.cfi_startproc
	endbr64
	movl	%esi, %eax
	subl	%edi, %eax
	shrl	%eax
	addl	%edi, %eax
	ret
	.cfi_endproc
.LFE39:
	.size	average_div, .-average_div
	.globl	average_bw1
	.type	average_bw1, @function
average_bw1:
.LFB40:
	.cfi_startproc
	endbr64
	movl	%edi, %eax
	shrl	%eax
	movl	%esi, %edx
	shrl	%edx
	addl	%edx, %eax
	andl	%esi, %edi
	andl	$1, %edi
	addl	%edi, %eax
	ret
	.cfi_endproc
.LFE40:
	.size	average_bw1, .-average_bw1
	.globl	average_bw2
	.type	average_bw2, @function
average_bw2:
.LFB41:
	.cfi_startproc
	endbr64
	movl	%edi, %eax
	xorl	%esi, %eax
	shrl	%eax
	andl	%esi, %edi
	addl	%edi, %eax
	ret
	.cfi_endproc
.LFE41:
	.size	average_bw2, .-average_bw2
	.globl	main
	.type	main, @function
main:
.LFB42:
	.cfi_startproc
	endbr64
	movl	$1000, %edx
.L5:
	movl	$1000, %eax
.L6:
	subl	$1, %eax
	jne	.L6
	subl	$1, %edx
	jne	.L5
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE42:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
