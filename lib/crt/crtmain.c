typedef void (*constructor_or_destructor_t)(void);

extern constructor_or_destructor_t __init_array_start;
extern constructor_or_destructor_t __init_array_end;

extern constructor_or_destructor_t __fini_array_start;
extern constructor_or_destructor_t __fini_array_end;

extern int main(void);  // TODO: int main (int argc, char** argv);

void _Noreturn _init(void) {
  constructor_or_destructor_t* init_array = &__init_array_start;
  do {
    (*init_array) ();
  } while (++init_array != &__init_array_end);
  main();
  constructor_or_destructor_t *fini_array = &__init_array_start;
  do {
    (*fini_array)();
  } while (++fini_array != &__fini_array_end);
  // TODO: exit();
  while (1)
    ;
}
