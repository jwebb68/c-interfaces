#ifndef M2_PANIC_H
#define M2_PANIC_H

#include <stddef.h> //size_t

void M2_panic_(char const *file, size_t line,
               char const *msg
              ) __attribute__((noreturn));
#define M2_PANIC(msg) M2_panic_(__FILE__, __LINE__, msg)

#endif//M2_PANIC_H
