#ifndef M4_OBJECT2_H
#define M4_OBJECT2_H


typedef struct M4_Object2_s M4_Object2;
struct M4_Object2_s;


#include "m4-interface.h"
#include "m4-interface1.h"
#include "m4-interface2.h"
#include "m4-result.h"
#include "m4-value.h"


struct M4_Object2_s {
    M4_Value value;

    // interface members, can go anywhere..
    M4_Interface1 iface1;
    M4_Interface2 iface2;
};


void M4_Object2_destroy(M4_Object2 *const self);


void M4_Object2_new(M4_Object2 *self);


void M4_Object2_query_interface(
    M4_Object2 const *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **const val
);


void M4_Object2_query_interface_mut(
    M4_Object2 *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **const val
);


void M4_Object2_foo(M4_Object2 *const self);


void M4_Object2_foo2(M4_Object2 *const self,
                     M4_Result *const ret);

void M4_Object2_foo3(M4_Result *const ret,
                     M4_Object2 *const self
                    );


void M4_Object2_get_value(
    M4_Object2 const *const self,
    M4_Result *const ret,
    M4_Value *const val
);


void M4_Object2_set_value(
    M4_Object2 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
);


void M4_Object2_get_objects(
    M4_Object2 const *const self,
    M4_Result *const ret,
    M4_Value *const val
);


void M4_Object2_set_objects(
    M4_Object2 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
);


#endif//M4_OBJECT2_H
