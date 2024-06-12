#include <stdio.h>

int main() {

	printf("hello int: %d\n", 7890);
	printf("hello hex: %x\n", 65521);
	printf("hello long: %ld\n", 1234567);
	printf("hello char %%: %c\n", '%');
	printf("hello string: \"%s\"\n", "this is a string");
 	printf("hello float: %f\n", 123.45678);

 	double a = 123.45678;
 	double b = 123.0;
 	const int res = (a - b)*100000;
   	return res != 45678;
}
