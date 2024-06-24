#include <stdio.h>

typedef struct 
{
	int quot; /* quotient */
	int rem; /* remainder */
} div_t;

div_t div(int _numer, int _denom)
{
	div_t res;
	res.quot = _numer;
	res.rem = _denom;
	printf("quot=%d rem=%d\n",res.quot,res.rem);
	return res;
}

int main()
{
	div_t res;
	res = div (33, 44);
	printf("quot=%d rem=%d\n",res.quot,res.rem);
	return res.rem != 44;
}
