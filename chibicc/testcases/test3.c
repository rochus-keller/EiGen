
long long f(int i, char c, void* p)
{
	return i;
}

long long gll;

int main()
{
	int i;
	
	gll = f(12345, '?', &i);
	i = gll;
	return i != 12345;
}
