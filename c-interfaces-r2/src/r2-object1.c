#include "r2-object1.h"

#include "r2-carray.h"
#include "r2-interface.h"
#include "r2-result.h"

#include <inttypes.h>
#include <memory.h>
#include <stddef.h>


static R2_InterfaceLookup const R2_Object1_ifaces[] = {
    {&R2_Interface1_ID, offsetof(R2_Object1, iface1)},
};
// TODO maybe wrap this in DEFINE_INTERFACEMAP(cls)/INTERFACE()/END_INTERFACEMAP macros

R2_Result R2_Object1_query_interface(R2_Object1 const *const self,
                                     R2_InterfaceID const *const iid, void const **const val)
{
    // no guard needed here as not relying on values in the object struct instance.
    // although a guard could be added to verify it's an instance of the expected type.
    return R2_Interface_query_interface(self, iid, val,
                                        R2_CARRAY_BEGIN(R2_Object1_ifaces), R2_CARRAY_END(R2_Object1_ifaces));
}

R2_Result R2_Object1_query_interface_mut(R2_Object1 *const self,
        R2_InterfaceID const *const iid, void **const val)
{
    // no guard needed here as not relying on values in the object struct instance.
    // although a guard could be added to verify it's an instance of the expected type.
    return R2_Interface_query_interface_mut(self, iid, val,
                                            R2_CARRAY_BEGIN(R2_Object1_ifaces), R2_CARRAY_END(R2_Object1_ifaces));
}

///////////////////////////////////////////////////////////////////////////////

static R2_Object1 const *R2_Object1_Interface1_getobjptr(
    R2_Interface1 const *const self)
{
    R2_Object1 const *const oself = R2_INTERFACE_GET_OBJPTR(R2_Object1, self);
    return oself;
}

static R2_Object1 *R2_Object1_Interface1_getobjptr_mut(R2_Interface1 *const
        self)
{
    R2_Object1 *const oself = R2_INTERFACE_GET_OBJPTR_MUT(R2_Object1, self);
    return oself;
}

R2_Result R2_Object1_Interface1_query_interface(R2_Interface1 const *const self,
        R2_InterfaceID const *const iid, void const **const val)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface1_check_guard(self);
    R2_RESULT_TRY0(r);
#endif
    return R2_Object1_query_interface(R2_Object1_Interface1_getobjptr(self), iid,
                                      val);
}

R2_Result R2_Object1_Interface1_query_interface_mut(R2_Interface1 *const self,
        R2_InterfaceID const *const iid, void **const val)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface1_check_guard(self);
    R2_RESULT_TRY0(r);
#endif
    return R2_Object1_query_interface_mut(R2_Object1_Interface1_getobjptr_mut(self),
                                          iid, val);
}

R2_Result R2_Object1_Interface1_get_value(R2_Interface1 const *const self,
        R2_Value *const val)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface1_check_guard(self);
    R2_RESULT_TRY0(r);
#endif
    return R2_Object1_get_value(R2_Object1_Interface1_getobjptr(self), val);
}

R2_Result R2_Object1_Interface1_set_value(R2_Interface1 *const self,
        R2_Value const *const arg)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface1_check_guard(self);
    R2_RESULT_TRY0(r);
#endif
    return R2_Object1_set_value(R2_Object1_Interface1_getobjptr_mut(self), arg);
}

static R2_Interface1Vtbl const R2_Object1_Interface1_vtbl = {
    &R2_Interface1_ID,
    offsetof(R2_Object1, iface1),
    R2_Object1_Interface1_query_interface,
    R2_Object1_Interface1_query_interface_mut,
    R2_Interface1_get,
    R2_Interface1_set,
    R2_Interface1_action,
    R2_Object1_Interface1_get_value,
    R2_Object1_Interface1_set_value
};

///////////////////////////////////////////////////////////////////////////////

void R2_Object1_destroy(R2_Object1 *const self)
{
    // completely corrupt object, including interface vtlb pointers (oops).
    // should be able to use any value here, but
    // on amd64 without a os level function to determine readability, then
    // use 0x0 (NULL)
    memset(self, 0x0, sizeof(*self));
}

R2_Object1 R2_Object1_new(void)
{
    // prob will be initialising value.
    // and vtbls need to be initialised via init list as thats the only way to
    // init const * const members.
    R2_Object1 inst = {
        .value = 0,
        .iface1 = R2_Interface1_new(&R2_Object1_Interface1_vtbl),
    };
    // need to stop vtbls in interfaces being mutable in a mutable R2_Object1 inst.
    // they shouldn't be.
    return inst;
}


R2_Result R2_Object1_get_value(R2_Object1 const *const self,
                               R2_Value *const val)
{
    *val = self->value;
    return R2_Result_ok(0);
}

R2_Result R2_Object1_set_value(R2_Object1 *const self,
                               R2_Value const *const arg)
{
    self->value = *arg;
    return R2_Result_ok(0);
}
