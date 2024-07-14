/*
	setjmp.h
	stubs for future use.
*/

#ifndef _SETJMP_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _SETJMP_H_

#if defined  __ECS_C__ || defined __ECS2_C__
// ECS specific, implementation in setjmp.cod
typedef struct jmp_buf {void *sp, *fp, (*pc) ();} jmp_buf[1];
#elif defined __GNUC__
typedef int __jmp_buf[6];
# define _SIGSET_NWORDS	(1024 / (8 * sizeof (unsigned long int)))
typedef struct
  {
    unsigned long int __val[_SIGSET_NWORDS];
  } __sigset_t;
struct __jmp_buf_tag
  {
    /* NOTE: The machine-dependent definitions of `__sigsetjmp'
       assume that a `jmp_buf' begins with a `__jmp_buf' and that
       `__mask_was_saved' follows it.  Do not move these members
       or add others before it.  */
    __jmp_buf __jmpbuf;		/* Calling environment.  */
    int __mask_was_saved;	/* Saved the signal mask?  */
    __sigset_t __saved_mask;	/* Saved signal mask.  */
  };
typedef struct __jmp_buf_tag jmp_buf[1];

#endif



void longjmp(jmp_buf __jmpb, int __retval);
int	setjmp(jmp_buf __jmpb);

#ifdef __cplusplus
}
#endif
#endif /* _SETJMP_H_ */

