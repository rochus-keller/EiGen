// source: https://github.com/EigenCompilerSuite/sources/blob/master/libraries/cpp/csetjmp.cpp

#ifdef __ecs_chibicc__

asm(
	".code longjmp\n"
	"mov	ptr $0, ptr [$sp + !lnksize * retalign + stackdisp]\n"
	"mov	int $res, int [$sp + !lnksize * retalign + ptralign + stackdisp]\n"
	"mov	ptr $sp, ptr [$0 + ptrsize * 0]\n"
	"mov	ptr $fp, ptr [$0 + ptrsize * 1]\n"
	"jump	fun [$0 + ptrsize * 2]"
	)


asm(
	".code setjmp\n"
	"#if !lnksize\n"
	"	pop	fun $0\n"
	"#endif\n"
	"mov	ptr $1, ptr [$sp + stackdisp]\n"
	"mov	ptr [$1 + ptrsize * 0], ptr $sp + stackdisp\n"
	"mov	ptr [$1 + ptrsize * 1], ptr $fp + stackdisp\n"
	"#if lnksize\n"
	"	mov	fun [$1 + ptrsize * 2], fun $lnk\n"
	"#else\n"
	"	mov	fun [$1 + ptrsize * 2], fun $0\n"
	"#endif\n"
	"mov	int $res, int 0\n"
	"#if lnksize\n"
	"	jump	fun $lnk\n"
	"#else\n"
	"	jump	fun $0\n"
	"#endif"
	)
	
#endif
