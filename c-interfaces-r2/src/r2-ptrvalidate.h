#ifndef PTRVALIDATE_H
#define PTRVALIDATE_H

#include <stddef.h> //size_t
#include <stdbool.h>


bool R2_is_range_readable(void const *const ptr, size_t const len);
#define R2_IS_RANGE_READABLE(ptr, len) R2_is_range_readable(ptr, len)
#define R2_IS_STRUCT_READABLE(ptr) R2_IS_RANGE_READABLE(ptr, sizeof(*ptr))

bool R2_is_range_writable(void *ptr, size_t len);
#define R2_IS_RANGE_WRITABLE(ptr, len) R2_is_range_writable(ptr, len)
#define R2_IS_STRUCT_WRITABLE(ptr) R2_IS_RANGE_WRITABLE(ptr, sizeof(*ptr))

bool R2_is_range_readwritable(void const *ptr, size_t len);
#define R2_IS_RANGE_READWRITABLE(ptr, len) R2_is_range_readwritable(ptr, len)
#define R2_IS_STRUCT_READWRITABLE(ptr) R2_IS_RANGE_READWRITABLE(ptr, sizeof(*ptr))


void R2_check_range_readable_(char const *file, size_t line,
                              void const *const ptr, size_t len);
#define R2_CHECK_RANGE_READABLE(ptr, len) do{R2_check_range_readable(__FILE__, __LINE__, ptr, len)}while(0);
#define R2_CHECK_STRUCT_READABLE(ptr) do{R2_check_range_readable(__FILE__, __LINE__, ptr, sizeof(*ptr))}while(0);

void R2_check_range_writable_(char const *file, size_t line, void *const ptr,
                              size_t len);
#define R2_CHECK_RANGE_WRITABLE(ptr, len) do{R2_check_range_writable(__FILE__, __LINE__, ptr, len)}while(0);
#define R2_CHECK_STRUCT_WRITABLE(ptr) do{R2_check_range_writable(__FILE__, __LINE__, ptr, sizeof(*ptr))}while(0);

void R2_check_range_readwritable_(char const *file, size_t line,
                                  void *const ptr, size_t len);
#define R2_CHECK_RANGE_READWRITABLE(ptr, len) do{R2_check_range_readwritable(__FILE__, __LINE__, ptr, len)}while(0);
#define R2_CHECK_STRUCT_READWRITABLE(ptr) do{R2_check_range_readwritable(__FILE__, __LINE__, ptr, sizeof(*ptr))}while(0);


#endif//PTRVALIDATE_H
