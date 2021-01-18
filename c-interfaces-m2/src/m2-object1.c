#include "m2-object1.h"

#include "m2-carray.h"
#include "m2-interface.h"
#include "m2-result.h"

#include <inttypes.h>
#include <memory.h>
#include <stddef.h>


static M2_InterfaceLookup const M2_Object1_ifaces[] = {
    {&M2_Interface1_ID, offsetof(M2_Object1, iface1)},
};
// TODO maybe wrap this in DEFINE_INTERFACEMAP(cls)/INTERFACE()/END_INTERFACEMAP macros


void M2_Object1_query_interface(M2_Object1 const *const self,
                                M2_InterfaceID const *const iid,
                                void const **const val,
                                M2_Result *const ret
                               )
{
    // no guard needed here as not relying on values in the object struct instance.
    // although a guard could be added to verify it's an instance of the expected type.
    M2_Interface_query_interface(self, iid, val, ret,
                                 M2_CARRAY_BEGIN(M2_Object1_ifaces),
                                 M2_CARRAY_END(M2_Object1_ifaces)
                                );
}


void M2_Object1_query_interface_mut(M2_Object1 *const self,
                                    M2_InterfaceID const *const iid,
                                    void **const val,
                                    M2_Result *const ret
                                   )
{
    // no guard needed here as not relying on values in the object struct instance.
    // although a guard could be added to verify it's an instance of the expected type.
    M2_Interface_query_interface_mut(self, iid, val, ret,
                                     M2_CARRAY_BEGIN(M2_Object1_ifaces),
                                     M2_CARRAY_END(M2_Object1_ifaces)
                                    );
}


///////////////////////////////////////////////////////////////////////////////

static M2_Object1 const *M2_Object1_Interface1_getobjptr(
    M2_Interface1 const *const self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M2_Object1 const *const oself = M2_INTERFACE_GET_OBJPTR(M2_Object1, self);
    return oself;
}


static M2_Object1 *M2_Object1_Interface1_getobjptr_mut(M2_Interface1 *const
        self)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
    // TODO: check self vtbl is expected one before accessing for the adjustment for self
    M2_Object1 *const oself = M2_INTERFACE_GET_OBJPTR_MUT(M2_Object1, self);
    return oself;
}

static void M2_Object1_Interface1_query_interface(M2_Interface1 const *const
        self,
        M2_InterfaceID const *const iid,
        void const **const val,
        M2_Result *const ret
                                                 )
{
    M2_Object1_query_interface(M2_Object1_Interface1_getobjptr(self),
                               iid,
                               val,
                               ret);
}

static void M2_Object1_Interface1_query_interface_mut(M2_Interface1 *const self,
        M2_InterfaceID const *const iid,
        void **const val,
        M2_Result *const ret
                                                     )
{
    M2_Object1_query_interface_mut(M2_Object1_Interface1_getobjptr_mut(self),
                                   iid,
                                   val,
                                   ret);
}


// ===========================================================================

static void M2_Object1_Interface1_foo(M2_Interface1 *const self)
{
    M2_Object1_foo(M2_Object1_Interface1_getobjptr_mut(self));
}

static void M2_Object1_Interface1_foo2(M2_Interface1 *const self,
                                       M2_Result *const ret
                                      )
{
    M2_Object1_foo2(M2_Object1_Interface1_getobjptr_mut(self), ret);
}


// ===========================================================================
static void M2_Object1_Interface1_get_value(M2_Interface1 const *const self,
        M2_Value *const val,
        M2_Result *const ret
                                           )
{
    M2_Object1_get_value(M2_Object1_Interface1_getobjptr(self), val, ret);
}


static void M2_Object1_Interface1_set_value(M2_Interface1 *const self,
        M2_Value const *const arg,
        M2_Result *const ret
                                           )
{
    M2_Object1_set_value(M2_Object1_Interface1_getobjptr_mut(self), arg, ret);
}


static M2_Interface1Vtbl const M2_Object1_Interface1_vtbl = {
    &M2_Object1_Interface1_vtbl,
    offsetof(M2_Object1, iface1),
    M2_Object1_Interface1_query_interface,
    M2_Object1_Interface1_query_interface_mut,
    M2_Object1_Interface1_foo,
    M2_Object1_Interface1_foo2,
    M2_Interface1_get,
    M2_Interface1_set,
    M2_Interface1_action,
    M2_Object1_Interface1_get_value,
    M2_Object1_Interface1_set_value
};


///////////////////////////////////////////////////////////////////////////////

void M2_Object1_destroy(M2_Object1 *const self)
{
    // completely corrupt object, including interface vtlb pointers (oops).
    // should be able to use any value here, but
    // on amd64 without a os level function to determine readability, then
    // use 0x0 (NULL)
    memset(self, 0x0, sizeof(*self));
}


void M2_Object1_new(M2_Object1 *const self)
{
    // only way to assign vtbl is via init list..
    // unless I hack it with offsetof..
    M2_Interface1_new(&self->iface1, &M2_Object1_Interface1_vtbl);
    //M2_Value_new(&self->value);
    self->value = 0;
}


void M2_Object1_foo(M2_Object1 *const self)
{
    ((void)self);
}


void M2_Object1_foo2(M2_Object1 *const self,
                     M2_Result *const ret)
{
    ((void)self);
    M2_Result_err(ret, M2_Err_NotImplemented);
}


void M2_Object1_get_value(M2_Object1 const *const self,
                          M2_Value *const val,
                          M2_Result *const ret
                         )
{
    *val = self->value;
    M2_Result_ok(ret, 0);
}


void M2_Object1_set_value(M2_Object1 *const self,
                          M2_Value const *const arg,
                          M2_Result *const ret
                         )
{
    self->value = *arg;
    M2_Result_ok(ret, 0);
}
