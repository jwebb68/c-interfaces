#ifndef OBJECT1_H
#define OBJECT1_H

typedef struct _Object1 Object1;
struct _Object1;

#include "interface.h"
#include "interface1.h"
#include "interface2.h"
#include "result.h"
#include "value.h"

struct _Object1 {
    Value value;

    // interface members, can go anywhere..
    Interface1 iface1;
    // TODO: maybe wrap interface members in a DECLARE_INTERFACE(ifacecls) macro..
};

void Object1_destroy(Object1 *self);

// struct must be bitwise copyable..
// keep things off the heap if possible, that way stack/global usage is possible.
Object1 Object1_new();

Result Object1_query_interface(const Object1 *self, const InterfaceID *iid, void **ret);

Result Object1_get_value(const Object1 *self, Value *ret);
Result Object1_set_value(Object1 *self, const Value *arg);

#endif//OBJECT1_H
