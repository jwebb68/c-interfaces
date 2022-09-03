#include "m4-object2.h"

#include "m4-carray.h"
#include "m4-interface.h"

#include <inttypes.h>
#include <stddef.h>
#include <memory.h>


//////////////////////////////////////////////////////////////////////////////
static M4_InterfaceLookup const M4_Object2_ifaces[] = {
    {&M4_Interface1_ID, offsetof(M4_Object2, iface1)},
    {&M4_Interface2_ID, offsetof(M4_Object2, iface2)},
};


void M4_Object2_query_interface(
    M4_Object2 const *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **const val
)
{
    // no guard needed here as not relying on values in the object struct instance.
    M4_Interface_query_interface(self, ret, iid, val,
                                 M4_CARRAY_BEGIN(M4_Object2_ifaces),
                                 M4_CARRAY_END(M4_Object2_ifaces)
                                );
}


void M4_Object2_query_interface_mut(
    M4_Object2 *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **const val
)
{
    // no guard needed here as not relying on values in the object struct instance.
    M4_Interface_query_interface_mut(self, ret, iid, val,
                                     M4_CARRAY_BEGIN(M4_Object2_ifaces),
                                     M4_CARRAY_END(M4_Object2_ifaces)
                                    );
}


//////////////////////////////////////////////////////////////////////////////

static M4_Object2 const *M4_Object2_Interface1_getobjptr(
    M4_Interface1 const *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M4_Object2 const *const oself = M4_INTERFACE_GET_OBJPTR(M4_Object2, self);
    return oself;
}


static M4_Object2 *M4_Object2_Interface1_getobjptr_mut(M4_Interface1 *const
        self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M4_Object2 *const oself = M4_INTERFACE_GET_OBJPTR_MUT(M4_Object2, self);
    return oself;
}


static void M4_Object2_Interface1_query_interface(
    M4_Interface1 const *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **const val
)
{
    M4_Object2_query_interface(
        M4_Object2_Interface1_getobjptr(self),
        ret,
        iid,
        val);
}


static void M4_Object2_Interface1_query_interface_mut(
    M4_Interface1 *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **const val
)
{
    M4_Object2_query_interface_mut(
        M4_Object2_Interface1_getobjptr_mut(self),
        ret,
        iid,
        val);
}


static void M4_Object2_Interface1_foo(M4_Interface1 *const self)
{
    M4_Object2_foo(M4_Object2_Interface1_getobjptr_mut(self));
}


static void M4_Object2_Interface1_foo2(M4_Interface1 *const self,
                                       M4_Result *const ret)
{
    M4_Object2_foo2(M4_Object2_Interface1_getobjptr_mut(self), ret);
}

static void M4_Object2_Interface1_foo3(M4_Result *const ret,
                                       M4_Interface1 *const self
                                      )
{
    M4_Object2_foo3(ret, M4_Object2_Interface1_getobjptr_mut(self));
}


static M4_Interface1Vtbl const M4_Object2_Interface1_vtbl = {
    &M4_Object2_Interface1_vtbl,
    offsetof(M4_Object2, iface1),
    M4_Object2_Interface1_query_interface,
    M4_Object2_Interface1_query_interface_mut,
    M4_Object2_Interface1_foo,
    M4_Object2_Interface1_foo2,
    M4_Object2_Interface1_foo3,
};


/////////////////////////////////////////////////////////////////////////////

static M4_Object2 const *M4_Object2_Interface2_getobjptr(
    M4_Interface2 const *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M4_Object2 const *const oself = M4_INTERFACE_GET_OBJPTR(M4_Object2, self);
    return oself;
}


static M4_Object2 *M4_Object2_Interface2_getobjptr_mut(M4_Interface2 *const
        self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M4_Object2 *const oself = M4_INTERFACE_GET_OBJPTR_MUT(M4_Object2, self);
    return oself;
}


static void M4_Object2_Interface2_query_interface(
    M4_Interface2 const *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **const val
)
{
    M4_Object2_query_interface(
        M4_Object2_Interface2_getobjptr(self),
        ret,
        iid,
        val);
}


static void M4_Object2_Interface2_query_interface_mut(
    M4_Interface2 *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **const val
)
{
    M4_Object2_query_interface_mut(
        M4_Object2_Interface2_getobjptr_mut(self),
        ret,
        iid,
        val);
}


static void M4_Object2_Interface2_get_value(
    M4_Interface2 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    M4_Object2_get_value(M4_Object2_Interface2_getobjptr(self), ret, val);
}


static void M4_Object2_Interface2_set_value(
    M4_Interface2 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    M4_Object2_set_value(M4_Object2_Interface2_getobjptr_mut(self), ret, arg);
}


static void M4_Object2_Interface2_get_objects(
    M4_Interface2 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    M4_Object2_get_objects(M4_Object2_Interface2_getobjptr(self), ret, val);
}


static void M4_Object2_Interface2_set_objects(
    M4_Interface2 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    M4_Object2_set_objects(M4_Object2_Interface2_getobjptr_mut(self), ret, arg);
}


static M4_Interface2Vtbl const M4_Object2_Interface2_vtbl = {
    &M4_Object2_Interface2_vtbl,
    offsetof(M4_Object2, iface2),
    M4_Object2_Interface2_query_interface,
    M4_Object2_Interface2_query_interface_mut,
    M4_Object2_Interface2_get_value,
    M4_Object2_Interface2_set_value,
    M4_Object2_Interface2_get_objects,
    M4_Object2_Interface2_set_objects

};


///////////////////////////////////////////////////////////////////////////////

static void M4_Object2_invalidate(M4_Object2 *const self)
{
    // completely corrupt object, including interface vtlb pointers (oops).
    // should be able to use any value here, but
    // on amd64 without a os level function to determine readability, then
    // use 0x0 (NULL)
    memset(self, 0x0, sizeof(*self));
}


void M4_Object2_destroy(M4_Object2 *const self)
{
    M4_Object2_invalidate(self);
}


void M4_Object2_new(M4_Object2 *self)
{
    M4_Interface1_new(&self->iface1, &M4_Object2_Interface1_vtbl);
    M4_Interface2_new(&self->iface2, &M4_Object2_Interface2_vtbl);
    self->value = 0;
}


void M4_Object2_foo(M4_Object2 *const self)
{
    ((void)self);
}


void M4_Object2_foo2(M4_Object2 *const self,
                     M4_Result *const ret)
{
    ((void)self);
    M4_Result_err(ret, M4_Err_NotImplemented);
}

void M4_Object2_foo3(M4_Result *const ret,
                     M4_Object2 *const self
                    )
{
    ((void)self);
    M4_Result_err(ret, M4_Err_NotImplemented);
}


void M4_Object2_get_value(
    M4_Object2 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    *val = self->value;
    M4_Result_ok(ret, 0);
}


void M4_Object2_set_value(
    M4_Object2 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    self->value = *arg;
    M4_Result_ok(ret, 0);
}


void M4_Object2_get_objects(
    M4_Object2 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    ((void)self);
    ((void)val);
    M4_Result_err(ret, M4_Err_NotImplemented);
}


void M4_Object2_set_objects(
    M4_Object2 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    ((void)self);
    ((void)arg);
    M4_Result_err(ret, M4_Err_NotImplemented);
}
