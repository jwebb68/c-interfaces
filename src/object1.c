#include "object1.h"
#include "inttypes.h"
#include "stddef.h"


//#define QI_IN_CODE
#ifdef QI_IN_CODE
Result Object1_query_interface(const Object1 *self, const InterfaceID *iid, void **value) {
    // could do this with a lookup table (iid + offset to iface
    if (*iid == Interface1_ID) {
       *value = (void *)&self->iface1;
       return Result_ok(0);
    } else if (*iid == Interface2_ID) {
       *value = (void *)&self->iface2;
       return Result_ok(0);
    }
    return Result_err(Err_InvalidParam);
}
//or:
#else//defined(QI_IN_DATA)
typedef struct _InterfaceLookup {
    const InterfaceID *iid;
    size_t offset;
} InterfaceLookup;
static const InterfaceLookup Object1_ifaces[] = {
{&Interface1_ID, offsetof(Object1, iface1)},
{&Interface2_ID, offsetof(Object1, iface2)},
};
#define CARRAY_COUNT(carray) (sizeof(carray)/sizeof(carray[0]))
Result Object1_query_interface(const Object1 *self, const InterfaceID *iid, void **value) {
    for (size_t idx=0; idx < CARRAY_COUNT(Object1_ifaces); ++idx) {
        const InterfaceLookup *elt = &Object1_ifaces[idx];
        if (elt->iid == iid) {
            // nasty hobbitses, casting away const and type.
            // but how else to get it generic in C..
            *value = (void *)((const uint8_t *)self + elt->offset);
            return Result_ok(0);
        }
    }
    return Result_err(1);
}
#endif//defined(QI_IN_DATA)


Result Object1_Interface1_query_interface(const Interface1 *self, const InterfaceID *iid, void **value) {
    const Object1 *oself = (const Object1 *)((const uint8_t *)self - self->_vtbl->offset);
    return Object1_query_interface(oself, iid, value);
}
Result Object1_Interface1_get_value(const Interface1 *self, Value *value) {
    const Object1 *oself = (const Object1 *)((const uint8_t *)self - self->_vtbl->offset);
    return Object1_get_value(oself, value);
}
Result Object1_Interface1_set_value(Interface1 *self, const Value *value) {
    Object1 *oself = (Object1 *)((uint8_t *)self - self->_vtbl->offset);
    return Object1_set_value(oself, value);
}

const Interface1Vtbl Object1_Interface1_vtbl = {
    offsetof(Object1, iface1),
    Object1_Interface1_query_interface,
    Object1_Interface1_get_value,
    Object1_Interface1_set_value
};

Result Object1_Interface2_query_interface(const Interface2 *self, const InterfaceID *iid, void **value) {
    const Object1 *oself = (const Object1 *)((const uint8_t *)self - self->_vtbl->offset);
    return Object1_query_interface(oself, iid, value);
}
Result Object1_Interface2_get_value(const Interface2 *self, Value *value) {
    const Object1 *oself = (const Object1 *)((const uint8_t *)self - self->_vtbl->offset);
    return Object1_get_value(oself, value);
}
Result Object1_Interface2_set_value(Interface2 *self, const Value *value) {
    Object1 *oself = (Object1 *)((uint8_t *)self - self->_vtbl->offset);
    return Object1_set_value(oself, value);
}
Result Object1_Interface2_get_objects(const Interface2 *self, Value *value) {
    const Object1 *oself = (const Object1 *)((const uint8_t *)self - self->_vtbl->offset);
    return Object1_get_objects(oself, value);
}
Result Object1_Interface2_set_objects(Interface2 *self, const Value *value) {
    Object1 *oself = (Object1 *)((uint8_t *)self - self->_vtbl->offset);
    return Object1_set_objects(oself, value);
}

const Interface2Vtbl Object1_Interface2_vtbl = {
    offsetof(Object1, iface2),
    Object1_Interface2_query_interface,
    Object1_Interface2_get_value,
    Object1_Interface2_set_value,
    Object1_Interface2_get_objects,
    Object1_Interface2_set_objects
};


void Object1_destroy(Object1 *self) {
}

Object1 Object1_new() {
    // prob will be initialising value.
    // and vtbls need to be initialised via init list as thats the only way to
    // init const * const members.
    Object1 inst = { 0, &Object1_Interface1_vtbl, &Object1_Interface2_vtbl };
    // need to stop vtbls in interfaces being mutable in a mutable Object1 inst.
    // they shouldn't be.
    return inst;
}

Result Object1_get_value(const Object1 *self, Value *value) {
      *value = self->value;
      return Result_ok(0);
}
Result Object1_set_value(Object1 *self, const Value *value) {
      self->value = *value;
      return Result_ok(0);
}
Result Object1_get_objects(const Object1 *self, Value *value) {
    return Result_err(Err_NotImplemented);
}
Result Object1_set_objects(Object1 *self, const Value *value) {
    return Result_err(Err_NotImplemented);
}
