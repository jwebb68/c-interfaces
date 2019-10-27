#include "interface1.h"

#include "carray.h"

const InterfaceID Interface1_ID = "Interface1";

// note: platform specific.
// currently matches the memset values in the destroy functions
// but really shouldn't need to match values.
// but don't know how to spot non-readable memory in linux.
static bool is_ptr_readable(const void *ptr) {
    return (ptr != NULL);
}

Result Interface1_check_guard(const Interface1 *self) {
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
    if (!is_ptr_readable(self)) return Result_err(Err_InvalidInterface);
    if (!is_ptr_readable(self->_vtbl)) return Result_err(Err_InvalidInterface);
    return Interface_check_guard(&Interface1_ID, self->_vtbl->guard);
}

Result Interface1_query_interface(const Interface1 *self, const InterfaceID *iid, void **ret) {
    RESULT_TRY(Interface1_check_guard(self));
    return self->_vtbl->query_interface(self, iid, ret);
}

/////////////////////////////////////////////////////////////////////////////

// an example of dynamic dispatch using ids for properties/actions
// needs re-implementing per interface though because of typed ptr in functon
// calls (and I don't want to remove that.. it's bad enough using void *)

typedef struct _PropertyDef {
    // use an id instead of array position so I can have gaps in the number
    // range and have a smaller array in the resultant image.
    AttributeID aid;
    Result (*get)(const Interface1 *self, Value *ret);
    Result (*set)(Interface1 *self, const Value *arg);
} PropertyDef;

typedef struct _ActionDef {
    ActionID aid;
    Result (*action)(Interface1 *self, const Value *arg, Value *ret);
} ActionDef;

static const PropertyDef Interface1_propdefs[] = {
    {1, Interface1_get_value, Interface1_set_value},
};
// TODO: maybe wrap this into a DEFINE_PROPMAP/PROP()/END_PROPMAP macros

static const ActionDef Interface1_actiondefs[] = {
};
// TODO: maybe wrap this into a DEFINE_ACTIONMAP/ACTION()/END_ACTIONMAP macros

static Result Interface1_Propdef_lookup(const PropertyDef *begin, const PropertyDef *end, AttributeID aid, const PropertyDef **ret) {
    for (const PropertyDef *it = begin;it != end; ++it) {
        if (it->aid == aid) {
            *ret = it;
            return Result_ok(0);
        }
    }
    return Result_err(Err_InvalidAttributeID);
}

static Result Interface1_Actiondef_lookup(const ActionDef *begin, const ActionDef *end, AttributeID aid, const ActionDef **ret) {
    for (const ActionDef *it = begin;it != end; ++it) {
        if (it->aid == aid) {
            *ret = it;
            return Result_ok(0);
        }
    }
    return Result_err(Err_InvalidActionID);
}

Result Interface1_get(const Interface1 *self, AttributeID aid, Value *ret) {
    RESULT_TRY(Interface1_check_guard(self));
    const PropertyDef *def;
    RESULT_TRY(Interface1_Propdef_lookup(CARRAY_BEGIN(Interface1_propdefs), CARRAY_END(Interface1_propdefs), aid, &def));
    return def->get(self, ret);
}

Result Interface1_set(Interface1 *self, AttributeID aid, const Value *arg) {
    RESULT_TRY(Interface1_check_guard(self));
    const PropertyDef *def;
    RESULT_TRY(Interface1_Propdef_lookup(CARRAY_BEGIN(Interface1_propdefs), CARRAY_END(Interface1_propdefs), aid, &def));
    return def->set(self, arg);
}

Result Interface1_action(Interface1 *self, ActionID aid, const Value *arg, Value *ret) {
    RESULT_TRY(Interface1_check_guard(self));
    const ActionDef *def;
    RESULT_TRY(Interface1_Actiondef_lookup(CARRAY_BEGIN(Interface1_actiondefs), CARRAY_END(Interface1_actiondefs), aid, &def));
    return def->action(self, arg, ret);
}

/////////////////////////////////////////////////////////////////////////////

Result Interface1_get_value(const Interface1 *self, Value *ret) {
    RESULT_TRY(Interface1_check_guard(self));
    return self->_vtbl->get_value(self, ret);
}

Result Interface1_set_value(Interface1 *self, const Value *arg) {
    RESULT_TRY(Interface1_check_guard(self));
    return self->_vtbl->set_value(self, arg);
}
