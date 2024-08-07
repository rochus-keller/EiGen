
static int unsigned_char(void) {
	unsigned char a = 0xE8u;
	char b = 2;

	const int r1 = sizeof(a << b);
	const int r2 = a << b;
	const int r3 = a >> b;
	return !(r1 == 4 && r2 == 928 && r3 == 58);
}

static int signed_char(void) {
	signed char a = 0x65;
	int b = 3;

	const int r1 = sizeof(a << b);
	const int r2 = a << b;
	const int r3 = a >> b;
	return !(r1 == 4 && r2 == 808 && r3 == 12);
}

static int signed_long(void) {
	long a = 0x7E00FF0F;
	short b = 33;
	
	const int r1 = sizeof(a << b);
	const int r2 = a << b;
	const int r3 = a >> 4;
	return !(r1 == 4 && r2 == -66978274 && r3 == 132124656);
}

static int chained(void)
{
	unsigned a = 0x7EABCDF4;
	const int r1 = a << 3 >> 1;
	return r1 != 2058303440;
}

static int overflow(void) {
	long a, b = 0x567895;
	a = 0x567895 << 10;
	b = b << 10;
	return !(a == 1508004864 && b == 1508004864);
}

int main(void) {
	return unsigned_char()
		+ signed_char()
		+ signed_long()
		+ chained()
		+ overflow();
}
