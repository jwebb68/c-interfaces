#include "m2-interface2.h"

#include "m2-ptrvalidate.h"


M2_InterfaceID const M2_Interface2_ID = "M2_Interface2";


void M2_Interface2_new(M2_Interface2 *const self,
                       M2_Interface2Vtbl const *const vtbl)
{
    // much nastyness, casting const *const to const *
    M2_Interface2Vtbl const **p = (M2_Interface2Vtbl const **)&self->_vtbl;
    *p = vtbl;
}


#if 0
void M2_Interface2_try_check_vtbl(M2_Interface2 const *self,
                                  M2_Result *const ret
                                 )
{
#if 0
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
    if (!M2_IS_STRUCT_READABLE(self)) {
        M2_Result_err(ret, M2_Err_InvalidInterface);
        return;
    }
    if (!M2_IS_STRUCT_READABLE(self->_vtbl)) {
        M2_Result_err(ret, M2_Err_InvalidInterface);
    }
#endif//0
    M2_Interface_try_check(self->_vtbl, self->_vtbl->token, ret);
}
#endif


void M2_Interface2_check_vtbl_(char const *file, size_t line,
                               M2_Interface2 const *self)
{
#if 0
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
    M2_check_struct_readable(file, line, self);
    M2_check_struct_readable(file, line, self->_vtbl);
#endif//0
    M2_Interface_check_(file, line, self->_vtbl, self->_vtbl->token);
}


static M2_Interface2Vtbl const *M2_Interface2_get_vtbl(M2_Interface2 const
        *const self)
{
    M2_Interface2_check_vtbl(self);
    return self->_vtbl;
}


void M2_Interface2_query_interface(M2_Interface2 const *const self,
                                   M2_InterfaceID const *const iid,
                                   void const **const val,
                                   M2_Result *const ret
                                  )
{
    M2_Interface2_get_vtbl(self)->query_interface(self, iid, val, ret);
}


void M2_Interface2_query_interface_mut(M2_Interface2 *const self,
                                       M2_InterfaceID const *const iid,
                                       void **const val,
                                       M2_Result *const ret
                                      )
{
    M2_Interface2_get_vtbl(self)->query_interface_mut(self, iid, val, ret);
}


/////////////////////////////////////////////////////////////////////////////

void M2_Interface2_get_value(M2_Interface2 const *const self,
                             M2_Value *const val,
                             M2_Result *const ret
                            )
{
    M2_Interface2_get_vtbl(self)->get_value(self, val, ret);
}


void M2_Interface2_set_value(M2_Interface2 *const self,
                             M2_Value const *const arg,
                             M2_Result *const ret
                            )
{
    M2_Interface2_get_vtbl(self)->set_value(self, arg, ret);
}


void M2_Interface2_get_objects(M2_Interface2 const *const self,
                               M2_Value *const val,
                               M2_Result *const ret
                              )
{
    M2_Interface2_get_vtbl(self)->get_objects(self, val, ret);
}


void M2_Interface2_set_objects(M2_Interface2 *const self,
                               M2_Value const *const arg,
                               M2_Result *const ret
                              )
{
    M2_Interface2_get_vtbl(self)->set_objects(self, arg, ret);
}
