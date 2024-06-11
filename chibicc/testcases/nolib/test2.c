
long long f()
{
	return 12345;
}

long long gll;

int main()
{
	int i;
	
	gll = f();
	i = gll;
	return i != 12345;
}
