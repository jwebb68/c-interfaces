#ifndef M3_INTERFACE3_H
#define M3_INTERFACE3_H

typedef struct M3_Interface3Vtbl_s M3_Interface3Vtbl;
typedef struct M3_Interface3_s M3_Interface3;
struct M3_Interface3Vtbl_s;
struct M3_Interface3_s;


#include "m3-interface.h"
#include "m3-result.h"
#include "m3-value.h"

#include <stddef.h>


//pub
struct M3_Interface3Vtbl_s {
    M3_Interface3Vtbl const *const token;
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
    void (*query_interface)(M3_Result *const ret,
                            M3_Interface3 const *const self,
                            M3_InterfaceID const *const iid,
                            void const **const val
                           );


    void (*query_interface_mut)(M3_Result *const ret,
                                M3_Interface3 *const self,
                                M3_InterfaceID const *const iid,
                                void **const val
                               );

    //// a form of id-driven property getter/setter..
    void (*get)(M3_Result *const ret,
                M3_Interface3 const *const self,
                M3_AttributeID const aid,
                M3_Value *const val
               );


    void (*set)(M3_Result *const ret,
                M3_Interface3 *const self,
                M3_AttributeID const aid,
                M3_Value const *const arg
               );

    //// a form of id-driven action callers..
    void (*action)(M3_Result *const ret,
                   M3_Interface3 *const self,
                   M3_ActionID const aid,
                   M3_Value const *const arg,
                   M3_Value *const val
                  );


    //// the property handlers/action handlers for direct calling.
    void (*get_value1)(M3_Result *const ret,
                       M3_Interface3 const *const self,
                       M3_Value *const val
                      );


    void (*set_value1)(M3_Result *const ret,
                       M3_Interface3 *const self,
                       M3_Value const *const arg
                      );


    void (*get_value2)(M3_Result *const ret,
                       M3_Interface3 const *const self,
                       M3_Value *const val
                      );


    void (*set_value2)(M3_Result *const ret,
                       M3_Interface3 *const self,
                       M3_Value const *const arg
                      );


    void (*get_value3)(M3_Result *const ret,
                       M3_Interface3 const *const self,
                       M3_Value *const val
                      );


    void (*set_value3)(M3_Result *const ret,
                       M3_Interface3 *const self,
                       M3_Value const *const arg
                      );

    void (*action1)(M3_Result *const ret,
                    M3_Interface3 *const self,
                    M3_Value const *const arg,
                    M3_Value *const out
                   );

    void (*action2)(M3_Result *const ret,
                    M3_Interface3 *const self,
                    M3_Value const *const arg,
                    M3_Value *const out
                   );
};



//pub
struct M3_Interface3_s {
    // for embedded (and indeed non-) vtbl must be const
    // this also complies with MISRA.
    M3_Interface3Vtbl const *const _vtbl;
};


//pub
extern M3_InterfaceID const M3_Interface3_ID;

//pub
#if 0
// this function is not being inlined and I don't know why.
// I want it inlined for speed/reduced code side
// I want it a function, for type-safety reasons
void M3_Interface3_new(M3_Interface3 *const self,
                       M3_Interface3Vtbl const *const vtbl);
#else
#define M3_Interface3_new(self, vtbl) \
    { uint8_t *s = (uint8_t *)(self); \
        M3_Interface3Vtbl const **p = (M3_Interface3Vtbl const **)(s + offsetof(M3_Interface3, _vtbl)); \
        *p = (vtbl); }
#endif



// Check that the interface referenced by self is indeed an M3_Interface3
// return ok() if it is, error otherwise.
#if 0
void M3_Interface3_try_check_vtbl_(char const *file, size_t line,
                                   M3_Interface3 const *const self
                                  );
#endif
//pub
void M3_Interface3_check_vtbl_(char const *file, size_t line,
                               M3_Interface3 const *const self);
#define M3_Interface3_check_vtbl(self) M3_Interface3_check_vtbl_(__FILE__, __LINE__, self)


// Return the interface ptr for the interface identified by iid.
// if one such exists, return ok(), and ptr in *value (will need casting).
// if does not exist or on error, return Err().
//pub
void M3_Interface3_query_interface(M3_Result *const ret,
                                   M3_Interface3 const *const self,
                                   M3_InterfaceID const *const iid,
                                   void const **const value
                                  );

//pub
void M3_Interface3_query_interface_mut(M3_Result *const ret,
                                       M3_Interface3 *const self,
                                       M3_InterfaceID const *const iid,
                                       void **const value
                                      );


// a form of dynamic dispatching using an interface using ids for props/actions
// (these names come from dlms/cosem)
void M3_Interface3_get(M3_Result *const ret,
                       M3_Interface3 const *const self,
                       M3_AttributeID const aid,
                       M3_Value *const value
                      );


void M3_Interface3_set(M3_Result *const ret,
                       M3_Interface3 *const self,
                       M3_AttributeID const aid,
                       M3_Value const *const value
                      );


void M3_Interface3_action(M3_Result *const ret,
                          M3_Interface3 *const self,
                          M3_ActionID const aid,
                          M3_Value const *const arg,
                          M3_Value *const val
                         );


void M3_Interface3_get_value1(M3_Result *const ret,
                              M3_Interface3 const *const self,
                              M3_Value *const val
                             );

void M3_Interface3_set_value1(M3_Result *const ret,
                              M3_Interface3 *const self,
                              M3_Value const *const arg
                             );


void M3_Interface3_get_value2(M3_Result *const ret,
                              M3_Interface3 const *const self,
                              M3_Value *const val
                             );

void M3_Interface3_set_value2(M3_Result *const ret,
                              M3_Interface3 *const self,
                              M3_Value const *const arg
                             );


void M3_Interface3_get_value3(M3_Result *const ret,
                              M3_Interface3 const *const self,
                              M3_Value *const val
                             );

void M3_Interface3_set_value3(M3_Result *const ret,
                              M3_Interface3 *const self,
                              M3_Value const *const arg
                             );

void M3_Interface3_action1(M3_Result *const ret,
                           M3_Interface3 *const self,
                           M3_Value const *const arg,
                           M3_Value *const out
                          );

void M3_Interface3_action2(M3_Result *const ret,
                           M3_Interface3 *const self,
                           M3_Value const *const arg,
                           M3_Value *const out
                          );


#endif//M3_INTERFACE3_H
