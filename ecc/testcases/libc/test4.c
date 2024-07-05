#include <stdarg.h>

int putchar(int);


void f(int t, ...)
{
	va_list l;
	va_start(l,t);
	const int a = va_arg(l,int);
	const double b = va_arg(l,double);
	const char* str = va_arg(l,const char*);
	const char c = va_arg(l,char);
	const int d = va_arg(l,int);
	va_end(l);
    while( *str != 0 )
    {
    	putchar(*str);
    	str++;
    }
	putchar(a);
	putchar('\n');
	putchar(c);
	putchar('\n');
	putchar(d);
	putchar('\n');
}

int main() {
	f(42,66,1.234567,"Hello World!\n",'c',77);
    return 0;
}
