#include "object1.h"

#include "carray.h"
#include "interface.h"
#include "result.h"

#include <inttypes.h>
#include <memory.h>
#include <stddef.h>


static const InterfaceLookup Object1_ifaces[] = {
{&Interface1_ID, offsetof(Object1, iface1)},
};
// TODO maybe wrap this in DEFINE_INTERFACEMAP(cls)/INTERFACE()/END_INTERFACEMAP macros

Result Object1_query_interface(const Object1 *self, const InterfaceID *iid, void **ret) {
    // no guard needed here as not relying on values in the object struct instance.
    // although a guard could be added to verify it's an instance of the expected type.
    return Interface_query_interface(CARRAY_BEGIN(Object1_ifaces), CARRAY_END(Object1_ifaces), self, iid, ret);
}

///////////////////////////////////////////////////////////////////////////////

static const Object1 *Object1_Interface1_getobjptr(const Interface1 *self) {
    const Object1 *oself = (const Object1 *)((const uint8_t *)self - self->_vtbl->offset);
    return oself;
}

static Object1 *Object1_Interface1_getobjptr_mut(Interface1 *self) {
    Object1 *oself = (Object1 *)((uint8_t *)self - self->_vtbl->offset);
    return oself;
}

Result Object1_Interface1_query_interface(const Interface1 *self, const InterfaceID *iid, void **ret) {
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    RESULT_TRY(Interface1_check_guard(self));
    return Object1_query_interface(Object1_Interface1_getobjptr(self), iid, ret);
}


Result Object1_Interface1_get_value(const Interface1 *self, Value *ret) {
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    RESULT_TRY(Interface1_check_guard(self));
    return Object1_get_value(Object1_Interface1_getobjptr(self), ret);
}
Result Object1_Interface1_set_value(Interface1 *self, const Value *arg) {
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    RESULT_TRY(Interface1_check_guard(self));
    return Object1_set_value(Object1_Interface1_getobjptr_mut(self), arg);
}

static const Interface1Vtbl Object1_Interface1_vtbl = {
    &Interface1_ID,
    offsetof(Object1, iface1),
    Object1_Interface1_query_interface,
    Interface1_get,
    Interface1_set,
    Interface1_action,
    Object1_Interface1_get_value,
    Object1_Interface1_set_value
};

///////////////////////////////////////////////////////////////////////////////

void Object1_destroy(Object1 *self) {
    // completely corrupt object, including interface vtlb pointers (oops).
    // should be able to use any value here, but
    // on amd64 without a os level function to determine readability, then
    // use 0x0 (NULL)
    memset(self, 0x0, sizeof(*self));
}

Object1 Object1_new() {
    // prob will be initialising value.
    // and vtbls need to be initialised via init list as thats the only way to
    // init const * const members.
    Object1 inst = { 0, &Object1_Interface1_vtbl};
    // need to stop vtbls in interfaces being mutable in a mutable Object1 inst.
    // they shouldn't be.
    return inst;
}

Result Object1_get_value(const Object1 *self, Value *ret) {
      *ret = self->value;
      return Result_ok(0);
}

Result Object1_set_value(Object1 *self, const Value *arg) {
      self->value = *arg;
      return Result_ok(0);
}
