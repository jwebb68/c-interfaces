#include "m3-object2.h"

#include "m3-carray.h"
#include "m3-interface.h"

#include <inttypes.h>
#include <stddef.h>
#include <memory.h>


//////////////////////////////////////////////////////////////////////////////
static M3_InterfaceLookup const M3_Object2_ifaces[] = {
    {&M3_Interface1_ID, offsetof(M3_Object2, iface1)},
    {&M3_Interface2_ID, offsetof(M3_Object2, iface2)},
};


void M3_Object2_query_interface(M3_Result *const ret,
                                M3_Object2 const *const self,
                                M3_InterfaceID const *const iid,
                                void const **const val
                               )
{
    // no guard needed here as not relying on values in the object struct instance.
    M3_Interface_query_interface(ret, self, iid, val,
                                 M3_CARRAY_BEGIN(M3_Object2_ifaces),
                                 M3_CARRAY_END(M3_Object2_ifaces)
                                );
}


void M3_Object2_query_interface_mut(M3_Result *const ret,
                                    M3_Object2 *const self,
                                    M3_InterfaceID const *const iid,
                                    void **const val
                                   )
{
    // no guard needed here as not relying on values in the object struct instance.
    M3_Interface_query_interface_mut(ret, self, iid, val,
                                     M3_CARRAY_BEGIN(M3_Object2_ifaces),
                                     M3_CARRAY_END(M3_Object2_ifaces)
                                    );
}


//////////////////////////////////////////////////////////////////////////////

static M3_Object2 const *M3_Object2_Interface1_getobjptr(
    M3_Interface1 const *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M3_Object2 const *const oself = M3_INTERFACE_GET_OBJPTR(M3_Object2, self);
    return oself;
}


static M3_Object2 *M3_Object2_Interface1_getobjptr_mut(M3_Interface1 *const
        self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M3_Object2 *const oself = M3_INTERFACE_GET_OBJPTR_MUT(M3_Object2, self);
    return oself;
}


static void M3_Object2_Interface1_query_interface(
    M3_Result *const ret,
    M3_Interface1 const *const self,
    M3_InterfaceID const *const iid,
    void const **const val
)
{
    M3_Object2_query_interface(ret,
                               M3_Object2_Interface1_getobjptr(self),
                               iid,
                               val);
}


static void M3_Object2_Interface1_query_interface_mut(
    M3_Result *const ret,
    M3_Interface1 *const self,
    M3_InterfaceID const *const iid,
    void **const val
)
{
    M3_Object2_query_interface_mut(ret,
                                   M3_Object2_Interface1_getobjptr_mut(self),
                                   iid,
                                   val);
}


static void M3_Object2_Interface1_foo(M3_Interface1 *const self)
{
    M3_Object2_foo(M3_Object2_Interface1_getobjptr_mut(self));
}


static void M3_Object2_Interface1_foo2(M3_Interface1 *const self,
                                       M3_Result *const ret)
{
    M3_Object2_foo2(M3_Object2_Interface1_getobjptr_mut(self), ret);
}

static void M3_Object2_Interface1_foo3(M3_Result *const ret,
                                       M3_Interface1 *const self
                                      )
{
    M3_Object2_foo3(ret, M3_Object2_Interface1_getobjptr_mut(self));
}


static M3_Interface1Vtbl const M3_Object2_Interface1_vtbl = {
    &M3_Object2_Interface1_vtbl,
    offsetof(M3_Object2, iface1),
    M3_Object2_Interface1_query_interface,
    M3_Object2_Interface1_query_interface_mut,
    M3_Object2_Interface1_foo,
    M3_Object2_Interface1_foo2,
    M3_Object2_Interface1_foo3,
};


/////////////////////////////////////////////////////////////////////////////

static M3_Object2 const *M3_Object2_Interface2_getobjptr(
    M3_Interface2 const *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M3_Object2 const *const oself = M3_INTERFACE_GET_OBJPTR(M3_Object2, self);
    return oself;
}


static M3_Object2 *M3_Object2_Interface2_getobjptr_mut(M3_Interface2 *const
        self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M3_Object2 *const oself = M3_INTERFACE_GET_OBJPTR_MUT(M3_Object2, self);
    return oself;
}


static void M3_Object2_Interface2_query_interface(
    M3_Result *const ret,
    M3_Interface2 const *const self,
    M3_InterfaceID const *const iid,
    void const **const val
)
{
    M3_Object2_query_interface(ret,
                               M3_Object2_Interface2_getobjptr(self),
                               iid,
                               val);
}


static void M3_Object2_Interface2_query_interface_mut(
    M3_Result *const ret,
    M3_Interface2 *const self,
    M3_InterfaceID const *const iid,
    void **const val
)
{
    M3_Object2_query_interface_mut(ret,
                                   M3_Object2_Interface2_getobjptr_mut(self),
                                   iid,
                                   val);
}


static void M3_Object2_Interface2_get_value(
    M3_Result *const ret,
    M3_Interface2 const *const self,
    M3_Value *const val
)
{
    M3_Object2_get_value(ret, M3_Object2_Interface2_getobjptr(self), val);
}


static void M3_Object2_Interface2_set_value(
    M3_Result *const ret,
    M3_Interface2 *const self,
    M3_Value const *const arg
)
{
    M3_Object2_set_value(ret, M3_Object2_Interface2_getobjptr_mut(self), arg);
}


static void M3_Object2_Interface2_get_objects(
    M3_Result *const ret,
    M3_Interface2 const *const self,
    M3_Value *const val
)
{
    M3_Object2_get_objects(ret, M3_Object2_Interface2_getobjptr(self), val);
}


static void M3_Object2_Interface2_set_objects(
    M3_Result *const ret,
    M3_Interface2 *const self,
    M3_Value const *const arg
)
{
    M3_Object2_set_objects(ret, M3_Object2_Interface2_getobjptr_mut(self), arg);
}


static M3_Interface2Vtbl const M3_Object2_Interface2_vtbl = {
    &M3_Object2_Interface2_vtbl,
    offsetof(M3_Object2, iface2),
    M3_Object2_Interface2_query_interface,
    M3_Object2_Interface2_query_interface_mut,
    M3_Object2_Interface2_get_value,
    M3_Object2_Interface2_set_value,
    M3_Object2_Interface2_get_objects,
    M3_Object2_Interface2_set_objects

};


///////////////////////////////////////////////////////////////////////////////

static void M3_Object2_invalidate(M3_Object2 *const self)
{
    // completely corrupt object, including interface vtlb pointers (oops).
    // should be able to use any value here, but
    // on amd64 without a os level function to determine readability, then
    // use 0x0 (NULL)
    memset(self, 0x0, sizeof(*self));
}


void M3_Object2_destroy(M3_Object2 *const self)
{
    M3_Object2_invalidate(self);
}


void M3_Object2_new(M3_Object2 *self)
{
    M3_Interface1_new(&self->iface1, &M3_Object2_Interface1_vtbl);
    M3_Interface2_new(&self->iface2, &M3_Object2_Interface2_vtbl);
    self->value = 0;
}


void M3_Object2_foo(M3_Object2 *const self)
{
    ((void)self);
}


void M3_Object2_foo2(M3_Object2 *const self,
                     M3_Result *const ret)
{
    ((void)self);
    M3_Result_err(ret, M3_Err_NotImplemented);
}

void M3_Object2_foo3(M3_Result *const ret,
                     M3_Object2 *const self
                    )
{
    ((void)self);
    M3_Result_err(ret, M3_Err_NotImplemented);
}


void M3_Object2_get_value(
    M3_Result *const ret,
    M3_Object2 const *const self,
    M3_Value *const val
)
{
    *val = self->value;
    M3_Result_ok(ret, 0);
}


void M3_Object2_set_value(
    M3_Result *const ret,
    M3_Object2 *const self,
    M3_Value const *const arg
)
{
    self->value = *arg;
    M3_Result_ok(ret, 0);
}


void M3_Object2_get_objects(
    M3_Result *const ret,
    M3_Object2 const *const self,
    M3_Value *const val
)
{
    ((void)self);
    ((void)val);
    M3_Result_err(ret, M3_Err_NotImplemented);
}


void M3_Object2_set_objects(
    M3_Result *const ret,
    M3_Object2 *const self,
    M3_Value const *const arg
)
{
    ((void)self);
    ((void)arg);
    M3_Result_err(ret, M3_Err_NotImplemented);
}
