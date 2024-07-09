#include <string.h>

static char *date = __DATE__;
static char *time = __TIME__;

int main(void) {
	return strlen(date) + strlen(time);
}
