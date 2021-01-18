#ifndef M2_INTERFACE_H
#define M2_INTERFACE_H


typedef struct M2_InterfaceLookup_s M2_InterfaceLookup;
struct M2_InterfaceLookup_s;


#include "m2-result.h"
#include "m2-panic.h"

#include <inttypes.h>
#include <stddef.h>


typedef const char *M2_InterfaceID;

typedef uint8_t M2_AttributeID;
typedef uint8_t M2_ActionID;


// compare two pointers for equality, panic if not equal
// assert(expected == actual)..
void M2_Interface_try_check(void const *const expected,
                            void const *const actual, M2_Result *const ret);


#if 0
void M2_Interface_check_guard_(char const *file, size_t line,
                               void const *const expected,
                               void const *const actual);
#define M2_Interface_check_guard(expected, actual) \
    M2_Interface_check_guard(__FILE__, __LINE__, expected, actual)
#else
// if check_guard is a function, gcc isn't inlining it.. and don't know why.
// using a macro gets it inlined
#define M2_Interface_check_(file, line, expected, actual) do{if((expected)!=(actual)){M2_panic_(file, line, "Bad Interface");}}while(0);
#endif


struct M2_InterfaceLookup_s {
    M2_InterfaceID const *iid;
    size_t offset;
};


void M2_Interface_query_interface(void const *inst,
                                  M2_InterfaceID const *const iid, void const **const val, M2_Result *const ret,
                                  M2_InterfaceLookup const *begin, M2_InterfaceLookup const *end);


void M2_Interface_query_interface_mut(void *inst,
                                      M2_InterfaceID const *const iid, void **const val, M2_Result *const ret,
                                      M2_InterfaceLookup const *begin, M2_InterfaceLookup const *end);


#define M2_INTERFACE_GET_OBJPTR(objtype, ifaceptr) ((objtype const *)((uint8_t const *)ifaceptr - ifaceptr->_vtbl->offset))


#define M2_INTERFACE_GET_OBJPTR_MUT(objtype, ifaceptr) ((objtype *)((uint8_t *)ifaceptr - ifaceptr->_vtbl->offset))


#endif// M2_INTERFACE_H
