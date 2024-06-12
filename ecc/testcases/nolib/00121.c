// TODO int f(int a), g(int a), a; // fails with chibicc
int f(int a);
int g(int a);
int a;


int
main()
{
	return f(1) - g(1);
}

int
f(int a)
{
	return a;
}

int
g(int a)
{
	return a;
}
