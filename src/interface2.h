#ifndef INTERFACE2_H
#define INTERFACE2_H

typedef struct _Interface2 Interface2;
typedef struct _Interface2Vtbl Interface2Vtbl;

#include "result.h"
#include "value.h"
#include "interface.h"
#include <stddef.h>

struct _Interface2Vtbl {
    size_t offset;
    Result (*query_interface)(const Interface2 *self, const InterfaceID *iid, void **value);
    ////
    Result (*get_value)(const Interface2 *self, Value *value);
    Result (*set_value)(Interface2 *self, const Value *value);
    Result (*get_objects)(const Interface2 *self, Value *value);
    Result (*set_objects)(Interface2 *self, const Value *value);
};

struct _Interface2 {
    // vtbl must be const
    const Interface2Vtbl * const _vtbl;
};

extern const InterfaceID Interface2_ID;


Result Interface2_query_interface(const Interface2 *self, const InterfaceID *iid, void **value);

Result Interface2_get_value(const Interface2 *self, Value *value);
Result Interface2_set_value(Interface2 *self, const Value *value);
Result Interface2_get_objects(const Interface2 *self, Value *value);
Result Interface2_set_objects(Interface2 *self, const Value *value);

#endif//INTERFACE2_H
