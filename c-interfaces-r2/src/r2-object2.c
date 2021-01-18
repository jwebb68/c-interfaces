#include "r2-object2.h"

#include "r2-carray.h"
#include "r2-interface.h"

#include <inttypes.h>
#include <stddef.h>
#include <memory.h>

//////////////////////////////////////////////////////////////////////////////

static R2_InterfaceLookup const R2_Object2_ifaces[] = {
    {&R2_Interface1_ID, offsetof(R2_Object2, iface1)},
    {&R2_Interface2_ID, offsetof(R2_Object2, iface2)},
};

R2_Result R2_Object2_query_interface(R2_Object2 const *const self,
                                     R2_InterfaceID const *const iid, void const **const ret)
{
    // no guard needed here as not relying on values in the object struct instance.
    return R2_Interface_query_interface(self, iid, ret,
                                        R2_CARRAY_BEGIN(R2_Object2_ifaces), R2_CARRAY_END(R2_Object2_ifaces));
}

R2_Result R2_Object2_query_interface_mut(R2_Object2 *const self,
        R2_InterfaceID const *const iid, void **const ret)
{
    // no guard needed here as not relying on values in the object struct instance.
    return R2_Interface_query_interface_mut(self, iid, ret,
                                            R2_CARRAY_BEGIN(R2_Object2_ifaces), R2_CARRAY_END(R2_Object2_ifaces));
}

//////////////////////////////////////////////////////////////////////////////

static R2_Object2 const *R2_Object2_Interface1_getobjptr(
    R2_Interface1 const *const self)
{
    R2_Object2 const *const oself = R2_INTERFACE_GET_OBJPTR(R2_Object2, self);
    return oself;
}

static R2_Object2 *R2_Object2_Interface1_getobjptr_mut(R2_Interface1 *const
        self)
{
    R2_Object2 *const oself = R2_INTERFACE_GET_OBJPTR_MUT(R2_Object2, self);
    return oself;
}


R2_Result R2_Object2_Interface1_query_interface(R2_Interface1 const *const self,
        R2_InterfaceID const *const iid, void const **const ret)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface1_check_guard(self);
    R2_RESULT_TRY0(r);
#endif//
    return R2_Object2_query_interface(R2_Object2_Interface1_getobjptr(self), iid,
                                      ret);
}

R2_Result R2_Object2_Interface1_query_interface_mut(R2_Interface1 *const self,
        R2_InterfaceID const *const iid, void **const ret)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface1_check_guard(self);
    R2_RESULT_TRY0(r);
#endif//
    return R2_Object2_query_interface_mut(R2_Object2_Interface1_getobjptr_mut(self),
                                          iid, ret);
}

//========================================================================

R2_Result R2_Object2_Interface1_get_value(R2_Interface1 const *const self,
        R2_Value *const ret)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface1_check_guard(self);
    R2_RESULT_TRY0(r);
#endif//
    return R2_Object2_get_value(R2_Object2_Interface1_getobjptr(self), ret);
}

R2_Result R2_Object2_Interface1_set_value(R2_Interface1 *const self,
        R2_Value const *const arg)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface1_check_guard(self);
    R2_RESULT_TRY0(r);
#endif//
    return R2_Object2_set_value(R2_Object2_Interface1_getobjptr_mut(self), arg);
}

static R2_Interface1Vtbl const R2_Object2_Interface1_vtbl = {
    &R2_Interface1_ID,
    offsetof(R2_Object2, iface1),
    R2_Object2_Interface1_query_interface,
    R2_Object2_Interface1_query_interface_mut,
    R2_Interface1_get,
    R2_Interface1_set,
    R2_Interface1_action,
    R2_Object2_Interface1_get_value,
    R2_Object2_Interface1_set_value
};

/////////////////////////////////////////////////////////////////////////////

static R2_Object2 const *R2_Object2_Interface2_getobjptr(
    R2_Interface2 const *const self)
{
    R2_Object2 const *const oself = R2_INTERFACE_GET_OBJPTR(R2_Object2, self);
    return oself;
}

static R2_Object2 *R2_Object2_Interface2_getobjptr_mut(R2_Interface2 *const
        self)
{
    R2_Object2 *const oself = R2_INTERFACE_GET_OBJPTR_MUT(R2_Object2, self);
    return oself;
}

R2_Result R2_Object2_Interface2_query_interface(R2_Interface2 const *const self,
        R2_InterfaceID const *const iid, void const **const ret)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface2_check_guard(self);
    R2_RESULT_TRY0(r);
#endif//
    return R2_Object2_query_interface(R2_Object2_Interface2_getobjptr(self), iid,
                                      ret);
}

R2_Result R2_Object2_Interface2_query_interface_mut(R2_Interface2 *const self,
        R2_InterfaceID const *const iid, void **const ret)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface2_check_guard(self);
    R2_RESULT_TRY0(r);
#endif//
    return R2_Object2_query_interface_mut(R2_Object2_Interface2_getobjptr_mut(self),
                                          iid, ret);
}


R2_Result R2_Object2_Interface2_get_value(R2_Interface2 const *const self,
        R2_Value *const ret)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface2_check_guard(self);
    R2_RESULT_TRY0(r);
#endif//
    return R2_Object2_get_value(R2_Object2_Interface2_getobjptr(self), ret);
}

R2_Result R2_Object2_Interface2_set_value(R2_Interface2 *const self,
        R2_Value const *const arg)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface2_check_guard(self);
    R2_RESULT_TRY0(r);
#endif//
    return R2_Object2_set_value(R2_Object2_Interface2_getobjptr_mut(self), arg);
}


R2_Result R2_Object2_Interface2_get_objects(R2_Interface2 const *const self,
        R2_Value *const ret)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface2_check_guard(self);
    R2_RESULT_TRY0(r);
#endif//
    return R2_Object2_get_objects(R2_Object2_Interface2_getobjptr(self), ret);
}

R2_Result R2_Object2_Interface2_set_objects(R2_Interface2 *const self,
        R2_Value const *const arg)
{
    // could recheck self->_vtbl again, on the rare/slim chance that it's been corrupted.
#if 0
    R2_Result r;
    r = R2_Interface2_check_guard(self);
    R2_RESULT_TRY0(r);
#endif//
    return R2_Object2_set_objects(R2_Object2_Interface2_getobjptr_mut(self), arg);
}


static R2_Interface2Vtbl const R2_Object2_Interface2_vtbl = {
    &R2_Interface2_ID,
    offsetof(R2_Object2, iface2),
    R2_Object2_Interface2_query_interface,
    R2_Object2_Interface2_query_interface_mut,
    R2_Object2_Interface2_get_value,
    R2_Object2_Interface2_set_value,
    R2_Object2_Interface2_get_objects,
    R2_Object2_Interface2_set_objects
};

///////////////////////////////////////////////////////////////////////////////
static void R2_Object2_invalidate(R2_Object2 *const self)
{
    // completely corrupt object, including interface vtlb pointers (oops).
    // should be able to use any R2_value here, but
    // on amd64 without a os level function to determine readability, then
    // use 0x0 (NULL)
    memset(self, 0x0, sizeof(*self));
}

void R2_Object2_destroy(R2_Object2 *const self)
{
    R2_Object2_invalidate(self);
}

R2_Object2 R2_Object2_new(void)
{
    // prob will be initialising value.
    // and vtbls need to be initialised via init list as thats the only way to
    // init const * const members.
    R2_Object2 inst = {
        .value = 0,
        .iface1 = R2_Interface1_new(&R2_Object2_Interface1_vtbl),
        .iface2 = R2_Interface2_new(&R2_Object2_Interface2_vtbl),
    };
    // need to stop vtbls in interfaces being mutable in a mutable R2_Object2 inst.
    // they shouldn't be.
    return inst;
}

R2_Result R2_Object2_get_value(R2_Object2 const *const self,
                               R2_Value *const ret)
{
    *ret = self->value;
    return R2_Result_ok(0);
}

R2_Result R2_Object2_set_value(R2_Object2 *const self,
                               R2_Value const *const arg)
{
    self->value = *arg;
    return R2_Result_ok(0);
}

R2_Result R2_Object2_get_objects(R2_Object2 const *const self,
                                 R2_Value *const ret)
{
    ((void)self);
    ((void)ret);
    return R2_Result_err(R2_Err_NotImplemented);
}

R2_Result R2_Object2_set_objects(R2_Object2 *const self,
                                 R2_Value const *const arg)
{
    ((void)self);
    ((void)arg);
    return R2_Result_err(R2_Err_NotImplemented);
}
