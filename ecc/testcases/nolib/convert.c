
int float_convert1()
{
    const int a = 2.71;
    const int b = 3.14;
	const int d = -2.71;
	const int e = -3.14;
	return !(a == 2 && b == 3 && d == -2 && e == -3);
}

int float_convert2()
{
	float x = 2.71;
	float y = 3.14;
    const int a = x;
    const int b = y;
	const int d = -x;
	const int e = -y;
	return !(a == 2 && b == 3 && d == -2 && e == -3);
}

int double_convert()
{
	double x = 2.71;
	double y = 3.14;
    const int a = x;
    const int b = y;
	const int d = -x;
	const int e = -y;
	return !(a == 2 && b == 3 && d == -2 && e == -3);
}

int main()
{
    return double_convert() + float_convert1() + float_convert2();
}
