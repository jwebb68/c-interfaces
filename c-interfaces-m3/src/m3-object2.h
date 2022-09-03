#ifndef M3_OBJECT2_H
#define M3_OBJECT2_H


typedef struct M3_Object2_s M3_Object2;
struct M3_Object2_s;


#include "m3-interface.h"
#include "m3-interface1.h"
#include "m3-interface2.h"
#include "m3-result.h"
#include "m3-value.h"


struct M3_Object2_s {
    M3_Value value;

    // interface members, can go anywhere..
    M3_Interface1 iface1;
    M3_Interface2 iface2;
};


void M3_Object2_destroy(M3_Object2 *const self);


void M3_Object2_new(M3_Object2 *self);


void M3_Object2_query_interface(M3_Result *const ret,
                                M3_Object2 const *const self,
                                M3_InterfaceID const *const iid,
                                void const **const val
                               );


void M3_Object2_query_interface_mut(M3_Result *const ret,
                                    M3_Object2 *const self,
                                    M3_InterfaceID const *const iid,
                                    void **const val
                                   );


void M3_Object2_foo(M3_Object2 *const self);


void M3_Object2_foo2(M3_Object2 *const self,
                     M3_Result *const ret);

void M3_Object2_foo3(M3_Result *const ret,
                     M3_Object2 *const self
                    );


void M3_Object2_get_value(M3_Result *const ret,
                          M3_Object2 const *const self,
                          M3_Value *const val
                         );


void M3_Object2_set_value(M3_Result *const ret,
                          M3_Object2 *const self,
                          M3_Value const *const arg
                         );


void M3_Object2_get_objects(M3_Result *const ret,
                            M3_Object2 const *const self,
                            M3_Value *const val
                           );


void M3_Object2_set_objects(M3_Result *const ret,
                            M3_Object2 *const self,
                            M3_Value const *const arg
                           );


#endif//M3_OBJECT2_H
