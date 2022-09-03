#ifndef M4_INTERFACE2_H
#define M4_INTERFACE2_H


typedef struct M4_Interface2Vtbl_s M4_Interface2Vtbl;
typedef struct M4_Interface2_s M4_Interface2;
struct M4_Interface2Vtbl_s;
struct M4_Interface2_s;


#include "m4-interface.h"
#include "m4-result.h"
#include "m4-value.h"

#include <stddef.h>

// each interface needs:
// 1. an offset of iface member of class implementing interface (see object1.c)
// 2. a function to allow finding other interfaces from any interface (see object1.c)
// 3. an id of the interface.

struct M4_Interface2Vtbl_s {
    // for embedded, give ability to check that vtbl is the expected one
    // and the vtbl pointer has not been corrupted, whic, if left unchecked
    // would result in calling into some random part of the address space.
    // It's something, if weak.
    M4_Interface2Vtbl const *const token;

    size_t offset;

    void (*query_interface)(
        M4_Interface2 const *const self,
        M4_Result *const ret,
        M4_InterfaceID const *const iid,
        void const **const val
    );
    void (*query_interface_mut)(
        M4_Interface2 *const self,
        M4_Result *const ret,
        M4_InterfaceID const *const iid,
        void **const val
    );

    ////
    void (*get_value)(
        M4_Interface2 const *const self,
        M4_Result *const ret,
        M4_Value *const val
    );
    void (*set_value)(
        M4_Interface2 *const self,
        M4_Result *const ret,
        M4_Value const *const arg
    );
    void (*get_objects)(
        M4_Interface2 const *const self,
        M4_Result *const ret,
        M4_Value *const val
    );
    void (*set_objects)(
        M4_Interface2 *const self,
        M4_Result *const ret,
        M4_Value const *const arg
    );
};


struct M4_Interface2_s {
    // vtbl must be read-only, even if struct is not
    M4_Interface2Vtbl const *const _vtbl;
};


extern M4_InterfaceID const M4_Interface2_ID;


void M4_Interface2_new(M4_Interface2 *const self,
                       M4_Interface2Vtbl const *const vtbl);


// Check that the vtbl referenced by self is indeed the expected vtbl
#if 0
// return ok() if it is, error otherwise.
void M4_Interface2_try_check_vtbl(
    M4_Interface2 const *const self,
    M4_Result *const ret
);
#endif
void M4_Interface2_check_vtbl_(char const *file, size_t line,
                               M4_Interface2 const *const self);
#define M4_Interface2_check_vtbl(self) M4_Interface2_check_vtbl_(__FILE__, __LINE__, self)


// Return the interface ptr for the interface identified by iid.
// if one such exists, return ok(), and ptr in *value (will need casting).
// if does not exist or on error, return Err().
void M4_Interface2_query_interface(
    M4_Interface2 const *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **const val
);
void M4_Interface2_query_interface_mut(
    M4_Interface2 *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **const val
);


// Example of getter/setters and indeed any other redirectable method.
void M4_Interface2_get_value(
    M4_Interface2 const *const self,
    M4_Result *const ret,
    M4_Value *const val
);


void M4_Interface2_set_value(
    M4_Interface2 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
);


void M4_Interface2_get_objects(
    M4_Interface2 const *const self,
    M4_Result *const ret,
    M4_Value *const val
);


void M4_Interface2_set_objects(
    M4_Interface2 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
);

#endif//M4_INTERFACE2_H
