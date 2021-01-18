#ifndef R2_OBJECT2_H
#define R2_OBJECT2_H

typedef struct R2_Object2_s R2_Object2;
struct R2_Object2_s;

#include "r2-interface.h"
#include "r2-interface1.h"
#include "r2-interface2.h"
#include "r2-result.h"
#include "r2-value.h"

struct R2_Object2_s {
    R2_Value value;

    // interface members, can go anywhere..
    R2_Interface1 iface1;
    R2_Interface2 iface2;
};

void R2_Object2_destroy(R2_Object2 *const self);

R2_Object2 R2_Object2_new(void);

R2_Result R2_Object2_query_interface(R2_Object2 const *const self,
                                     R2_InterfaceID const *const iid, void const **const ret);
R2_Result R2_Object2_query_interface_mut(R2_Object2 *const self,
        R2_InterfaceID const *const iid, void **const ret);

R2_Result R2_Object2_get_value(R2_Object2 const *const self,
                               R2_Value *const ret);
R2_Result R2_Object2_set_value(R2_Object2 *const self,
                               R2_Value const *const arg);
R2_Result R2_Object2_get_objects(R2_Object2 const *const self,
                                 R2_Value *const ret);
R2_Result R2_Object2_set_objects(R2_Object2 *const self,
                                 R2_Value const *const arg);

#endif//R2_OBJECT2_H
