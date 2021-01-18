#include "r2-ptrvalidate.h"

#include "r2-panic.h"

// note: platform specific.
// currently matches the memset values in the destroy functions
// but really shouldn't need to match values.
// but don't know how to spot non-readable memory in linux.
bool R2_is_range_readable(void const *const ptr, size_t const len)
{
    return (ptr != NULL && len > 0);
}

bool R2_is_range_writable(void *ptr, size_t len)
{
    return (ptr != NULL && len > 0);
}

bool R2_is_range_readwritable(void const *ptr, size_t len)
{
    return (ptr != NULL && len > 0);
}


void R2_check_range_readable(char const *file, size_t line,
                             void const *const ptr, size_t len)
{
    if (!R2_is_range_readable(ptr, len)) {
        R2_panic_(file, line, "struct not readable");
    }
}

void R2_check_range_writable_(char const *file, size_t line, void *const ptr,
                              size_t len)
{
    if (!R2_is_range_writable(ptr, len)) {
        R2_panic_(file, line, "struct not writable");
    }
}

void R2_check_range_readwritable_(char const *file, size_t line,
                                  void *const ptr, size_t len)
{
    if (!R2_is_range_readwritable(ptr, len)) {
        R2_panic_(file, line, "struct not read/writable");
    }
}
