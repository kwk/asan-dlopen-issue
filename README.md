# Blacklisting in conjunction with dlopen

This contrived example CMake program shows how I attempted to compile a
library and a C program that loads the library with dlopen.

Inside the library a malloc is done which is never freed.

I want to ignore this memory leak somehow because it clutters my ASAN logs in
the real project.

# Compilation

     git clone https://github.com/kwk/asan-dlopen-issue.git
     cd asan-dlopen
     mkdir build
     export CC=$(which clang)
     cmake ..
     make
     ./myprog

# Results

As you can see, the blacklisted call to `foo` is reported even though it was
blacklisted.

     Hello! 0x60200000efd0
     
     =================================================================
     ==24244==ERROR: LeakSanitizer: detected memory leaks
     
     Direct leak of 4 byte(s) in 1 object(s) allocated from:
         #0 0x4bce02 in __interceptor_malloc (/home/kkleine/Schreibtisch/asan-dlopen/build/myprog+0x4bce02)
         #1 0x7f67e2efe733 in say_hello /home/kkleine/Schreibtisch/asan-dlopen/mylib.c:6:28
         #2 0x4dc2b1 in foo /home/kkleine/Schreibtisch/asan-dlopen/myprog.c:20:3
         #3 0x4dc4ff in main /home/kkleine/Schreibtisch/asan-dlopen/myprog.c:27:3
         #4 0x7f67e57f0ec4 in __libc_start_main /build/buildd/eglibc-2.19/csu/libc-start.c:287
     
     SUMMARY: AddressSanitizer: 4 byte(s) leaked in 1 allocation(s).
