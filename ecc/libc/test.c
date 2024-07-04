#include <stdio.h>


int main(int argc, char** argv) {

    printf("Hello!\n");

    int i, n;
    
    for( i = 0; i < argc; i++ )
      printf("arg %d: %s\n",i, argv[i]);

    // initialize first and second terms
    int t1 = 0, t2 = 1;

    // initialize the next term (3rd term)
    int nextTerm = t1 + t2;

    n = 30;

    // print the first two terms t1 and t2
    printf("Fibonacci Series: %d, %d, ", t1, t2);

    // print 3rd to nth terms
    for (i = 3; i <= n; ++i) {
      printf("%d, ", nextTerm);
      t1 = t2;
      t2 = nextTerm;
      nextTerm = t1 + t2;
    }
    printf("\n");
    return 0;
}
