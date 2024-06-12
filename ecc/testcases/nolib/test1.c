
#ifdef __cplusplus
extern "C" {
#endif

int putchar(int);

#define HELLO "Hello World!\n"

int main() {
    const char* p = HELLO;
    while( *p != 0 )
    {
    	putchar(*p);
    	p++;
    }
    return 0;
}

#ifdef __cplusplus
}
#endif

