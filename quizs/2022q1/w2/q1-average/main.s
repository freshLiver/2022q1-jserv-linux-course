	.file	"main.c"
	.text
	.p2align 4
	.globl	average_div
	.type	average_div, @function
average_div:
.LFB0:
	.cfi_startproc
	endbr64
	movl	%esi, %eax
	subl	%edi, %eax
	shrl	%eax
	addl	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	average_div, .-average_div
	.p2align 4
	.globl	average_bw1
	.type	average_bw1, @function
average_bw1:
.LFB1:
	.cfi_startproc
	endbr64
	movl	%edi, %eax
	movl	%esi, %edx
	andl	%esi, %edi
	shrl	%eax
	shrl	%edx
	andl	$1, %edi
	addl	%edx, %eax
	addl	%edi, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	average_bw1, .-average_bw1
	.p2align 4
	.globl	average_bw2
	.type	average_bw2, @function
average_bw2:
.LFB2:
	.cfi_startproc
	endbr64
	movl	%edi, %eax
	andl	%esi, %edi
	xorl	%esi, %eax
	shrl	%eax
	addl	%edi, %eax
	ret
	.cfi_endproc
.LFE2:
	.size	average_bw2, .-average_bw2
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
