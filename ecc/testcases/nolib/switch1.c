int putchar(int);

int numbers[] = { 4, 6, 9, 1, 7, 3, 4, 8, 11, 19, 13, 2, 0 };

int main()
{
	int* p = numbers;
	while( *p )
	{
		switch(*p)
		{
		case 1:
			putchar('L');
			break;
		case 13:
		case 3:
		case 8:
		case 2:
		case 5:
			putchar('F');
			break;
		case 19:
			putchar('M');
			break;
		default:
			putchar('O');
			break;
		}
		p++;
	}
	putchar('\n');
	return 0;
}

// expected: OOOLOFOFOMFF

