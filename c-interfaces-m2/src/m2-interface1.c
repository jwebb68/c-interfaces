#include "m2-interface1.h"

#include "m2-carray.h"
#include "m2-ptrvalidate.h"
#include "m2-panic.h"


M2_InterfaceID const M2_Interface1_ID = "M2_Interface1";


#if 0
#define M2_Interface1_new(self, vtbl) \
    { uint8_t *s = (uint8_t *)(self); \
        M2_Interface1Vtbl const **p = (M2_Interface1Vtbl const **)(s + offsetof(M2_Interface1, _vtbl)); \
        *p = (vtbl); }
#endif


#if 0
void M2_Interface1_new(M2_Interface1 *const self,
                       M2_Interface1Vtbl const *const vtbl)
{
    // annoyingly, I cannot get this to auto-inline.
    // in fast/-O3 or minsize, unless I use a macro

    // // HAAACK: dirty nasty hack to write to a const * const
    // // and compiler still does not inline it.
    M2_Interface1Vtbl const **p = (M2_Interface1Vtbl const **)&self->_vtbl;
    *p = vtbl;

    // // HAAACK: dirty nasty hack to write to a const * const
    // // and compiler still does not inline it.
    // uint8_t *s = (uint8_t *)self;
    // M2_Interface1Vtbl const **p = (M2_Interface1Vtbl const **)(s + offsetof(M2_Interface1, _vtbl));
    // *p = vtbl;

    // // HAAACK: dirty nasty hack to write to a const * const
    // // and compiler still does not inline it.
    // typedef struct Interface1Mut_s {
    //     M2_Interface1Vtbl const *_vtbl;
    // } Interface1Mut;
    // Interface1Mut *const mself = (Interface1Mut *)self;
    // mself->_vtbl = vtbl;
}
#endif

#if 0
void M2_Interface1_try_check_vtbl(M2_Interface1 const *const self,
                                  M2_Result *const ret
                                 )
{
    // Need to check vtbl pointed to by self is expected.
    // the in-ram struct can corrupt, leaving _vtbl pointing to something other than the vtbl expected.
    // if this happens it's most likely _vtbl ptr is not going to match value that it's pointng to,
    // so use that to validate it.

    // check that vbtl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
#if 0
    if (!M2_IS_STRUCT_READABLE(self)) {
        M2_Result_err(ret, M2_Err_InvalidInterface);
        return;
    }
    if (!M2_IS_STRUCT_READABLE(self->_vtbl)) {
        M2_Result_err(ret, M2_Err_InvalidInterface);
        return
    }
#endif//
    M2_Interface_try_check(&self->_vtbl, self->_vtbl->token, ret);
}
#endif

void M2_Interface1_check_vtbl_(char const *file, size_t line,
                               M2_Interface1 const *const self)
{
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
#if 0
    M2_check_struct_readable(file, line, self);
    M2_check_struct_readable(file, line, self->_vtbl);
#endif//
    M2_Interface_check_(file, line, self->_vtbl, self->_vtbl->token);
}


static M2_Interface1Vtbl const *M2_Interface1_get_vtbl(M2_Interface1 const
        *const self)
{
    M2_Interface1_check_vtbl(self);
    return self->_vtbl;
}


void M2_Interface1_query_interface(M2_Interface1 const *const self,
                                   M2_InterfaceID const *const iid,
                                   void const **const val,
                                   M2_Result *const ret
                                  )
{
    M2_Interface1_get_vtbl(self)->query_interface(self, iid, val, ret);
}


void M2_Interface1_query_interface_mut(M2_Interface1 *const self,
                                       M2_InterfaceID const *const iid,
                                       void **const val,
                                       M2_Result *const ret
                                      )
{
    M2_Interface1_get_vtbl(self)->query_interface_mut(self, iid, val, ret);
}


/////////////////////////////////////////////////////////////////////////////

void M2_Interface1_foo(M2_Interface1 *const self)
{
    M2_Interface1_get_vtbl(self)->foo(self);
}

#if 0
// adds the result try, still messy
void M2_Interface1_foo22(M2_Interface1 *const self, M2_Result *const ret)
{
    M2_Interface1_try_check_vtbl(self, ret);
    M2_RESULT_TRY0(ret);
    self->_vtbl->foo2(self, ret);
}
#endif

void M2_Interface1_foo2(M2_Interface1 *const self,
                        M2_Result *const ret)
{
    M2_Interface1_get_vtbl(self)->foo2(self, ret);
}
