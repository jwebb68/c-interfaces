#ifndef M2_INTERFACE3_H
#define M2_INTERFACE3_H

typedef struct M2_Interface3Vtbl_s M2_Interface3Vtbl;
typedef struct M2_Interface3_s M2_Interface3;
struct M2_Interface3Vtbl_s;
struct M2_Interface3_s;


#include "m2-interface.h"
#include "m2-result.h"
#include "m2-value.h"

#include <stddef.h>


//pub
struct M2_Interface3Vtbl_s {
    M2_Interface3Vtbl const *const token;
    size_t offset;

    // TODO: create separate struct containing just the methods..?
    // can this be the interface?
    // doesn't matter, interface does not have functions on it
    // but vtable ptr does.

    /// the 'method' that needs to be on all interfaces.
    // a bit nasty in using void ** for the out-param, would prefer it to be
    // typed with the expected type, but it's C and you cannot do that..
    // Or I could use a Specific M2_Result struct ( Result<void *, ErrorType>) -
    // nice although that is, it adds an extra struct + funcs to maintain
    // and results is manual generics expansion..
    void (*query_interface)(M2_Interface3 const *const self,
                            M2_InterfaceID const *const iid,
                            void const **const val,
                            M2_Result *const ret
                           );


    void (*query_interface_mut)(M2_Interface3 *const self,
                                M2_InterfaceID const *const iid,
                                void **const val,
                                M2_Result *const ret
                               );

    //// a form of id-driven property getter/setter..
    void (*get)(M2_Interface3 const *const self,
                M2_AttributeID const aid,
                M2_Value *const val,
                M2_Result *const ret
               );


    void (*set)(M2_Interface3 *const self,
                M2_AttributeID const aid,
                M2_Value const *const arg,
                M2_Result *const ret
               );

    //// a form of id-driven action callers..
    void (*action)(M2_Interface3 *const self,
                   M2_ActionID const aid,
                   M2_Value const *const arg,
                   M2_Value *const val,
                   M2_Result *const ret
                  );


    //// the property handlers/action handlers for direct calling.
    void (*get_value1)(M2_Interface3 const *const self,
                       M2_Value *const val,
                       M2_Result *const ret
                      );


    void (*set_value1)(M2_Interface3 *const self,
                       M2_Value const *const arg,
                       M2_Result *const ret
                      );


    void (*get_value2)(M2_Interface3 const *const self,
                       M2_Value *const val,
                       M2_Result *const ret
                      );


    void (*set_value2)(M2_Interface3 *const self,
                       M2_Value const *const arg,
                       M2_Result *const ret
                      );


    void (*get_value3)(M2_Interface3 const *const self,
                       M2_Value *const val,
                       M2_Result *const ret
                      );


    void (*set_value3)(M2_Interface3 *const self,
                       M2_Value const *const arg,
                       M2_Result *const ret
                      );

    void (*action1)(M2_Interface3 *const self,
                    M2_Value const *const arg,
                    M2_Value *const out,
                    M2_Result *const ret
                   );

    void (*action2)(M2_Interface3 *const self,
                    M2_Value const *const arg,
                    M2_Value *const out,
                    M2_Result *const ret
                   );
};



//pub
struct M2_Interface3_s {
    // for embedded (and indeed non-) vtbl must be const
    // this also complies with MISRA.
    M2_Interface3Vtbl const *const _vtbl;
};


//pub
extern M2_InterfaceID const M2_Interface3_ID;

//pub
#if 0
// this function is not being inlined and I don't know why.
// I want it inlined for speed/reduced code side
// I want it a function, for type-safety reasons
void M2_Interface3_new(M2_Interface3 *const self,
                       M2_Interface3Vtbl const *const vtbl);
#else
#define M2_Interface3_new(self, vtbl) \
    { uint8_t *s = (uint8_t *)(self); \
        M2_Interface3Vtbl const **p = (M2_Interface3Vtbl const **)(s + offsetof(M2_Interface3, _vtbl)); \
        *p = (vtbl); }
#endif



// Check that the interface referenced by self is indeed an M2_Interface3
// return ok() if it is, error otherwise.
#if 0
void M2_Interface3_try_check_vtbl_(char const *file, size_t line,
                                   M2_Interface3 const *const self
                                  );
#endif
//pub
void M2_Interface3_check_vtbl_(char const *file, size_t line,
                               M2_Interface3 const *const self);
#define M2_Interface3_check_vtbl(self) M2_Interface3_check_vtbl_(__FILE__, __LINE__, self)


// Return the interface ptr for the interface identified by iid.
// if one such exists, return ok(), and ptr in *value (will need casting).
// if does not exist or on error, return Err().
//pub
void M2_Interface3_query_interface(M2_Interface3 const *const self,
                                   M2_InterfaceID const *const iid,
                                   void const **const value,
                                   M2_Result *const ret
                                  );

//pub
void M2_Interface3_query_interface_mut(M2_Interface3 *const self,
                                       M2_InterfaceID const *const iid,
                                       void **const value,
                                       M2_Result *const ret
                                      );


// a form of dynamic dispatching using an interface using ids for props/actions
// (these names come from dlms/cosem)
void M2_Interface3_get(M2_Interface3 const *const self,
                       M2_AttributeID const aid,
                       M2_Value *const value,
                       M2_Result *const ret
                      );


void M2_Interface3_set(M2_Interface3 *const self,
                       M2_AttributeID const aid,
                       M2_Value const *const value,
                       M2_Result *const ret
                      );


void M2_Interface3_action(M2_Interface3 *const self,
                          M2_ActionID const aid,
                          M2_Value const *const arg,
                          M2_Value *const val,
                          M2_Result *const ret
                         );


void M2_Interface3_get_value1(M2_Interface3 const *const self,
                              M2_Value *const val,
                              M2_Result *const ret
                             );

void M2_Interface3_set_value1(M2_Interface3 *const self,
                              M2_Value const *const arg,
                              M2_Result *const ret
                             );


void M2_Interface3_get_value2(M2_Interface3 const *const self,
                              M2_Value *const val,
                              M2_Result *const ret
                             );

void M2_Interface3_set_value2(M2_Interface3 *const self,
                              M2_Value const *const arg,
                              M2_Result *const ret
                             );


void M2_Interface3_get_value3(M2_Interface3 const *const self,
                              M2_Value *const val,
                              M2_Result *const ret
                             );

void M2_Interface3_set_value3(M2_Interface3 *const self,
                              M2_Value const *const arg,
                              M2_Result *const ret
                             );

void M2_Interface3_action1(M2_Interface3 *const self,
                           M2_Value const *const arg,
                           M2_Value *const out,
                           M2_Result *const ret
                          );

void M2_Interface3_action2(M2_Interface3 *const self,
                           M2_Value const *const arg,
                           M2_Value *const out,
                           M2_Result *const ret
                          );


#endif//M2_INTERFACE3_H
