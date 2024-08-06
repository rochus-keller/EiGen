#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <eigen/lib_adapter.h>

static size_t __printstr(const char* str)
{
	size_t n = 0;
	while( *str )
	{
		putchar(*str);
		str++; n++;
	}
	return n;
}

size_t strlen(const char * str)
{
	int i = 0;
	while( *str )
	{
		i++;
		str++;
	}
	return i;
}

extern double sin(double in)
{
	return 1.0; // TODO
}

char* strcpy(char * out, const char * in)
{
	while( *in )
	{
		*out = *in;
		out++; in++;
	}
	*out = 0;
	return out;
}

char* strncpy(char * out, const char * in, size_t len)
{
	while(*in && len)
	{
		*out = *in;
		out++; in++;
		len--;
	}
	return out;
}

int memcmp(const void* lhs, const void* rhs, size_t n)
{
  unsigned char *s1 = (unsigned char *) lhs;
  unsigned char *s2 = (unsigned char *) rhs;

  while (n--)
    {
      if (*s1 != *s2)
	{
	  return *s1 - *s2;
	}
      s1++;
      s2++;
    }
  return 0;
}

int strncmp(const char* s1, const char* s2, size_t n)
{
  if (n == 0)
    return 0;

  while (n-- != 0 && *s1 == *s2)
    {
      if (n == 0 || *s1 == '\0')
	break;
      s1++;
      s2++;
    }

  return (*(unsigned char *) s1) - (*(unsigned char *) s2);
}

void* memcpy(void* out, const void* in, size_t len)
{
	char* lhs = out;
	char* rhs = in;
	for( int i = 0; i < len; i++ )
		lhs[i] = rhs[i];
	return out;
}

void* memset(void* out, int in, size_t len)
{
	char* str = out;
	for( int i = 0; i < len; i++ )
		str[i] = in;
	return out;
}

char * strcat(char * s1, const char* s2)
{
  char *s = s1;

  while (*s1)
    s1++;

  while (*s1++ = *s2++)
    ;
  return s;
}

char * strchr(const char* s1, int i)
{
  const unsigned char *s = (const unsigned char *)s1;
  unsigned char c = i;
  while (*s && *s != c)
    s++;
  if (*s == c)
    return (char *)s;
  return NULL;
}

char * strrchr(const char* s, int i)
{
  const char *last = NULL;

  if (i)
    {
      while ((s=strchr(s, i)))
	{
	  last = s;
	  s++;
	}
    }
  else
    {
      last = strchr(s, i);
    }
		  
  return (char *) last;
}

static void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

// source: https://www.geeksforgeeks.org/implement-itoa/
int myitoa(int num, char* str, int base)
{
    int i = 0;
    int isNegative = 0;
 
    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return 1;
    }
 
    // In standard itoa(), negative numbers are handled
    // only with base 10. Otherwise numbers are
    // considered unsigned.
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return i;
}

// adopted from https://stackoverflow.com/questions/16647278/minimal-implementation-of-sprintf-or-printf
int printf(const char* fmt, ... )
{
	int int_temp;
	long long_temp;
    char char_temp;
    char *string_temp;
    double double_temp;

    char ch;
    int length = 0;

    char buffer[512];

	va_list arg;
	va_start(arg,fmt);
	    
    while ( ch = *fmt++) {
        if ( '%' == ch ) {
            switch (ch = *fmt++) {
                /* %% - print out a single %    */
                case '%':
                    putchar('%');
                    length++;
                    break;

                /* %c: print out a character    */
                case 'c':
                    char_temp = va_arg(arg, int);
                    putchar(char_temp);
                    length++;
                    break;

                /* %s: print out a string       */
                case 's':
                    string_temp = va_arg(arg, char *);
                    length += __printstr(string_temp);
                    break;

                /* %d: print out an int         */
                case 'd':
                    int_temp = va_arg(arg, int);
                    myitoa(int_temp, buffer, 10);
                    length += __printstr(buffer);
                    break;
                    
                case 'l':
                	ch = *fmt++;
                	if( ch == 'd' )
                	{
		                long_temp = va_arg(arg, long);
		                myitoa(long_temp, buffer, 10);
		                length += __printstr(buffer);
                	}else
                		putchar('?');
                	break;

                /* %x: print out an int in hex  */
                case 'x':
                    int_temp = va_arg(arg, int);
                    myitoa(int_temp, buffer, 16);
                    length += __printstr(buffer);
                    break;

                case 'f':
                case 'e':
                case 'g':
                	{
                    double_temp = va_arg(arg, double);
                    const int lhs = double_temp;
                    int len = myitoa(lhs,buffer,10);
                    buffer[len++] = '.';
                    const int rhs = (double_temp-(double)lhs)*100000;
                    myitoa(rhs,buffer+len,10);
                    length += __printstr(buffer);
                    }
                    break;

                default:
                	putchar('?');
                	break;
            }
        }else { // no % var, just plain text
            putchar(ch);
            length++;
        }
    }
    return length;
}

double ceil( double f )
{
	return f + 1.0;
}

double floor( double f )
{
	return f;
}

void _Exit(int code)
{
	exit(code);
}

// source: https://github.com/EigenCompilerSuite/sources/blob/master/libraries/cpp/csetjmp.cpp

asm (R"(
	.code longjmp
	mov	ptr $0, ptr [$sp + !lnksize * retalign + stackdisp]
	mov	int $res, int [$sp + !lnksize * retalign + ptralign + stackdisp]
	mov	ptr $sp, ptr [$0 + ptrsize * 0]
	mov	ptr $fp, ptr [$0 + ptrsize * 1]
	jump	fun [$0 + ptrsize * 2]
	)");


asm (R"(
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
	)");

#if defined(__unix__) || defined(__linux__)
LIBRARY(libc, "libc.so.6");
#elif defined(__APPLE__)
LIBRARY(libc, "/usr/lib/libSystem.B.dylib");
#else
#error "no libc available for given OS"
#endif
FUNCTION(libc, malloc, 1);
FUNCTION(libc, calloc, 1);
FUNCTION(libc, realloc, 2);
FUNCTION(libc, free, 2);
FUNCTION(libc, rand,0);
FUNCTION(libc, putchar,1);
FUNCTION(libc, exit,1);
FUNCTION(libc, strcmp, 2);
FUNCTION(libc, fopen, 2);
FUNCTION(libc, fgetc, 1);
FUNCTION(libc, fwrite, 4);
FUNCTION(libc, fread, 4);
FUNCTION(libc, fclose, 1);


