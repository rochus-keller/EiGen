#include <stddef.h>
#include <stdarg.h>

extern int putchar(int);
extern void* malloc(size_t _size);

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

void *calloc(size_t n, size_t s)
{
	const int m = n*s;
	char* res = malloc(m);
	for( int i = 0; i < m; i++ )
		res[i] = 0;
	return res;
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
char* itoa(int num, char* str, int base)
{
    int i = 0;
    int isNegative = 0;
 
    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
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
 
    return str;
}

static int normalize(double *val) {
    int exponent = 0;
    double value = *val;

    while (value >= 1.0) {
        value /= 10.0;
        ++exponent;
    }

    while (value < 0.1) {
        value *= 10.0;
        --exponent;
    }
    *val = value;
    return exponent;
}

static void ftoa_fixed(char *buffer, double value) {  
    /* carry out a fixed conversion of a double value to a string, with a precision of 5 decimal digits. 
     * Values with absolute values less than 0.000001 are rounded to 0.0
     * Note: this blindly assumes that the buffer will be large enough to hold the largest possible result.
     * The largest value we expect is an IEEE 754 double precision real, with maximum magnitude of approximately
     * e+308. The C standard requires an implementation to allow a single conversion to produce up to 512 
     * characters, so that's what we really expect as the buffer size.     
     */

    int exponent = 0;
    int places = 0;
    static const int width = 4;

    if (value == 0.0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }         

    if (value < 0.0) {
        *buffer++ = '-';
        value = -value;
    }

    exponent = normalize(&value);

    while (exponent > 0) {
        int digit = value * 10;
        *buffer++ = digit + '0';
        value = value * 10 - digit;
        ++places;
        --exponent;
    }

    if (places == 0)
        *buffer++ = '0';

    *buffer++ = '.';

    while (exponent < 0 && places < width) {
        *buffer++ = '0';
        --exponent;
        ++places;
    }

    while (places < width) {
        int digit = value * 10.0;
        *buffer++ = digit + '0';
        value = value * 10.0 - digit;
        ++places;
    }
    *buffer = '\0';
}

void ftoa_sci(char *buffer, double value) {
    int exponent = 0;
    int places = 0;
    static const int width = 4;

    if (value == 0.0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0.0) {
        *buffer++ = '-';
        value = -value;
    }

    exponent = normalize(&value);

    int digit = value * 10.0;
    *buffer++ = digit + '0';
    value = value * 10.0 - digit;
    --exponent;

    *buffer++ = '.';

    for (int i = 0; i < width; i++) {
        int digit = value * 10.0;
        *buffer++ = digit + '0';
        value = value * 10.0 - digit;
    }

    *buffer++ = 'e';
    itoa(exponent, buffer, 10);
  	return 0;
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
                    itoa(int_temp, buffer, 10);
                    length += __printstr(buffer);
                    break;
                    
                case 'l':
                	ch = *fmt++;
                	if( ch == 'd' )
                	{
		                long_temp = va_arg(arg, long);
		                itoa(long_temp, buffer, 10);
		                length += __printstr(buffer);
                	}else
                		putchar('?');
                	break;

                /* %x: print out an int in hex  */
                case 'x':
                    int_temp = va_arg(arg, int);
                    itoa(int_temp, buffer, 16);
                    length += __printstr(buffer);
                    break;

                case 'f':
                    double_temp = va_arg(arg, double);
                    ftoa_fixed(buffer, double_temp);
                    length += __printstr(buffer);
                    break;

                case 'e':
                    double_temp = va_arg(arg, double);
                    ftoa_sci(buffer, double_temp);
                    length += __printstr(buffer);
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

