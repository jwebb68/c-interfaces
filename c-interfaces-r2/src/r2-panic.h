#ifndef PANIC_H
#define PANIC_H

#include <stddef.h> //size_t

void R2_panic_(char const *file, size_t line,
               char const *msg) __attribute__((noreturn));
#define R2_PANIC(msg) R2_panic_(__FILE__, __LINE__, msg)

#endif//PANIC_H
