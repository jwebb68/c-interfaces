#include "r2-interface2.h"

#include "r2-ptrvalidate.h"

R2_InterfaceID const R2_Interface2_ID = "R2_Interface2";

R2_Interface2 R2_Interface2_new(R2_Interface2Vtbl const *const vtbl)
{
    R2_Interface2 inst = {._vtbl = vtbl};
    return inst;
}

// R2_Result R2_Interface2_check_guard(R2_Interface2 const *self) {
//     // Need to check vtbl is in valid readable range, which should be
//     // flash (r/o memory).
//     // And that will depend on CPU and platform architecture.
//     // as the deref os ctbl causes a segf on amd64.
//     // Not best solution, as now the
// #if 0
//     if (!R2_IS_STRUCT_READABLE(self)) {
//         return R2_Result_err(R2_Err_InvalidInterface);
//     }
//     if (!R2_IS_STRUCT_READABLE(self->_vtbl)) {
//         return R2_Result_err(R2_Err_InvalidInterface);
//     }
// #endif
//     return R2_Interface_check_guard(&R2_Interface2_ID, self->_vtbl->guard);
// }

void R2_Interface2_check_guard(R2_Interface2 const *self)
{
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
#if 0
    R2_CHECK_STRUCT_READABLE(self);
    R2_CHECK_STRUCT_READABLE(self->_vtbl);
#endif
    R2_Interface_check_guard(&R2_Interface2_ID, self->_vtbl->guard);
}

R2_Result R2_Interface2_query_interface(R2_Interface2 const *const self,
                                        R2_InterfaceID const *const iid, void const **const ret)
{
    // R2_Result r;
    // r = R2_Interface2_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface2_check_guard(self);
    return self->_vtbl->query_interface(self, iid, ret);
}

R2_Result R2_Interface2_query_interface_mut(R2_Interface2 *const self,
        R2_InterfaceID const *const iid, void **const ret)
{
    // R2_Result r;
    // r = R2_Interface2_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface2_check_guard(self);
    return self->_vtbl->query_interface_mut(self, iid, ret);
}

/////////////////////////////////////////////////////////////////////////////

R2_Result R2_Interface2_get_value(R2_Interface2 const *const self,
                                  R2_Value *const ret)
{
    // R2_Result r;
    // r = R2_Interface2_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface2_check_guard(self);
    return self->_vtbl->get_value(self, ret);
}

R2_Result R2_Interface2_set_value(R2_Interface2 *const self,
                                  R2_Value const *const arg)
{
    // R2_Result r;
    // r = R2_Interface2_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface2_check_guard(self);
    return self->_vtbl->set_value(self, arg);
}

R2_Result R2_Interface2_get_objects(R2_Interface2 const *const self,
                                    R2_Value *const ret)
{
    // R2_Result r;
    // r = R2_Interface2_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface2_check_guard(self);
    return self->_vtbl->get_objects(self, ret);
}

R2_Result R2_Interface2_set_objects(R2_Interface2 *const self,
                                    R2_Value const *const arg)
{
    // R2_Result r;
    // r = R2_Interface2_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface2_check_guard(self);
    return self->_vtbl->set_objects(self, arg);
}
