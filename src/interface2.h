#ifndef INTERFACE2_H
#define INTERFACE2_H

typedef struct _Interface2Vtbl Interface2Vtbl;
typedef struct _Interface2 Interface2;
struct _Interface2Vtbl;
struct _Interface2;

#include "interface.h"
#include "result.h"
#include "value.h"

#include <stddef.h>

// each interface needs:
// 1. an offset of iface member of class implementing interface (see object1.c)
// 2. a function to allow finding other interfaces from any interface (see object1.c)
// 3. an id of the interface.

struct _Interface2Vtbl {
    // for embedded, give ability to check that vtbl is the expected one
    // and the vtbl pointer has not been corrupted, whic, if left unchecked
    // would result in calling into some random part of the address space.
    // It's something, if weak.
    const InterfaceID *guard;

    size_t offset;
    Result (*query_interface)(const Interface2 *self, const InterfaceID *iid, void **ret);
    ////
    Result (*get_value)(const Interface2 *self, Value *ret);
    Result (*set_value)(Interface2 *self, const Value *arg);
    Result (*get_objects)(const Interface2 *self, Value *ret);
    Result (*set_objects)(Interface2 *self, const Value *arg);
};

struct _Interface2 {
    // vtbl must be const
    const Interface2Vtbl * const _vtbl;
};

extern const InterfaceID Interface2_ID;

// Check that the interface referenced by self is indeed an Interface2
// return ok() if it is, error otherwise.
Result Interface2_check_guard(const Interface2 *self);

// Return the interface ptr for the interface identified by iid.
// if one such exists, return ok(), and ptr in *value (will need casting).
// if does not exist or on error, return Err().
Result Interface2_query_interface(const Interface2 *self, const InterfaceID *iid, void **ret);

// Example of getter/setters and indeed any other redirectable method.
Result Interface2_get_value(const Interface2 *self, Value *ret);
Result Interface2_set_value(Interface2 *self, const Value *arg);
Result Interface2_get_objects(const Interface2 *self, Value *ret);
Result Interface2_set_objects(Interface2 *self, const Value *arg);

#endif//INTERFACE2_H
