#ifndef M2_OBJECT2_H
#define M2_OBJECT2_H


typedef struct M2_Object2_s M2_Object2;
struct M2_Object2_s;


#include "m2-interface.h"
#include "m2-interface1.h"
#include "m2-interface2.h"
#include "m2-result.h"
#include "m2-value.h"


struct M2_Object2_s {
    M2_Value value;

    // interface members, can go anywhere..
    M2_Interface1 iface1;
    M2_Interface2 iface2;
};


void M2_Object2_destroy(M2_Object2 *const self);


void M2_Object2_new(M2_Object2 *self);


void M2_Object2_query_interface(M2_Object2 const *const self,
                                M2_InterfaceID const *const iid,
                                void const **const val,
                                M2_Result *const ret
                               );


void M2_Object2_query_interface_mut(M2_Object2 *const self,
                                    M2_InterfaceID const *const iid,
                                    void **const val,
                                    M2_Result *const ret
                                   );


void M2_Object2_foo(M2_Object2 *const self);


void M2_Object2_foo2(M2_Object2 *const self,
                     M2_Result *const ret);


void M2_Object2_get_value(M2_Object2 const *const self,
                          M2_Value *const val,
                          M2_Result *const ret
                         );


void M2_Object2_set_value(M2_Object2 *const self,
                          M2_Value const *const arg,
                          M2_Result *const ret
                         );


void M2_Object2_get_objects(M2_Object2 const *const self,
                            M2_Value *const val,
                            M2_Result *const ret
                           );


void M2_Object2_set_objects(M2_Object2 *const self,
                            M2_Value const *const arg,
                            M2_Result *const ret
                           );


#endif//M2_OBJECT2_H
