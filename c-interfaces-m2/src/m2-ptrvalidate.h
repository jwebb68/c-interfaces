#ifndef M2_PTRVALIDATE_H
#define M2_PTRVALIDATE_H

#include <stddef.h> //size_t
#include <stdbool.h>


bool M2_is_range_readable(void const *const ptr, size_t const len);
#define M2_IS_RANGE_READABLE(ptr, len) \
    (M2_is_range_readable((ptr), (len)))
#define M2_IS_STRUCT_READABLE(ptr) \
    (M2_IS_RANGE_READABLE((ptr), sizeof(*(ptr))))

bool M2_is_range_writable(void *ptr, size_t len);
#define M2_IS_RANGE_WRITABLE(ptr, len) \
    (M2_is_range_writable((ptr), (len)))
#define M2_IS_STRUCT_WRITABLE(ptr) \
    (M2_IS_RANGE_WRITABLE((ptr), sizeof(*(ptr))))

bool M2_is_range_readwritable(void const *ptr, size_t len);
#define M2_IS_RANGE_READWRITABLE(ptr, len) \
    (M2_is_range_readwritable((ptr), (len)))
#define M2_IS_STRUCT_READWRITABLE(ptr) \
    (M2_IS_RANGE_READWRITABLE((ptr), sizeof(*(ptr))))


void M2_check_range_readable_(char const *file, size_t line,
                              void const *const ptr, size_t len);
#define M2_CHECK_RANGE_READABLE(ptr, len) \
    (M2_check_range_readable_(__FILE__, __LINE__, (ptr), (len)))

#define M2_check_struct_readable_(file, line, ptr) \
    (M2_check_range_readable_((file), (line), (ptr), sizeof(*(ptr))))
#define M2_CHECK_STRUCT_READABLE(ptr) \
    (M2_check_struct_readable_(__FILE__, __LINE__, (ptr)))


void M2_check_range_writable_(char const *file, size_t line, void *const ptr,
                              size_t len);
#define M2_CHECK_RANGE_WRITABLE(ptr, len) \
    (M2_check_range_writable_(__FILE__, __LINE__, (ptr), (len)))

#define M2_check_struct_writable_(file, line, ptr) \
    (M2_check_range_writable_((file), (line), (ptr), sizeof(*(ptr))))
#define M2_CHECK_STRUCT_WRITABLE(ptr) \
    (M2_check_struct_writable_(__FILE__, __LINE__, (ptr)))


void M2_check_range_readwritable_(char const *file, size_t line,
                                  void *const ptr, size_t len);
#define M2_CHECK_RANGE_READWRITABLE(ptr) \
    (M2_check_range_readwritable_(__FILE__, __LINE__, (ptr), (len))

#define M2_check_struct_readwritable_(file, line, ptr) \
    (M2_check_range_readwritable_((file), (line), (ptr), sizeof(*(ptr))))
#define M2_CHECK_STRUCT_READWRITABLE(ptr) \
    (M2_check_struct_readwritable_(__FILE__, __LINE__, (ptr)))


#endif//M2_PTRVALIDATE_H
