#ifndef M4_PANIC_H
#define M4_PANIC_H

#include <stddef.h> //size_t

void M4_panic_(char const *file, size_t line,
               char const *msg
              ) __attribute__((noreturn));
#define M4_PANIC(msg) M4_panic_(__FILE__, __LINE__, msg)

#endif//M4_PANIC_H
