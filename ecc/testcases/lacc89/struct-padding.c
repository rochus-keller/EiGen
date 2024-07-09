#include <assert.h>

struct foo {
	char c;
	int y;
	long long x;
};

struct s2 {
	int foo, bar;
	int b;
};

struct s3 {
	char *c;
	int i;
};

struct s4 {
	char foo[7];
	int l;
};

struct s5 {
	char c;
};

struct s6 {
	char c[9];
};

struct s7 {
	int x;
	int y;
	char *name;
	char tag[3];
};

struct s8 {
	char s[3];
	char c[5];
};

struct s9 {
	short s;
	char c[3];
};

struct s10 {
	short s;
	int i[2];
};

int main() {
    int res = 1;
    res &= sizeof(struct foo) == 16;
    res &= sizeof(struct s2) == 12;
    res &= sizeof(struct s3) ==
#if __SIZEOF_POINTER__ == 8
            16;
#else
            8;
#endif
    res &= sizeof(struct s4) == 12;
    res &= sizeof(struct s5) == 1;
    res &= sizeof(struct s6) == 9;
    res &= sizeof(struct s7) ==
#if __SIZEOF_POINTER__ == 8
            24;
#else
            16;
#endif
    res &= sizeof(struct s8) == 8;
    res &= sizeof(struct s9) == 6;
    res &= sizeof(struct s10) == 12;
    assert(res == 1);

    return !res;
}
