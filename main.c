#include "syscall.c"
#include "threads.c"
#include <stdio.h>
#include "contextSwitch.c"
int main() {
	sysc();
	threads();
	contextSwitch();

return 0;
}
