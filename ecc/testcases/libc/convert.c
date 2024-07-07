#include <math.h>

int float_convert()
{
    const int a = 2.71;
    const int b = 3.14;
	const int d = floor(2.71);
	const int e = floor(3.14);
	const int f = ceil(2.71);
	const int g = ceil(3.14);
	return !(a == 2 && b == 3 && d == 2 && e == 3 && f == 3 && g == 4);
}

int double_convert()
{
	double x = 2.71;
	double y = 3.14;
    const int a = x;
    const int b = y;
	const int d = floor(x);
	const int e = floor(y);
	const int f = ceil(x);
	const int g = ceil(y);
	return !(a == 2 && b == 3 && d == 2 && e == 3 && f == 3 && g == 4);
}

int main()
{
	return double_convert() + float_convert();
}
