// example from https://stackoverflow.com/questions/14685406/practical-usage-of-setjmp-and-longjmp-in-c

#include <stdio.h>
#include <setjmp.h>

#if 1
jmp_buf bufferA, bufferB;

void routineB(); // forward declaration 

void routineA()
{
    int r ;

    printf("- 12 : (A1)\n");

    r = setjmp(bufferA);
    if (r == 0) routineB();

    printf("- 17 : (A2) r=%d\n",r);

    r = setjmp(bufferA);
    if (r == 0) longjmp(bufferB, 20001);

    printf("- 22 : (A3) r=%d\n",r);

    r = setjmp(bufferA);
    if (r == 0) longjmp(bufferB, 20002);

    printf("- 27 : (A4) r=%d\n",r);
}

void routineB()
{
    int r;

    printf("- 34 : (B1)\n");

    r = setjmp(bufferB);
    if (r == 0) longjmp(bufferA, 10001);

    printf("- 39 : (B2) r=%d\n", r);

    r = setjmp(bufferB);
    if (r == 0) longjmp(bufferA, 10002);

    printf("- 44 : (B3) r=%d\n", r);

    r = setjmp(bufferB);
    if (r == 0) longjmp(bufferA, 10003);
}


int main(int argc, char **argv) 
{
    routineA();
    return 0;
}

/* Expected output

- 12 : (A1)
- 34 : (B1)
- 17 : (A2) r=10001
- 39 : (B2) r=20001
- 22 : (A3) r=10002
- 44 : (B3) r=20002
- 27 : (A4) r=10003

*/

#else

// example from https://www.geeksforgeeks.org/c-setjump-and-longjump/

jmp_buf buf; 
void func() 
{ 
    printf("Welcome to GeeksforGeeks\n"); 
  
    // Jump to the point setup by setjmp 
    longjmp(buf, 1); 
  
    printf("Geek2\n"); 
} 
  
int main() 
{ 
    // Setup jump position using buf and return 0 
    if (setjmp(buf)) 
        printf("Geek3\n"); 
    else { 
        printf("Geek4\n"); 
        func(); 
    } 
    return 0; 
}

/* Expected output:
Geek4
Welcome to GeeksforGeeks
Geek3
*/

#endif
