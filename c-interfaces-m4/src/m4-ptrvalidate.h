#ifndef M4_PTRVALIDATE_H
#define M4_PTRVALIDATE_H

#include <stddef.h> //size_t
#include <stdbool.h>


bool M4_is_range_readable(void const *const ptr, size_t const len);
#define M4_IS_RANGE_READABLE(ptr, len) \
    (M4_is_range_readable((ptr), (len)))
#define M4_IS_STRUCT_READABLE(ptr) \
    (M4_IS_RANGE_READABLE((ptr), sizeof(*(ptr))))

bool M4_is_range_writable(void *ptr, size_t len);
#define M4_IS_RANGE_WRITABLE(ptr, len) \
    (M4_is_range_writable((ptr), (len)))
#define M4_IS_STRUCT_WRITABLE(ptr) \
    (M4_IS_RANGE_WRITABLE((ptr), sizeof(*(ptr))))

bool M4_is_range_readwritable(void const *ptr, size_t len);
#define M4_IS_RANGE_READWRITABLE(ptr, len) \
    (M4_is_range_readwritable((ptr), (len)))
#define M4_IS_STRUCT_READWRITABLE(ptr) \
    (M4_IS_RANGE_READWRITABLE((ptr), sizeof(*(ptr))))


void M4_check_range_readable_(char const *file, size_t line,
                              void const *const ptr, size_t len);
#define M4_CHECK_RANGE_READABLE(ptr, len) \
    (M4_check_range_readable_(__FILE__, __LINE__, (ptr), (len)))

#define M4_check_struct_readable_(file, line, ptr) \
    (M4_check_range_readable_((file), (line), (ptr), sizeof(*(ptr))))
#define M4_CHECK_STRUCT_READABLE(ptr) \
    (M4_check_struct_readable_(__FILE__, __LINE__, (ptr)))


void M4_check_range_writable_(char const *file, size_t line, void *const ptr,
                              size_t len);
#define M4_CHECK_RANGE_WRITABLE(ptr, len) \
    (M4_check_range_writable_(__FILE__, __LINE__, (ptr), (len)))

#define M4_check_struct_writable_(file, line, ptr) \
    (M4_check_range_writable_((file), (line), (ptr), sizeof(*(ptr))))
#define M4_CHECK_STRUCT_WRITABLE(ptr) \
    (M4_check_struct_writable_(__FILE__, __LINE__, (ptr)))


void M4_check_range_readwritable_(char const *file, size_t line,
                                  void *const ptr, size_t len);
#define M4_CHECK_RANGE_READWRITABLE(ptr) \
    (M4_check_range_readwritable_(__FILE__, __LINE__, (ptr), (len))

#define M4_check_struct_readwritable_(file, line, ptr) \
    (M4_check_range_readwritable_((file), (line), (ptr), sizeof(*(ptr))))
#define M4_CHECK_STRUCT_READWRITABLE(ptr) \
    (M4_check_struct_readwritable_(__FILE__, __LINE__, (ptr)))


#endif//M4_PTRVALIDATE_H
