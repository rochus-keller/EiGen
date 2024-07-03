#include <stdio.h>

typedef struct 
{
	long long quot; 
	long long rem; 
} div_t;


div_t div(int a, int b)
{
	div_t res;
	res.quot = a;
	res.rem = b;
	return res;
}

div_t dov(div_t d)
{
	printf("quot=%d rem=%d\n",(int)d.quot,(int)d.rem);
	d.quot = 55;
	d.rem = 66;
	return d;
}

int main()
{
	div_t res;
	
	res = dov( div (33,44) );
	printf("quot=%d rem=%d\n",(int)res.quot,(int)res.rem);
	return res.rem != 66;
}
