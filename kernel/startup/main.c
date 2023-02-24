#include <stdio.h>
#include <kernel/tty.h>

void kmain(void) {
	terminal_initialize();
	printf("Welcome to SteinsOS, world line 1.048596\n");
}
