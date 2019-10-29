#include "interface2.h"

const InterfaceID Interface2_ID = "Interface2";

// note: platform specific.
// currently matches the memset values in the destroy functions
// but really shouldn't need to match values.
// but don't know how to spot non-readable memory in linux.
static bool is_ptr_readable(const void *ptr) {
    return (ptr != NULL);
}

Result Interface2_check_guard(const Interface2 *self) {
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
    if (!is_ptr_readable(self)) return Result_err(Err_InvalidInterface);
    if (!is_ptr_readable(self->_vtbl)) return Result_err(Err_InvalidInterface);
    return Interface_check_guard(&Interface2_ID, self->_vtbl->guard);
}

Result Interface2_query_interface(const Interface2 *self, const InterfaceID *iid, void **ret) {
    RESULT_TRY(Interface2_check_guard(self));
    return self->_vtbl->query_interface(self, iid, ret);
}

/////////////////////////////////////////////////////////////////////////////

Result Interface2_get_value(const Interface2 *self, Value *ret) {
    RESULT_TRY(Interface2_check_guard(self));
    return self->_vtbl->get_value(self, ret);
}

Result Interface2_set_value(Interface2 *self, const Value *arg) {
    RESULT_TRY(Interface2_check_guard(self));
    return self->_vtbl->set_value(self, arg);
}

Result Interface2_get_objects(const Interface2 *self, Value *ret) {
    RESULT_TRY(Interface2_check_guard(self));
    return self->_vtbl->get_objects(self, ret);
}

Result Interface2_set_objects(Interface2 *self, const Value *arg) {
    RESULT_TRY(Interface2_check_guard(self));
    return self->_vtbl->set_objects(self, arg);
}
