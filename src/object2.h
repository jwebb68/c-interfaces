#ifndef OBJECT2_H
#define OBJECT2_H

typedef struct _Object2 Object2;
struct _Object2;

#include "interface.h"
#include "interface1.h"
#include "interface2.h"
#include "result.h"
#include "value.h"

struct _Object2 {
    Value value;

    // interface members, can go anywhere..
    Interface1 iface1;
    Interface2 iface2;
};

void Object2_destroy(Object2 *self);
Object2 Object2_new();

Result Object2_query_interface(const Object2 *self, const InterfaceID *iid, void **ret);

Result Object2_get_value(const Object2 *self, Value *ret);
Result Object2_set_value(Object2 *self, const Value *arg);
Result Object2_get_objects(const Object2 *self, Value *ret);
Result Object2_set_objects(Object2 *self, const Value *arg);

#endif//OBJECT2_H
