#ifndef R2_INTERFACE2_H
#define R2_INTERFACE2_H

typedef struct R2_Interface2Vtbl_s R2_Interface2Vtbl;
typedef struct R2_Interface2_s R2_Interface2;
struct R2_Interface2Vtbl_s;
struct R2_Interface2_s;

#include "r2-interface.h"
#include "r2-result.h"
#include "r2-value.h"

#include <stddef.h>

// each interface needs:
// 1. an offset of iface member of class implementing interface (see object1.c)
// 2. a function to allow finding other interfaces from any interface (see object1.c)
// 3. an id of the interface.

struct R2_Interface2Vtbl_s {
    // for embedded, give ability to check that vtbl is the expected one
    // and the vtbl pointer has not been corrupted, whic, if left unchecked
    // would result in calling into some random part of the address space.
    // It's something, if weak.
    R2_InterfaceID const *guard;

    size_t offset;

    R2_Result(*query_interface)(R2_Interface2 const *const self,
                                R2_InterfaceID const *const iid, void const **const ret);
    R2_Result(*query_interface_mut)(R2_Interface2 *const self,
                                    R2_InterfaceID const *const iid, void **const ret);
    ////
    R2_Result(*get_value)(R2_Interface2 const *const self, R2_Value *const ret);
    R2_Result(*set_value)(R2_Interface2 *const self, R2_Value const *const arg);
    R2_Result(*get_objects)(R2_Interface2 const *const self, R2_Value *const ret);
    R2_Result(*set_objects)(R2_Interface2 *const self, R2_Value const *const arg);
};

struct R2_Interface2_s {
    // vtbl must be const, even in mut object
    R2_Interface2Vtbl const *const _vtbl;
};

extern const R2_InterfaceID R2_Interface2_ID;

R2_Interface2 R2_Interface2_new(R2_Interface2Vtbl const *const vtbl);

// Check that the interface referenced by self is indeed an Interface2
// return ok() if it is, error otherwise.
//R2_Result R2_Interface2_check_guard(R2_Interface2 const *const self);
void R2_Interface2_check_guard(R2_Interface2 const *const self);

// Return the interface ptr for the interface identified by iid.
// if one such exists, return ok(), and ptr in *value (will need casting).
// if does not exist or on error, return Err().
R2_Result R2_Interface2_query_interface(R2_Interface2 const *const self,
                                        R2_InterfaceID const *const iid, void const **const ret);
R2_Result R2_Interface2_query_interface_mut(R2_Interface2 *const self,
        R2_InterfaceID const *const iid, void **const ret);

// Example of getter/setters and indeed any other redirectable method.
R2_Result R2_Interface2_get_value(R2_Interface2 const *const self,
                                  R2_Value *const ret);
R2_Result R2_Interface2_set_value(R2_Interface2 *const self,
                                  R2_Value const *const arg);
R2_Result R2_Interface2_get_objects(R2_Interface2 const *const self,
                                    R2_Value *const ret);
R2_Result R2_Interface2_set_objects(R2_Interface2 *const self,
                                    R2_Value const *const arg);

#endif//R2_INTERFACE2_H
