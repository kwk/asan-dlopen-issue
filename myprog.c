#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void foo() {
  void * handle = dlopen("./libmylib.so", RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "Error opening ./libmylib.so: %s", dlerror());
    return;
  }
  void * fn = dlsym(handle, "say_hello");
  if (!fn) {
    fprintf(stderr, "Error getting address of \"say_hello\" symbol: %s", dlerror());
    return;
  }

  // Cast the function pointer to correct type and call the function 
  typedef void (*say_hello_ptr)();
  say_hello_ptr say_hello = (say_hello_ptr)fn;
  say_hello();
}

int main(int argc, char **argv) {
  (void) argc;
  (void) argv;

  foo();
  return EXIT_SUCCESS;
}
