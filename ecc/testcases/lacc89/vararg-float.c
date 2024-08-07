#include <stdarg.h>

int printf(const char *, ...);

int foo(float a, double b, ...) {
	double c, d, e;
	va_list args;
	va_start(args, b);

	c = va_arg(args, double);
	d = va_arg(args, double);
	e = va_arg(args, double);

	printf("a = %f, b = %f, c = %f, d = %f, e = %f\n", a, b, c, d, e);
    // expect: a = 3.140000, b = 2.710000, c = 4.900000, d = 90.000000, e = 3.140000

	va_end(args);
	return d;
}

int main(void) {
	float f = 3.14f;
	double d = 2.71;
	return foo(f, d, 4.9f, 90.0, f);
}
