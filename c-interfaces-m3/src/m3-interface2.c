#include "m3-interface2.h"

#include "m3-ptrvalidate.h"


M3_InterfaceID const M3_Interface2_ID = "M3_Interface2";


void M3_Interface2_new(M3_Interface2 *const self,
                       M3_Interface2Vtbl const *const vtbl)
{
    // much nastyness, casting const *const to const *
    M3_Interface2Vtbl const **p = (M3_Interface2Vtbl const **)&self->_vtbl;
    *p = vtbl;
}


#if 0
void M3_Interface2_try_check_vtbl(M3_Result *const ret,
                                  M3_Interface2 const *self,
                                 )
{
#if 0
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
    if (!M3_IS_STRUCT_READABLE(self)) {
        M3_Result_err(ret, M3_Err_InvalidInterface);
        return;
    }
    if (!M3_IS_STRUCT_READABLE(self->_vtbl)) {
        M3_Result_err(ret, M3_Err_InvalidInterface);
    }
#endif//0
    M3_Interface_try_check(ret, self->_vtbl, self->_vtbl->token);
}
#endif


void M3_Interface2_check_vtbl_(char const *file, size_t line,
                               M3_Interface2 const *self)
{
#if 0
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
    M3_check_struct_readable(file, line, self);
    M3_check_struct_readable(file, line, self->_vtbl);
#endif//0
    M3_Interface_check_(file, line, self->_vtbl, self->_vtbl->token);
}


static M3_Interface2Vtbl const *M3_Interface2_get_vtbl(
    M3_Interface2 const *const self)
{
    M3_Interface2_check_vtbl(self);
    return self->_vtbl;
}


void M3_Interface2_query_interface(M3_Result *const ret,
                                   M3_Interface2 const *const self,
                                   M3_InterfaceID const *const iid,
                                   void const **const val
                                  )
{
    M3_Interface2_get_vtbl(self)->query_interface(ret, self, iid, val);
}


void M3_Interface2_query_interface_mut(M3_Result *const ret,
                                       M3_Interface2 *const self,
                                       M3_InterfaceID const *const iid,
                                       void **const val
                                      )
{
    M3_Interface2_get_vtbl(self)->query_interface_mut(ret, self, iid, val);
}


/////////////////////////////////////////////////////////////////////////////

void M3_Interface2_get_value(M3_Result *const ret,
                             M3_Interface2 const *const self,
                             M3_Value *const val
                            )
{
    M3_Interface2_get_vtbl(self)->get_value(ret, self, val);
}


void M3_Interface2_set_value(M3_Result *const ret,
                             M3_Interface2 *const self,
                             M3_Value const *const arg
                            )
{
    M3_Interface2_get_vtbl(self)->set_value(ret, self, arg);
}


void M3_Interface2_get_objects(M3_Result *const ret,
                               M3_Interface2 const *const self,
                               M3_Value *const val
                              )
{
    M3_Interface2_get_vtbl(self)->get_objects(ret, self, val);
}


void M3_Interface2_set_objects(M3_Result *const ret,
                               M3_Interface2 *const self,
                               M3_Value const *const arg
                              )
{
    M3_Interface2_get_vtbl(self)->set_objects(ret, self, arg);
}
