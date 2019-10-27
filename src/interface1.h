#ifndef INTERFACE1_H
#define INTERFACE1_H

typedef struct _Interface1Vtbl Interface1Vtbl;
typedef struct _Interface1 Interface1;
struct _Interface1Vtbl;
struct _Interface1;

#include "interface.h"
#include "result.h"
#include "value.h"

#include <stddef.h>

// each interface needs:
// 1. an offset of iface member of class implementing interface (see object1.c)
// 2. a function to allow finding other interfaces from any interface (see object1.c)
// 3. an id of the interface, unique across all interfaces.

struct _Interface1Vtbl {
    // for embedded, give ability to check that vtbl is the expected one
    // and the vtbl pointer has not been corrupted, whic, if left unchecked
    // would result in calling into some random part of the address space.
    // It's something, if weak.
    const InterfaceID *guard;

    size_t offset;
    ///
    Result (*query_interface)(const Interface1 *self, const InterfaceID *iid, void **ret);
    ////
    Result (*get)(const Interface1 *self, AttributeID aid, Value *ret);
    Result (*set)(Interface1 *self, AttributeID aid, const Value *arg);
    Result (*action)(Interface1 *self, ActionID aid, const Value *arg, Value *ret);
    ////
    Result (*get_value)(const Interface1 *self, Value *ret);
    Result (*set_value)(Interface1 *self, const Value *arg);
};

struct _Interface1 {
    // vtbl must be const
    const Interface1Vtbl * const _vtbl;
};

extern const InterfaceID Interface1_ID;

// Check that the interface referenced by self is indeed an Interface1
// return ok() if it is, error otherwise.
Result Interface1_check_guard(const Interface1 *self);

// Return the interface ptr for the interface identified by iid.
// if one such exists, return ok(), and ptr in *value (will need casting).
// if does not exist or on error, return Err().
Result Interface1_query_interface(const Interface1 *self, const InterfaceID *iid, void **value);

// a form of dynamic dispatching using an interface using ids for props/actions
// (these names come from dlms/cosem)
Result Interface1_get(const Interface1 *self, AttributeID aid, Value *value);
Result Interface1_set(Interface1 *self, AttributeID aid, const Value *value);
Result Interface1_action(Interface1 *self, ActionID aid, const Value *arg, Value *ret);

// Example of getter/setters and indeed any other redirectable method.
Result Interface1_get_value(const Interface1 *self, Value *value);
Result Interface1_set_value(Interface1 *self, const Value *value);


#endif//INTERFACE1_H
