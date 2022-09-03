#include "m3-object1.h"

#include "m3-carray.h"
#include "m3-interface.h"
#include "m3-result.h"

#include <inttypes.h>
#include <memory.h>
#include <stddef.h>

static M3_InterfaceLookup const M3_Object1_ifaces[] = {
    {&M3_Interface1_ID, offsetof(M3_Object1, iface1)},
    {&M3_Interface3_ID, offsetof(M3_Object1, iface3)},
};
// TODO maybe wrap this in DEFINE_INTERFACEMAP(cls)/INTERFACE()/END_INTERFACEMAP macros


void M3_Object1_query_interface(M3_Result *const ret,
                                M3_Object1 const *const self,
                                M3_InterfaceID const *const iid,
                                void const **const val
                               )
{
    // no guard needed here as not relying on values in the object struct instance.
    // although a guard could be added to verify it's an instance of the expected type.
    M3_Interface_query_interface(ret, self, iid, val,
                                 M3_CARRAY_BEGIN(M3_Object1_ifaces),
                                 M3_CARRAY_END(M3_Object1_ifaces)
                                );
}


void M3_Object1_query_interface_mut(M3_Result *const ret,
                                    M3_Object1 *const self,
                                    M3_InterfaceID const *const iid,
                                    void **const val
                                   )
{
    // no guard needed here as not relying on values in the object struct instance.
    // although a guard could be added to verify it's an instance of the expected type.
    M3_Interface_query_interface_mut(ret, self, iid, val,
                                     M3_CARRAY_BEGIN(M3_Object1_ifaces),
                                     M3_CARRAY_END(M3_Object1_ifaces)
                                    );
}


///////////////////////////////////////////////////////////////////////////////

static M3_Object1 const *M3_Object1_Interface1_getobjptr(
    M3_Interface1 const *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M3_Object1 const *const oself = M3_INTERFACE_GET_OBJPTR(M3_Object1, self);
    return oself;
}


static M3_Object1 *M3_Object1_Interface1_getobjptr_mut(
    M3_Interface1 *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M3_Object1 *const oself = M3_INTERFACE_GET_OBJPTR_MUT(M3_Object1, self);
    return oself;
}

static void M3_Object1_Interface1_query_interface(
    M3_Result *const ret,
    M3_Interface1 const *const self,
    M3_InterfaceID const *const iid,
    void const **const val
)
{
    M3_Object1_query_interface(ret, M3_Object1_Interface1_getobjptr(self),
                               iid,
                               val);
}

static void M3_Object1_Interface1_query_interface_mut(
    M3_Result *const ret,
    M3_Interface1 *const self,
    M3_InterfaceID const *const iid,
    void **const val
)
{
    M3_Object1_query_interface_mut(ret, M3_Object1_Interface1_getobjptr_mut(self),
                                   iid,
                                   val);
}


// ===========================================================================

static void M3_Object1_Interface1_foo(M3_Interface1 *const self)
{
    M3_Object1_foo(M3_Object1_Interface1_getobjptr_mut(self));
}

static void M3_Object1_Interface1_foo2(M3_Interface1 *const self,
                                       M3_Result *const ret)
{
    M3_Object1_foo2(M3_Object1_Interface1_getobjptr_mut(self), ret);
}

static void M3_Object1_Interface1_foo3(M3_Result *const ret,
                                       M3_Interface1 *const self)
{
    M3_Object1_foo3(ret, M3_Object1_Interface1_getobjptr_mut(self));
}


static M3_Interface1Vtbl const M3_Object1_Interface1_vtbl = {
    &M3_Object1_Interface1_vtbl,
    offsetof(M3_Object1, iface1),
    M3_Object1_Interface1_query_interface,
    M3_Object1_Interface1_query_interface_mut,
    M3_Object1_Interface1_foo,
    M3_Object1_Interface1_foo2,
    M3_Object1_Interface1_foo3,
};



// ===========================================================================

static M3_Object1 const *M3_Object1_Interface3_getobjptr(
    M3_Interface3 const *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M3_Object1 const *const oself = M3_INTERFACE_GET_OBJPTR(M3_Object1, self);
    return oself;
}


static M3_Object1 *M3_Object1_Interface3_getobjptr_mut(
    M3_Interface3 *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M3_Object1 *const oself = M3_INTERFACE_GET_OBJPTR_MUT(M3_Object1, self);
    return oself;
}

static void M3_Object1_Interface3_query_interface(
    M3_Result *const ret,
    M3_Interface3 const *const self,
    M3_InterfaceID const *const iid,
    void const **const val
)
{
    M3_Object1_query_interface(ret, M3_Object1_Interface3_getobjptr(self),
                               iid,
                               val);
}

static void M3_Object1_Interface3_query_interface_mut(
    M3_Result *const ret,
    M3_Interface3 *const self,
    M3_InterfaceID const *const iid,
    void **const val
)
{
    M3_Object1_query_interface_mut(ret,
                                   M3_Object1_Interface3_getobjptr_mut(self),
                                   iid,
                                   val);
}

static void M3_Object1_Interface3_get_value1(
    M3_Result *const ret,
    M3_Interface3 const *const self,
    M3_Value *const val)
{
    M3_Object1_get_value1(ret, M3_Object1_Interface3_getobjptr(self), val);
}


static void M3_Object1_Interface3_set_value1(
    M3_Result *const ret,
    M3_Interface3 *const self,
    M3_Value const *const arg
)
{
    M3_Object1_set_value1(ret, M3_Object1_Interface3_getobjptr_mut(self), arg);
}

static void M3_Object1_Interface3_get_value2(
    M3_Result *const ret,
    M3_Interface3 const *const self,
    M3_Value *const val
)
{
    M3_Object1_get_value2(ret, M3_Object1_Interface3_getobjptr(self), val);
}


static void M3_Object1_Interface3_set_value2(
    M3_Result *const ret,
    M3_Interface3 *const self,
    M3_Value const *const arg
)
{
    M3_Object1_set_value2(ret, M3_Object1_Interface3_getobjptr_mut(self), arg);
}


static void M3_Object1_Interface3_get_value3(
    M3_Result *const ret,
    M3_Interface3 const *const self,
    M3_Value *const val)
{
    M3_Object1_get_value3(ret, M3_Object1_Interface3_getobjptr(self), val);
}


static void M3_Object1_Interface3_set_value3(
    M3_Result *const ret,
    M3_Interface3 *const self,
    M3_Value const *const arg
)
{
    M3_Object1_set_value3(ret, M3_Object1_Interface3_getobjptr_mut(self), arg);
}

static void M3_Object1_Interface3_action1(
    M3_Result *const ret,
    M3_Interface3 *const self,
    M3_Value const *const arg,
    M3_Value *const out
)
{
    M3_Object1_action1(ret, M3_Object1_Interface3_getobjptr_mut(self), arg, out);
}


static void M3_Object1_Interface3_action2(
    M3_Result *const ret,
    M3_Interface3 *const self,
    M3_Value const *const arg,
    M3_Value *const out
)
{
    M3_Object1_action2(ret, M3_Object1_Interface3_getobjptr_mut(self), arg, out);
}


static M3_Interface3Vtbl const M3_Object1_Interface3_vtbl = {
    &M3_Object1_Interface3_vtbl,
    offsetof(M3_Object1, iface3),
    M3_Object1_Interface3_query_interface,
    M3_Object1_Interface3_query_interface_mut,
    M3_Interface3_get,
    M3_Interface3_set,
    M3_Interface3_action,
    M3_Object1_Interface3_get_value1,
    M3_Object1_Interface3_set_value1,
    M3_Object1_Interface3_get_value2,
    M3_Object1_Interface3_set_value2,
    M3_Object1_Interface3_get_value3,
    M3_Object1_Interface3_set_value3,
    M3_Object1_Interface3_action1,
    M3_Object1_Interface3_action2,
};






///////////////////////////////////////////////////////////////////////////////

void M3_Object1_destroy(M3_Object1 *const self)
{
    // completely corrupt object, including interface vtlb pointers (oops).
    // should be able to use any value here, but
    // on amd64 without a os level function to determine readability, then
    // use 0x0 (NULL)
    memset(self, 0x0, sizeof(*self));
}


void M3_Object1_new(M3_Object1 *const self)
{
    // only way to assign vtbl is via init list..
    // unless I hack it with offsetof..
    M3_Interface1_new(&self->iface1, &M3_Object1_Interface1_vtbl);
    //M3_Value_new(&self->value);
    self->value1 = 0;
    self->value2 = 1;
    self->value3 = 2;
}


void M3_Object1_foo(M3_Object1 *const self)
{
    ((void)self);
}


void M3_Object1_foo2(M3_Object1 *const self,
                     M3_Result *const ret)
{
    ((void)self);
    M3_Result_err(ret, M3_Err_NotImplemented);
}


void M3_Object1_foo3(M3_Result *const ret,
                     M3_Object1 *const self
                    )
{
    ((void)self);
    M3_Result_err(ret, M3_Err_NotImplemented);
}


void M3_Object1_get_value1(M3_Result *const ret,
                           M3_Object1 const *const self,
                           M3_Value *const val
                          )
{
    *val = self->value1;
    M3_Result_ok(ret, 0);
}


void M3_Object1_set_value1(M3_Result *const ret,
                           M3_Object1 *const self,
                           M3_Value const *const arg
                          )
{
    self->value1 = *arg;
    M3_Result_ok(ret, 0);
}

void M3_Object1_get_value2(M3_Result *const ret,
                           M3_Object1 const *const self,
                           M3_Value *const val
                          )
{
    *val = self->value2;
    M3_Result_ok(ret, 0);
}


void M3_Object1_set_value2(M3_Result *const ret,
                           M3_Object1 *const self,
                           M3_Value const *const arg
                          )
{
    self->value2 = *arg;
    M3_Result_ok(ret, 0);
}

void M3_Object1_get_value3(M3_Result *const ret,
                           M3_Object1 const *const self,
                           M3_Value *const val
                          )
{
    *val = self->value3;
    M3_Result_ok(ret, 0);
}


void M3_Object1_set_value3(M3_Result *const ret,
                           M3_Object1 *const self,
                           M3_Value const *const arg
                          )
{
    self->value3 = *arg;
    M3_Result_ok(ret, 0);
}

void M3_Object1_action1(M3_Result *const ret,
                        M3_Object1 *const self,
                        M3_Value const *const arg,
                        M3_Value *const out
                       )
{
    *out = self->value1 + *arg + 23;
    M3_Result_ok(ret, 0);
}

void M3_Object1_action2(M3_Result *const ret,
                        M3_Object1 *const self,
                        M3_Value const *const arg,
                        M3_Value *const out
                       )
{
    ((void)self);
    ((void)arg);
    ((void)out);
    M3_Result_err(ret, M3_Err_NotImplemented);
}
