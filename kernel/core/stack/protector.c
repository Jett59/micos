#include <error.h>

_Noreturn void __stack_chk_fail(void) { fatal_error("Stack smash detected"); }