#ifndef INTERFACE1_H
#define INTERFACE1_H

typedef struct _Interface1Vtbl Interface1Vtbl;
typedef struct _Interface1 Interface1;

#include "interface.h"
#include "result.h"
#include "value.h"

#include <stddef.h>

// each interface needs:
// 1. an offset of iface member of class implementing interface (see object1.c)
// 2. a function to allow finding other interfaces from any interface (see object1.c)
// 3. an id of the interface.

struct _Interface1Vtbl {
    size_t offset;
    Result (*query_interface)(const Interface1 *self, const InterfaceID *iid, void **value);
    ////
    Result (*get_value)(const Interface1 *self, Value *value);
    Result (*set_value)(Interface1 *self, const Value *value);
};

struct _Interface1 {
    // vtbl must be const
    const Interface1Vtbl * const _vtbl;
};

extern const InterfaceID Interface1_ID;

Result Interface1_query_interface(const Interface1 *self, const InterfaceID *iid, void **value);

Result Interface1_get_value(const Interface1 *self, Value *value);
Result Interface1_set_value(Interface1 *self, Value *value);


#endif//INTERFACE1_H
