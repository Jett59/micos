typedef void (*constructor_or_destructor_t)(void);

extern constructor_or_destructor_t __init_array_start;
extern constructor_or_destructor_t __init_array_end;

extern constructor_or_destructor_t __fini_array_start;
extern constructor_or_destructor_t __fini_array_end;

extern int main(void);  // TODO: int main (int argc, char** argv);

void _Noreturn _init(void) {
  for (constructor_or_destructor_t* init_array = &__init_array_start; init_array != &__init_array_end; init_array++) {
    (*init_array)();
  }
  main();
  for (constructor_or_destructor_t *fini_array = &__fini_array_start;
       fini_array != &__fini_array_end; fini_array++) {
    (*fini_array)();
  }
  // TODO: exit();
  while (1)
    ;
}
