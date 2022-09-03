#include "m3-panic.h"

#include <assert.h>
#include <stdbool.h>


__attribute__((noreturn)) void M3_panic_(char const *file, size_t line,
        char const *msg
                                        )
{
    ((void)file);
    ((void)line);
    ((void)msg);
    assert(false);
}
