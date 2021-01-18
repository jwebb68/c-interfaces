#ifndef M2_OBJECT1_H
#define M2_OBJECT1_H

typedef struct M2_Object1_s M2_Object1;
struct M2_Object1_s;

#include "m2-interface.h"
#include "m2-interface1.h"
#include "m2-interface2.h"
#include "m2-result.h"
#include "m2-value.h"

struct M2_Object1_s {
    M2_Value value;

    // interface members, can go anywhere..
    M2_Interface1 iface1;
    // TODO: maybe wrap interface members in a DECLARE_INTERFACE(ifacecls) macro..
};

void M2_Object1_destroy(M2_Object1 *const self);

// struct must be bitwise copyable..
// keep things off the heap if possible, that way stack/global usage is possible.
void M2_Object1_new(M2_Object1 *const self);

void M2_Object1_query_interface(M2_Object1 const *const self,
                                M2_InterfaceID const *const iid, void const **const val, M2_Result *res);
void M2_Object1_query_interface_mut(M2_Object1 *const self,
                                    M2_InterfaceID const *const iid, void **const val, M2_Result *res);

void M2_Object1_foo(M2_Object1 *const self);
void M2_Object1_foo2(M2_Object1 *const self, M2_Result *res);

void M2_Object1_get_value(M2_Object1 const *const self, M2_Value *const val,
                          M2_Result *const ret
                         );
void M2_Object1_set_value(M2_Object1 *const self, M2_Value const *const arg,
                          M2_Result *const ret
                         );

#endif//M2_OBJECT1_H
