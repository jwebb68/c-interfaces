#ifndef OBJECT1_H
#define OBJECT1_H

#include "value.h"
#include "interface1.h"
#include "interface2.h"
#include "interface.h"
#include "result.h"

typedef struct _Object1 {
    Value value;

    // interface members, can go anywhere..
    Interface1 iface1;
    Interface2 iface2;
} Object1;

void Object1_destroy(Object1 *self);
Object1 Object1_new();

Result Object1_query_interface(const Object1 *self, const InterfaceID *iid, void **value);

Result Object1_get_value(const Object1 *self, Value *value);
Result Object1_set_value(Object1 *self, const Value *value);
Result Object1_get_objects(const Object1 *self, Value *value);
Result Object1_set_objects(Object1 *self, const Value *value);

#endif//OBJECT1_H
