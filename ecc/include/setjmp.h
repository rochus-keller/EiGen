/*
	setjmp.h
	stubs for future use.
*/

#ifndef _SETJMP_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _SETJMP_H_

#include "_ansi.h"

// ECS specific, implementation in setjmp.cod
typedef struct jmp_buf {void *sp, *fp, (*pc) ();} jmp_buf[1];



void longjmp(jmp_buf __jmpb, int __retval);
int	setjmp(jmp_buf __jmpb);

#ifdef __cplusplus
}
#endif
#endif /* _SETJMP_H_ */

