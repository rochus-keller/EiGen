int printf(const char *, ...);

struct foo {
	long long f : 50;
};

int main(void) {

    struct foo p = {0x235709324614}; // 38856723416596, msb 45

    long long a = p.f & 7610294871096; // msb 42, res 136315920 msb 27
	long long b = p.f | 7610294871096; // res 46467018287692, msb 45; truncated to 32 bit: -232887732

	return printf("%ld, %ld\n", a, b);
}
