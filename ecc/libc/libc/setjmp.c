#include <setjmp.h>
#include <stdlib.h>

#if defined __ECS_C__ || defined __ECS2_C__
// source: https://github.com/EigenCompilerSuite/sources/blob/master/libraries/cpp/csetjmp.cpp

asm(R"(
	.code longjmp
	mov	ptr $0, ptr [$sp + !lnksize * retalign + stackdisp]
	mov	int $res, int [$sp + !lnksize * retalign + ptralign + stackdisp]
	mov	ptr $sp, ptr [$0 + ptrsize * 0]
	mov	ptr $fp, ptr [$0 + ptrsize * 1]
	jump	fun [$0 + ptrsize * 2]
	)")


asm(R"(
	.code setjmp
	#if !lnksize
		pop	fun $0
	#endif
	mov	ptr $1, ptr [$sp + stackdisp]
	mov	ptr [$1 + ptrsize * 0], ptr $sp + stackdisp
	mov	ptr [$1 + ptrsize * 1], ptr $fp + stackdisp
	#if lnksize
		mov	fun [$1 + ptrsize * 2], fun $lnk
	#else
		mov	fun [$1 + ptrsize * 2], fun $0
	#endif
	mov	int $res, int 0
	#if lnksize
		jump	fun $lnk
	#else
		jump	fun $0
	#endif
	)")
#else

void longjmp(jmp_buf __jmpb, int __retval)
{
    exit(__retval);
}

int	setjmp(jmp_buf __jmpb)
{
    return 0;
}


#endif

