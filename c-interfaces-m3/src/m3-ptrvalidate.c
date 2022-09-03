#include "m3-ptrvalidate.h"

#include "m3-panic.h"

// note: platform specific.
// currently matches the memset values in the destroy functions
// but really shouldn't need to match values.
// but don't know how to spot non-readable memory in linux.
bool M3_is_range_readable(void const *const ptr, size_t const len)
{
    return (ptr != NULL && len > 0);
}


bool M3_is_range_writable(void *ptr, size_t len)
{
    return (ptr != NULL && len > 0);
}


bool M3_is_range_readwritable(void const *ptr, size_t len)
{
    return (ptr != NULL && len > 0);
}


void M3_check_range_readable(char const *file, size_t line,
                             void const *const ptr, size_t len)
{
    if (!M3_is_range_readable(ptr, len)) {
        M3_panic_(file, line, "struct not readable");
    }
}


void M3_check_range_writable_(char const *file, size_t line, void *const ptr,
                              size_t len)
{
    if (!M3_is_range_writable(ptr, len)) {
        M3_panic_(file, line, "struct not writable");
    }
}


void M3_check_range_readwritable_(char const *file, size_t line,
                                  void *const ptr, size_t len)
{
    if (!M3_is_range_readwritable(ptr, len)) {
        M3_panic_(file, line, "struct not read/writable");
    }
}
