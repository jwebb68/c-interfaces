#include "object2.h"

#include "carray.h"
#include "interface.h"

#include <inttypes.h>
#include <memory.h>
#include <stddef.h>

//////////////////////////////////////////////////////////////////////////////

static const InterfaceLookup Object2_ifaces[] = {
{&Interface1_ID, offsetof(Object2, iface1)},
{&Interface2_ID, offsetof(Object2, iface2)},
};

Result Object2_query_interface(const Object2 *self, const InterfaceID *iid, void **ret) {
    // no guard needed here as not relying on values in the object struct instance.
    return Interface_query_interface(CARRAY_BEGIN(Object2_ifaces), CARRAY_END(Object2_ifaces), self, iid, ret);
}

//////////////////////////////////////////////////////////////////////////////

static const Object2 *Object2_Interface1_getobjptr(const Interface1 *self) {
    const Object2 *oself = (const Object2 *)((const uint8_t *)self - self->_vtbl->offset);
    return oself;
}

static Object2 *Object2_Interface1_getobjptr_mut(Interface1 *self) {
    Object2 *oself = (Object2 *)((uint8_t *)self - self->_vtbl->offset);
    return oself;
}


Result Object2_Interface1_query_interface(const Interface1 *self, const InterfaceID *iid, void **ret) {
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    RESULT_TRY(Interface1_check_guard(self));
    return Object2_query_interface(Object2_Interface1_getobjptr(self), iid, ret);
}

Result Object2_Interface1_get_value(const Interface1 *self, Value *ret) {
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    RESULT_TRY(Interface1_check_guard(self));
    return Object2_get_value(Object2_Interface1_getobjptr(self), ret);
}

Result Object2_Interface1_set_value(Interface1 *self, const Value *arg) {
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    RESULT_TRY(Interface1_check_guard(self));
    return Object2_set_value(Object2_Interface1_getobjptr_mut(self), arg);
}

static const Interface1Vtbl Object2_Interface1_vtbl = {
    &Interface1_ID,
    offsetof(Object2, iface1),
    Object2_Interface1_query_interface,
    Interface1_get,
    Interface1_set,
    Interface1_action,
    Object2_Interface1_get_value,
    Object2_Interface1_set_value
};

/////////////////////////////////////////////////////////////////////////////

static const Object2 *Object2_Interface2_getobjptr(const Interface2 *self) {
    const Object2 *oself = (const Object2 *)((const uint8_t *)self - self->_vtbl->offset);
    return oself;
}

static Object2 *Object2_Interface2_getobjptr_mut(Interface2 *self) {
    Object2 *oself = (Object2 *)((uint8_t *)self - self->_vtbl->offset);
    return oself;
}

Result Object2_Interface2_query_interface(const Interface2 *self, const InterfaceID *iid, void **ret) {
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    RESULT_TRY(Interface2_check_guard(self));
    return Object2_query_interface(Object2_Interface2_getobjptr(self), iid, ret);
}

Result Object2_Interface2_get_value(const Interface2 *self, Value *ret) {
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    RESULT_TRY(Interface2_check_guard(self));
    return Object2_get_value(Object2_Interface2_getobjptr(self), ret);
}

Result Object2_Interface2_set_value(Interface2 *self, const Value *arg) {
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    RESULT_TRY(Interface2_check_guard(self));
    return Object2_set_value(Object2_Interface2_getobjptr_mut(self), arg);
}

Result Object2_Interface2_get_objects(const Interface2 *self, Value *ret) {
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    RESULT_TRY(Interface2_check_guard(self));
    return Object2_get_objects(Object2_Interface2_getobjptr(self), ret);
}

Result Object2_Interface2_set_objects(Interface2 *self, const Value *arg) {
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    RESULT_TRY(Interface2_check_guard(self));
    return Object2_set_objects(Object2_Interface2_getobjptr_mut(self), arg);
}

static const Interface2Vtbl Object2_Interface2_vtbl = {
    &Interface2_ID,
    offsetof(Object2, iface2),
    Object2_Interface2_query_interface,
    Object2_Interface2_get_value,
    Object2_Interface2_set_value,
    Object2_Interface2_get_objects,
    Object2_Interface2_set_objects
};

///////////////////////////////////////////////////////////////////////////////

void Object2_destroy(Object2 *self) {
    // completely corrupt object, including interface vtlb pointers (oops).
    // should be able to use any value here, but
    // on amd64 without a os level function to determine readability, then
    // use 0x0 (NULL)
    memset(self, 0x0, sizeof(*self));
}

Object2 Object2_new() {
    // prob will be initialising value.
    // and vtbls need to be initialised via init list as thats the only way to
    // init const * const members.
    Object2 inst = { 0, &Object2_Interface1_vtbl, &Object2_Interface2_vtbl };
    // need to stop vtbls in interfaces being mutable in a mutable Object2 inst.
    // they shouldn't be.
    return inst;
}

Result Object2_get_value(const Object2 *self, Value *ret) {
      *ret = self->value;
      return Result_ok(0);
}

Result Object2_set_value(Object2 *self, const Value *arg) {
      self->value = *arg;
      return Result_ok(0);
}

Result Object2_get_objects(const Object2 *self, Value *ret) {
    return Result_err(Err_NotImplemented);
}

Result Object2_set_objects(Object2 *self, const Value *arg) {
    return Result_err(Err_NotImplemented);
}
