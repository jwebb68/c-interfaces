#ifndef M4_OBJECT1_H
#define M4_OBJECT1_H

typedef struct M4_Object1_s M4_Object1;
struct M4_Object1_s;

#include "m4-interface.h"
#include "m4-interface1.h"
#include "m4-interface3.h"
#include "m4-result.h"
#include "m4-value.h"

struct M4_Object1_s {
    M4_Value value1;
    M4_Value value2;
    M4_Value value3;

    // interface members, can go anywhere..
    M4_Interface1 iface1;
    M4_Interface3 iface3;
    // TODO: maybe wrap interface members in a DECLARE_INTERFACE(ifacecls) macro..
};

void M4_Object1_destroy(M4_Object1 *const self);

// struct must be bitwise copyable..
// keep things off the heap if possible, that way stack/global usage is possible.
void M4_Object1_new(M4_Object1 *const self);

void M4_Object1_query_interface(
    M4_Object1 const *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **const out);
void M4_Object1_query_interface_mut(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **const out);

void M4_Object1_foo(M4_Object1 *const self);
void M4_Object1_foo2(M4_Object1 *const self, M4_Result *res);
void M4_Object1_foo3(M4_Result *res, M4_Object1 *const self);

void M4_Object1_get_value1(
    M4_Object1 const *const self,
    M4_Result *const ret,
    M4_Value *const val
);
void M4_Object1_set_value1(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
);
void M4_Object1_get_value2(
    M4_Object1 const *const self,
    M4_Result *const ret,
    M4_Value *const val
);
void M4_Object1_set_value2(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
);
void M4_Object1_get_value3(
    M4_Object1 const *const self,
    M4_Result *const ret,
    M4_Value *const val
);
void M4_Object1_set_value3(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
);
void M4_Object1_action1(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_Value const *const arg,
    M4_Value *const out
);
void M4_Object1_action2(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_Value const *const arg,
    M4_Value *const out
);

#endif//M4_OBJECT1_H
