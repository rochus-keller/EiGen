int
main()
{
	int x;
	
	x = 4;
	if(!x != 0)
		return 3;
	if(!!x != 1)
		return 2;
	if(-x != 0 - 4)
		return 1;
	return 0;
}

