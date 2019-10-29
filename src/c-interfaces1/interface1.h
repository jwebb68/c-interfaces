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
    // and the vtbl pointer has not been corrupted, which, if left unchecked
    // would result in calling into some random part of the address space.
    // It's something, if weak.
    const InterfaceID *guard;

    // offset to compute pointer-to-interface struct to it's containing
    // struct start.
    size_t offset;
    /// the 'method' that needs to be on all interfaces.
    // a bit nasty in using void ** for the out-param, would prefer it to be
    // typed with the expected type, but it's C and you cannot do that..
    // Or I could use a Specific Result struct ( Result<void *, ErrorType>) -
    // nice although that is, it adds an extra struct + funcs to maintain
    // and results is manual generics expansion..
    Result (*query_interface)(const Interface1 *self, const InterfaceID *iid, void **ret);

    ////
    // example of some 'methods' that are implemented in this interface.
    // there is an argument to be had regarding keeping implementation out of interfaces.
    Result (*get)(const Interface1 *self, AttributeID aid, Value *ret);
    Result (*set)(Interface1 *self, AttributeID aid, const Value *arg);
    Result (*action)(Interface1 *self, ActionID aid, const Value *arg, Value *ret);

    ////
    Result (*get_value)(const Interface1 *self, Value *ret);
    Result (*set_value)(Interface1 *self, const Value *arg);
};

struct _Interface1 {
    // for embedded (and indeed non-) vtbl must be const
    // this also complies with MISRA.
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
