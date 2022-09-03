#ifndef M2_INTERFACE2_H
#define M2_INTERFACE2_H


typedef struct M2_Interface2Vtbl_s M2_Interface2Vtbl;
typedef struct M2_Interface2_s M2_Interface2;
struct M2_Interface2Vtbl_s;
struct M2_Interface2_s;


#include "m2-interface.h"
#include "m2-result.h"
#include "m2-value.h"

#include <stddef.h>

// each interface needs:
// 1. an offset of iface member of class implementing interface (see object1.c)
// 2. a function to allow finding other interfaces from any interface (see object1.c)
// 3. an id of the interface.

struct M2_Interface2Vtbl_s {
    // for embedded, give ability to check that vtbl is the expected one
    // and the vtbl pointer has not been corrupted, whic, if left unchecked
    // would result in calling into some random part of the address space.
    // It's something, if weak.
    M2_Interface2Vtbl const *const token;

    size_t offset;

    void (*query_interface)(M2_Interface2 const *const self,
                            M2_InterfaceID const *const iid,
                            void const **const val,
                            M2_Result *const ret
                           );
    void (*query_interface_mut)(M2_Interface2 *const self,
                                M2_InterfaceID const *const iid,
                                void **const val,
                                M2_Result *const ret
                               );

    ////
    void (*get_value)(M2_Interface2 const *const self,
                      M2_Value *const val,
                      M2_Result *const ret
                     );
    void (*set_value)(M2_Interface2 *const self,
                      M2_Value const *const arg,
                      M2_Result *const ret
                     );
    void (*get_objects)(M2_Interface2 const *const self,
                        M2_Value *const val,
                        M2_Result *const ret
                       );
    void (*set_objects)(M2_Interface2 *const self,
                        M2_Value const *const arg,
                        M2_Result *const ret
                       );
};


struct M2_Interface2_s {
    // vtbl must be read-only, even if struct is not
    M2_Interface2Vtbl const *const _vtbl;
};


extern M2_InterfaceID const M2_Interface2_ID;


void M2_Interface2_new(M2_Interface2 *const self,
                       M2_Interface2Vtbl const *const vtbl);


// Check that the vtbl referenced by self is indeed the expected vtbl
#if 0
// return ok() if it is, error otherwise.
void M2_Interface2_try_check_vtbl(M2_Interface2 const *const self,
                                  M2_Result *const ret
                                 );
#endif
void M2_Interface2_check_vtbl_(char const *file, size_t line,
                               M2_Interface2 const *const self);
#define M2_Interface2_check_vtbl(self) M2_Interface2_check_vtbl_(__FILE__, __LINE__, self)


// Return the interface ptr for the interface identified by iid.
// if one such exists, return ok(), and ptr in *value (will need casting).
// if does not exist or on error, return Err().
void M2_Interface2_query_interface(M2_Interface2 const *const self,
                                   M2_InterfaceID const *const iid,
                                   void const **const val,
                                   M2_Result *const ret
                                  );
void M2_Interface2_query_interface_mut(M2_Interface2 *const self,
                                       M2_InterfaceID const *const iid,
                                       void **const val,
                                       M2_Result *const ret
                                      );


// Example of getter/setters and indeed any other redirectable method.
void M2_Interface2_get_value(M2_Interface2 const *const self,
                             M2_Value *const val,
                             M2_Result *const ret
                            );


void M2_Interface2_set_value(M2_Interface2 *const self,
                             M2_Value const *const arg,
                             M2_Result *const ret
                            );


void M2_Interface2_get_objects(M2_Interface2 const *const self,
                               M2_Value *const val,
                               M2_Result *const ret
                              );


void M2_Interface2_set_objects(M2_Interface2 *const self,
                               M2_Value const *const arg,
                               M2_Result *const ret
                              );

#endif//M2_INTERFACE2_H
