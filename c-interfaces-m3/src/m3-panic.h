#ifndef M3_PANIC_H
#define M3_PANIC_H

#include <stddef.h> //size_t

void M3_panic_(char const *file, size_t line,
               char const *msg
              ) __attribute__((noreturn));
#define M3_PANIC(msg) M3_panic_(__FILE__, __LINE__, msg)

#endif//M3_PANIC_H
