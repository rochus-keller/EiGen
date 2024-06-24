#include <stdio.h>

typedef struct 
{
	int quot; /* quotient */
	int rem; /* remainder */
} div_t;

typedef struct
{
	int number, denom;
} fract_t;

div_t div(fract_t fract)
{
	div_t res;
	printf("number=%d denom=%d\n",fract.number,fract.denom);
	res.quot = fract.number;
	res.rem = fract.denom;
	return res;
}

int main()
{
	fract_t fract;
	div_t res;
	fract.number = 33;
	fract.denom = 44;
	res = div (fract);
	printf("quot=%d rem=%d\n",res.quot,res.rem);
	return res.rem != 44;
}
