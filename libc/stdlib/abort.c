#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void) {
    __builtin_unreachable();
}
