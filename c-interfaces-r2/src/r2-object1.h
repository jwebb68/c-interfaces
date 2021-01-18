#ifndef R2_OBJECT1_H
#define R2_OBJECT1_H

typedef struct R2_Object1_s R2_Object1;
struct R2_Object1_s;

#include "r2-interface.h"
#include "r2-interface1.h"
#include "r2-interface2.h"
#include "r2-result.h"
#include "r2-value.h"

struct R2_Object1_s {
    R2_Value value;

    // interface members, can go anywhere..
    R2_Interface1 iface1;
    // TODO: maybe wrap interface members in a DECLARE_INTERFACE(ifacecls) macro..
};

void R2_Object1_destroy(R2_Object1 *const self);

// struct must be bitwise copyable..
// keep things off the heap if possible, that way stack/global usage is possible.
R2_Object1 R2_Object1_new(void);

R2_Result R2_Object1_query_interface(R2_Object1 const *const self,
                                     R2_InterfaceID const *const iid, void const **const val);
R2_Result R2_Object1_query_interface_mut(R2_Object1 *const self,
        R2_InterfaceID const *const iid, void **const val);

R2_Result R2_Object1_get_value(R2_Object1 const *const self,
                               R2_Value *const val);
R2_Result R2_Object1_set_value(R2_Object1 *const self,
                               R2_Value const *const arg);

#endif//R2_OBJECT1_H
