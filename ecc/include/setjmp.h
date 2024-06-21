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
// TODO #include <machine/setjmp.h>
#define _JBLEN 5
typedef int jmp_buf[_JBLEN]; // TODO


void	_EXFUN(longjmp,(jmp_buf __jmpb, int __retval));
int	_EXFUN(setjmp,(jmp_buf __jmpb));

#ifdef __cplusplus
}
#endif
#endif /* _SETJMP_H_ */

