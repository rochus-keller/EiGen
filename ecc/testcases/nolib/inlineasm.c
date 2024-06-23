

int main() {

	asm ( "push	s4 35\n"
		  "mov	fun $0, fun @putchar\n"
		  "call fun $0, 4 \n"
		  "push	s4 10\n"
		  "mov	fun $0, fun @putchar\n"
		  "call fun $0, 4" );
	return 0;
}
