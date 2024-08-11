typedef unsigned int uint32_t;

struct OBX$Array$1 { uint32_t $1: 31; uint32_t $s: 1; void* $a; };

int numbers[] = { 33, 23, 64, 86, 9, 12 };

int index(int i) {
	return i;
}

int count( struct OBX$Array$1 arr )
{
	int a = ((int *)arr.$a)[2];
	((int *)arr.$a)[4] = 13;
	int b = ((int *)arr.$a)[index(4)];
	struct OBX$Array$1* $t0 = &arr;
	int c = ((int *)$t0->$a)[index(0)];
	return !(a == 64 && b == 13 && c == 33);
}

int main()
{
	return count((struct OBX$Array$1){6,0,numbers});
}
