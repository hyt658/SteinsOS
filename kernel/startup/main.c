#include <stdio.h>
#include <kernel/tty.h>

void 
kmain(void) 
{
	terminal_initialize();
	printf("Welcome to SteinsOS\n");
    printf("World line 1.0%d\n", 48596);
    printf("El Psy %s\n", "Congroo");

    for (int i=0; i<500; ++i) {
        printf("%d ", i);
    }
}
