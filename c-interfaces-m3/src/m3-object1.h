#ifndef M3_OBJECT1_H
#define M3_OBJECT1_H

typedef struct M3_Object1_s M3_Object1;
struct M3_Object1_s;

#include "m3-interface.h"
#include "m3-interface1.h"
#include "m3-interface3.h"
#include "m3-result.h"
#include "m3-value.h"

struct M3_Object1_s {
    M3_Value value1;
    M3_Value value2;
    M3_Value value3;

    // interface members, can go anywhere..
    M3_Interface1 iface1;
    M3_Interface3 iface3;
    // TODO: maybe wrap interface members in a DECLARE_INTERFACE(ifacecls) macro..
};

void M3_Object1_destroy(M3_Object1 *const self);

// struct must be bitwise copyable..
// keep things off the heap if possible, that way stack/global usage is possible.
void M3_Object1_new(M3_Object1 *const self);

void M3_Object1_query_interface(M3_Result *const ret,
                                M3_Object1 const *const self,
                                M3_InterfaceID const *const iid,
                                void const **const out);
void M3_Object1_query_interface_mut(M3_Result *const ret,
                                    M3_Object1 *const self,
                                    M3_InterfaceID const *const iid,
                                    void **const out);

void M3_Object1_foo(M3_Object1 *const self);
void M3_Object1_foo2(M3_Object1 *const self, M3_Result *res);
void M3_Object1_foo3(M3_Result *res, M3_Object1 *const self);

void M3_Object1_get_value1(M3_Result *const ret,
                           M3_Object1 const *const self,
                           M3_Value *const val
                          );
void M3_Object1_set_value1(M3_Result *const ret,
                           M3_Object1 *const self,
                           M3_Value const *const arg
                          );
void M3_Object1_get_value2(M3_Result *const ret,
                           M3_Object1 const *const self,
                           M3_Value *const val
                          );
void M3_Object1_set_value2(M3_Result *const ret,
                           M3_Object1 *const self,
                           M3_Value const *const arg
                          );
void M3_Object1_get_value3(M3_Result *const ret,
                           M3_Object1 const *const self,
                           M3_Value *const val
                          );
void M3_Object1_set_value3(M3_Result *const ret,
                           M3_Object1 *const self,
                           M3_Value const *const arg
                          );
void M3_Object1_action1(M3_Result *const ret,
                        M3_Object1 *const self,
                        M3_Value const *const arg,
                        M3_Value *const out
                       );
void M3_Object1_action2(M3_Result *const ret,
                        M3_Object1 *const self,
                        M3_Value const *const arg,
                        M3_Value *const out
                       );

#endif//M3_OBJECT1_H
