	.file	"tst.c"
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LLC0:
	.long	0
	.long	0
	.section	".text"
	.align 4
	.global dodiv
	.type	dodiv, #function
	.proc	07
dodiv:
	mov	0, %g1
	sethi	%hi(.LLC0), %g2
	ldd	[%g2+%lo(.LLC0)], %f0
.LL2:
	add	%o0, %g1, %g2
	ldd	[%g2+8], %f8
	add	%g1, 8, %g1
	cmp	%g1, 72
	bne,pt	%icc, .LL2
	 faddd	%f0, %f8, %f0
	jmp	%o7+8
	 nop
	.size	dodiv, .-dodiv
	.ident	"GCC: (Debian 4.6.3-14) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
