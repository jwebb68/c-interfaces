#include "m4-interface2.h"

#include "m4-ptrvalidate.h"


M4_InterfaceID const M4_Interface2_ID = "M4_Interface2";


void M4_Interface2_new(M4_Interface2 *const self,
                       M4_Interface2Vtbl const *const vtbl)
{
    // much nastyness, casting const *const to const *
    M4_Interface2Vtbl const **p = (M4_Interface2Vtbl const **)&self->_vtbl;
    *p = vtbl;
}


#if 0
void M4_Interface2_try_check_vtbl(
    M4_Interface2 const *self,
    M4_Result *const ret,
)
{
#if 0
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
    if (!M4_IS_STRUCT_READABLE(self)) {
        M4_Result_err(ret, M4_Err_InvalidInterface);
        return;
    }
    if (!M4_IS_STRUCT_READABLE(self->_vtbl)) {
        M4_Result_err(ret, M4_Err_InvalidInterface);
    }
#endif//0
    M4_Interface_try_check(ret, self->_vtbl, self->_vtbl->token);
}
#endif


void M4_Interface2_check_vtbl_(char const *file, size_t line,
                               M4_Interface2 const *self)
{
#if 0
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
    M4_check_struct_readable(file, line, self);
    M4_check_struct_readable(file, line, self->_vtbl);
#endif//0
    M4_Interface_check_(file, line, self->_vtbl, self->_vtbl->token);
}


static M4_Interface2Vtbl const *M4_Interface2_get_vtbl(
    M4_Interface2 const *const self)
{
    M4_Interface2_check_vtbl(self);
    return self->_vtbl;
}


void M4_Interface2_query_interface(
    M4_Interface2 const *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **const val
)
{
    M4_Interface2_get_vtbl(self)->query_interface(self, ret, iid, val);
}


void M4_Interface2_query_interface_mut(
    M4_Interface2 *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **const val
)
{
    M4_Interface2_get_vtbl(self)->query_interface_mut(self, ret, iid, val);
}


/////////////////////////////////////////////////////////////////////////////

void M4_Interface2_get_value(
    M4_Interface2 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    M4_Interface2_get_vtbl(self)->get_value(self, ret, val);
}


void M4_Interface2_set_value(
    M4_Interface2 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    M4_Interface2_get_vtbl(self)->set_value(self, ret, arg);
}


void M4_Interface2_get_objects(
    M4_Interface2 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    M4_Interface2_get_vtbl(self)->get_objects(self, ret, val);
}


void M4_Interface2_set_objects(
    M4_Interface2 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    M4_Interface2_get_vtbl(self)->set_objects(self, ret, arg);
}
