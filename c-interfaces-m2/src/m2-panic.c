#include "m2-panic.h"

#include <assert.h>
#include <stdbool.h>


__attribute__((noreturn)) void M2_panic_(char const *file, size_t line,
        char const *msg
                                        )
{
    ((void)file);
    ((void)line);
    ((void)msg);
    assert(false);
}
