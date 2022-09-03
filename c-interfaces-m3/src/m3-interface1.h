#ifndef M3_INTERFACE1_H
#define M3_INTERFACE1_H


typedef struct M3_Interface1Vtbl_s M3_Interface1Vtbl;
typedef struct M3_Interface1_s M3_Interface1;
struct M3_Interface1Vtbl_s;
struct M3_Interface1_s;


#include "m3-interface.h"
#include "m3-result.h"
#include "m3-value.h"

#include <stddef.h>

// each interface needs:
// 1. an offset of iface member of class implementing interface (see object1.c)
// 2. a function to allow finding other interfaces from any interface (see object1.c)
// 3. an id of the interface, unique across all interfaces.

//pub
struct M3_Interface1Vtbl_s {
    // for embedded, give ability to check that vtbl is the expected one
    // and the vtbl pointer has not been corrupted, which, if left unchecked
    // would result in calling into some random part of the address space.
    // It's something, albeit weak.
    M3_Interface1Vtbl const *const token;

    // Offset from interace location in struct to the location of the containing struct.
    size_t offset;

    // TODO: create separate struct containing just the methods..?
    // can this be the interface?
    // doesn't matter, interface does not have functions on it
    // but vtable ptr does.

    /// the 'method' that needs to be on all interfaces.
    // a bit nasty in using void ** for the out-param, would prefer it to be
    // typed with the expected type, but it's C and you cannot do that..
    // Or I could use a Specific M3_Result struct ( Result<void *, ErrorType>) -
    // nice although that is, it adds an extra struct + funcs to maintain
    // and results is manual generics expansion..
    void (*query_interface)(
        M3_Result *const ret,
        M3_Interface1 const *const self,
        M3_InterfaceID const *const iid,
        void const **const val
    );


    void (*query_interface_mut)(
        M3_Result *const ret,
        M3_Interface1 *const self,
        M3_InterfaceID const *const iid,
        void **const val
    );

    ////
    // example of some 'methods' that are implemented in this interface.
    // there is an argument to be had regarding keeping implementation out of interfaces.
    //
    // They should always have interface ptr as first,
    // Maybe result as second (although seriously thinking of always having a result, even if unused
    // as this would prevent some register reallocations but would limit number of args that would
    // go in regs).
    void (*foo)(M3_Interface1 *const self);


    void (*foo2)(M3_Interface1 *const self, M3_Result *const ret);

    void (*foo3)(M3_Result *const ret, M3_Interface1 *const self);
};


//pub
struct M3_Interface1_s {
    // for embedded (and indeed non-) vtbl must be const
    // this also complies with MISRA.
    M3_Interface1Vtbl const *const _vtbl;
};


//pub
extern M3_InterfaceID const M3_Interface1_ID;

//pub
#if 0
// this function is not being inlined and I don't know why.
// I want it inlined for speed/reduced code side
// I want it a function, for type-safety reasons
void M3_Interface1_new(M3_Interface1 *const self,
                       M3_Interface1Vtbl const *const vtbl);
#else
#define M3_Interface1_new(self, vtbl) \
    { uint8_t *s = (uint8_t *)(self); \
        M3_Interface1Vtbl const **p = (M3_Interface1Vtbl const **)(s + offsetof(M3_Interface1, _vtbl)); \
        *p = (vtbl); }
#endif



// Check that the interface referenced by self is indeed an M3_Interface1
// return ok() if it is, error otherwise.
#if 0
void M3_Interface1_try_check_vtbl_(M3_Result *const ret,
                                   char const *file, size_t line,
                                   M3_Interface1 const *const self
                                  );
#endif
//pub
void M3_Interface1_check_vtbl_(char const *file, size_t line,
                               M3_Interface1 const *const self);
#define M3_Interface1_check_vtbl(self) M3_Interface1_check_vtbl_(__FILE__, __LINE__, self)


// Return the interface ptr for the interface identified by iid.
// if one such exists, return ok(), and ptr in *value (will need casting).
// if does not exist or on error, return Err().
//pub
void M3_Interface1_query_interface(
    M3_Result *const ret,
    M3_Interface1 const *const self,
    M3_InterfaceID const *const iid,
    void const **const value
);

//pub
void M3_Interface1_query_interface_mut(
    M3_Result *const ret,
    M3_Interface1 *const self,
    M3_InterfaceID const *const iid,
    void **const value
);


//pub
void M3_Interface1_foo(M3_Interface1 *const self);


//pub
void M3_Interface1_foo2(M3_Interface1 *const self, M3_Result *const ret);

//pub
void M3_Interface1_foo3(M3_Result *const ret, M3_Interface1 *const self);

#endif//M3_INTERFACE1_H
