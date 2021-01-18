#ifndef R2_INTERFACE1_H
#define R2_INTERFACE1_H

typedef struct R2_Interface1Vtbl_s R2_Interface1Vtbl;
typedef struct R2_Interface1_s R2_Interface1;
struct R2_Interface1Vtbl_s;
struct R2_Interface1_s;

#include "r2-interface.h"
#include "r2-result.h"
#include "r2-value.h"

#include <stddef.h>

// each interface needs:
// 1. an offset of iface member of class implementing interface (see object1.c)
// 2. a function to allow finding other interfaces from any interface (see object1.c)
// 3. an id of the interface, unique across all interfaces.

struct R2_Interface1Vtbl_s {
    // for embedded, give ability to check that vtbl is the expected one
    // and the vtbl pointer has not been corrupted, which, if left unchecked
    // would result in calling into some random part of the address space.
    // It's something, if weak.
    R2_InterfaceID const *guard;

    // offset to compute pointer-to-interface struct to it's containing
    // struct start.
    size_t offset;

    /// the 'method' that needs to be on all interfaces.
    // a bit nasty in using void ** for the out-param, would prefer it to be
    // typed with the expected type, but it's C and you cannot do that..
    // Or I could use a Specific R2_Result struct ( R2::Result<void *, ErrorType>) -
    // nice although that is, it adds an extra struct + funcs to maintain
    // and results is manual generics expansion..
    R2_Result(*query_interface)(R2_Interface1 const *const self,
                                R2_InterfaceID const *const iid, void const **const ret);
    R2_Result(*query_interface_mut)(R2_Interface1 *const self,
                                    R2_InterfaceID const *const iid, void **const ret);

    ////
    // example of some 'methods' that are implemented in this interface.
    // there is an argument to be had regarding keeping implementation out of interfaces.
    R2_Result(*get)(R2_Interface1 const *const self, R2_AttributeID const aid,
                    R2_Value *const ret);
    R2_Result(*set)(R2_Interface1 *const self, R2_AttributeID const aid,
                    R2_Value const *const arg);
    R2_Result(*action)(R2_Interface1 *const self, R2_ActionID const aid,
                       R2_Value const *const arg, R2_Value *const ret);

    ////
    R2_Result(*get_value)(R2_Interface1 const *const self, R2_Value *const ret);
    R2_Result(*set_value)(R2_Interface1 *const self, R2_Value const *const arg);
};

struct R2_Interface1_s {
    // for embedded (and indeed non-) vtbl must be const
    // this also complies with MISRA.
    R2_Interface1Vtbl const *const _vtbl;
};

extern R2_InterfaceID const R2_Interface1_ID;

R2_Interface1 R2_Interface1_new(R2_Interface1Vtbl const *const vtbl);

// Check that the interface referenced by self is indeed an Interface1
// return ok() if it is, error otherwise.
//R2_Result R2_Interface1_check_guard(R2_Interface1 const *const self);
void R2_Interface1_check_guard(R2_Interface1 const *const self);

// Return the interface ptr for the interface identified by iid.
// if one such exists, return ok(), and ptr in *value (will need casting).
// if does not exist or on error, return Err().
R2_Result R2_Interface1_query_interface(R2_Interface1 const *const self,
                                        R2_InterfaceID const *const iid, void const **const value);
R2_Result R2_Interface1_query_interface_mut(R2_Interface1 *const self,
        R2_InterfaceID const *const iid, void **const value);

// a form of dynamic dispatching using an interface using ids for props/actions
// (these names come from dlms/cosem)
R2_Result R2_Interface1_get(R2_Interface1 const *const self,
                            R2_AttributeID const aid, R2_Value *const value);
R2_Result R2_Interface1_set(R2_Interface1 *const self, R2_AttributeID const aid,
                            R2_Value const *const value);
R2_Result R2_Interface1_action(R2_Interface1 *const self, R2_ActionID const aid,
                               R2_Value const *const arg, R2_Value *const ret);


// Example of getter/setters and indeed any other redirectable method.
R2_Result R2_Interface1_get_value(R2_Interface1 const *const self,
                                  R2_Value *const value);
R2_Result R2_Interface1_set_value(R2_Interface1 *const self,
                                  R2_Value const *const value);

#endif//R2_INTERFACE1_H
