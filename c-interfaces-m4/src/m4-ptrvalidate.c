#include "m4-ptrvalidate.h"

#include "m4-panic.h"

// note: platform specific.
// currently matches the memset values in the destroy functions
// but really shouldn't need to match values.
// but don't know how to spot non-readable memory in linux.
bool M4_is_range_readable(void const *const ptr, size_t const len)
{
    return (ptr != NULL && len > 0);
}


bool M4_is_range_writable(void *ptr, size_t len)
{
    return (ptr != NULL && len > 0);
}


bool M4_is_range_readwritable(void const *ptr, size_t len)
{
    return (ptr != NULL && len > 0);
}


void M4_check_range_readable(char const *file, size_t line,
                             void const *const ptr, size_t len)
{
    if (!M4_is_range_readable(ptr, len)) {
        M4_panic_(file, line, "struct not readable");
    }
}


void M4_check_range_writable_(char const *file, size_t line, void *const ptr,
                              size_t len)
{
    if (!M4_is_range_writable(ptr, len)) {
        M4_panic_(file, line, "struct not writable");
    }
}


void M4_check_range_readwritable_(char const *file, size_t line,
                                  void *const ptr, size_t len)
{
    if (!M4_is_range_readwritable(ptr, len)) {
        M4_panic_(file, line, "struct not read/writable");
    }
}
