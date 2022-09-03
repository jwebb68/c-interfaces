#include "m4-object1.h"

#include "m4-carray.h"
#include "m4-interface.h"
#include "m4-result.h"

#include <inttypes.h>
#include <memory.h>
#include <stddef.h>

static M4_InterfaceLookup const M4_Object1_ifaces[] = {
    {&M4_Interface1_ID, offsetof(M4_Object1, iface1)},
    {&M4_Interface3_ID, offsetof(M4_Object1, iface3)},
};
// TODO maybe wrap this in DEFINE_INTERFACEMAP(cls)/INTERFACE()/END_INTERFACEMAP macros


void M4_Object1_query_interface(
    M4_Object1 const *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **const val
)
{
    // no guard needed here as not relying on values in the object struct instance.
    // although a guard could be added to verify it's an instance of the expected type.
    M4_Interface_query_interface(self, ret, iid, val,
                                 M4_CARRAY_BEGIN(M4_Object1_ifaces),
                                 M4_CARRAY_END(M4_Object1_ifaces)
                                );
}


void M4_Object1_query_interface_mut(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **const val
)
{
    // no guard needed here as not relying on values in the object struct instance.
    // although a guard could be added to verify it's an instance of the expected type.
    M4_Interface_query_interface_mut(self, ret, iid, val,
                                     M4_CARRAY_BEGIN(M4_Object1_ifaces),
                                     M4_CARRAY_END(M4_Object1_ifaces)
                                    );
}


///////////////////////////////////////////////////////////////////////////////

static M4_Object1 const *M4_Object1_Interface1_getobjptr(
    M4_Interface1 const *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M4_Object1 const *const oself = M4_INTERFACE_GET_OBJPTR(M4_Object1, self);
    return oself;
}


static M4_Object1 *M4_Object1_Interface1_getobjptr_mut(
    M4_Interface1 *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M4_Object1 *const oself = M4_INTERFACE_GET_OBJPTR_MUT(M4_Object1, self);
    return oself;
}

static void M4_Object1_Interface1_query_interface(
    M4_Interface1 const *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **const val
)
{
    M4_Object1_query_interface(M4_Object1_Interface1_getobjptr(self),
                               ret,
                               iid,
                               val);
}

static void M4_Object1_Interface1_query_interface_mut(
    M4_Interface1 *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **const val
)
{
    M4_Object1_query_interface_mut(M4_Object1_Interface1_getobjptr_mut(self),
                                   ret,
                                   iid,
                                   val);
}


// ===========================================================================

static void M4_Object1_Interface1_foo(M4_Interface1 *const self)
{
    M4_Object1_foo(M4_Object1_Interface1_getobjptr_mut(self));
}

static void M4_Object1_Interface1_foo2(M4_Interface1 *const self,
                                       M4_Result *const ret)
{
    M4_Object1_foo2(M4_Object1_Interface1_getobjptr_mut(self), ret);
}

static void M4_Object1_Interface1_foo3(M4_Result *const ret,
                                       M4_Interface1 *const self)
{
    M4_Object1_foo3(ret, M4_Object1_Interface1_getobjptr_mut(self));
}


static M4_Interface1Vtbl const M4_Object1_Interface1_vtbl = {
    &M4_Object1_Interface1_vtbl,
    offsetof(M4_Object1, iface1),
    M4_Object1_Interface1_query_interface,
    M4_Object1_Interface1_query_interface_mut,
    M4_Object1_Interface1_foo,
    M4_Object1_Interface1_foo2,
    M4_Object1_Interface1_foo3,
};



// ===========================================================================

static M4_Object1 const *M4_Object1_Interface3_getobjptr(
    M4_Interface3 const *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M4_Object1 const *const oself = M4_INTERFACE_GET_OBJPTR(M4_Object1, self);
    return oself;
}


static M4_Object1 *M4_Object1_Interface3_getobjptr_mut(
    M4_Interface3 *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M4_Object1 *const oself = M4_INTERFACE_GET_OBJPTR_MUT(M4_Object1, self);
    return oself;
}

static void M4_Object1_Interface3_query_interface(
    M4_Interface3 const *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **const val
)
{
    M4_Object1_query_interface(M4_Object1_Interface3_getobjptr(self),
                               ret,
                               iid,
                               val);
}

static void M4_Object1_Interface3_query_interface_mut(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **const val
)
{
    M4_Object1_query_interface_mut(
        M4_Object1_Interface3_getobjptr_mut(self),
        ret,
        iid,
        val);
}

static void M4_Object1_Interface3_get_value1(
    M4_Interface3 const *const self,
    M4_Result *const ret,
    M4_Value *const val)
{
    M4_Object1_get_value1(M4_Object1_Interface3_getobjptr(self), ret, val);
}


static void M4_Object1_Interface3_set_value1(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    M4_Object1_set_value1(M4_Object1_Interface3_getobjptr_mut(self), ret, arg);
}

static void M4_Object1_Interface3_get_value2(
    M4_Interface3 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    M4_Object1_get_value2(M4_Object1_Interface3_getobjptr(self), ret, val);
}


static void M4_Object1_Interface3_set_value2(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    M4_Object1_set_value2(M4_Object1_Interface3_getobjptr_mut(self), ret, arg);
}


static void M4_Object1_Interface3_get_value3(
    M4_Interface3 const *const self,
    M4_Result *const ret,
    M4_Value *const val)
{
    M4_Object1_get_value3(M4_Object1_Interface3_getobjptr(self), ret, val);
}


static void M4_Object1_Interface3_set_value3(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    M4_Object1_set_value3(M4_Object1_Interface3_getobjptr_mut(self), ret, arg);
}

static void M4_Object1_Interface3_action1(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_Value const *const arg,
    M4_Value *const out
)
{
    M4_Object1_action1(M4_Object1_Interface3_getobjptr_mut(self), ret, arg, out);
}


static void M4_Object1_Interface3_action2(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_Value const *const arg,
    M4_Value *const out
)
{
    M4_Object1_action2(M4_Object1_Interface3_getobjptr_mut(self), ret, arg, out);
}


static M4_Interface3Vtbl const M4_Object1_Interface3_vtbl = {
    &M4_Object1_Interface3_vtbl,
    offsetof(M4_Object1, iface3),
    M4_Object1_Interface3_query_interface,
    M4_Object1_Interface3_query_interface_mut,
    M4_Interface3_get,
    M4_Interface3_set,
    M4_Interface3_action,
    M4_Object1_Interface3_get_value1,
    M4_Object1_Interface3_set_value1,
    M4_Object1_Interface3_get_value2,
    M4_Object1_Interface3_set_value2,
    M4_Object1_Interface3_get_value3,
    M4_Object1_Interface3_set_value3,
    M4_Object1_Interface3_action1,
    M4_Object1_Interface3_action2,
};






///////////////////////////////////////////////////////////////////////////////

void M4_Object1_destroy(M4_Object1 *const self)
{
    // completely corrupt object, including interface vtlb pointers (oops).
    // should be able to use any value here, but
    // on amd64 without a os level function to determine readability, then
    // use 0x0 (NULL)
    memset(self, 0x0, sizeof(*self));
}


void M4_Object1_new(M4_Object1 *const self)
{
    // only way to assign vtbl is via init list..
    // unless I hack it with offsetof..
    M4_Interface1_new(&self->iface1, &M4_Object1_Interface1_vtbl);
    //M4_Value_new(&self->value);
    self->value1 = 0;
    self->value2 = 1;
    self->value3 = 2;
}


void M4_Object1_foo(M4_Object1 *const self)
{
    ((void)self);
}


void M4_Object1_foo2(M4_Object1 *const self,
                     M4_Result *const ret)
{
    ((void)self);
    M4_Result_err(ret, M4_Err_NotImplemented);
}


void M4_Object1_foo3(M4_Result *const ret,
                     M4_Object1 *const self
                    )
{
    ((void)self);
    M4_Result_err(ret, M4_Err_NotImplemented);
}


void M4_Object1_get_value1(
    M4_Object1 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    *val = self->value1;
    M4_Result_ok(ret, 0);
}


void M4_Object1_set_value1(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    self->value1 = *arg;
    M4_Result_ok(ret, 0);
}

void M4_Object1_get_value2(
    M4_Object1 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    *val = self->value2;
    M4_Result_ok(ret, 0);
}


void M4_Object1_set_value2(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    self->value2 = *arg;
    M4_Result_ok(ret, 0);
}

void M4_Object1_get_value3(
    M4_Object1 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    *val = self->value3;
    M4_Result_ok(ret, 0);
}


void M4_Object1_set_value3(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    self->value3 = *arg;
    M4_Result_ok(ret, 0);
}

void M4_Object1_action1(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_Value const *const arg,
    M4_Value *const out
)
{
    *out = self->value1 + *arg + 23;
    M4_Result_ok(ret, 0);
}

void M4_Object1_action2(
    M4_Object1 *const self,
    M4_Result *const ret,
    M4_Value const *const arg,
    M4_Value *const out
)
{
    ((void)self);
    ((void)arg);
    ((void)out);
    M4_Result_err(ret, M4_Err_NotImplemented);
}
