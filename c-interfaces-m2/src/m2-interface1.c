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


/////////////////////////////////////////////////////////////////////////////

// an example of dynamic dispatch using ids for properties/actions
// needs re-implementing per interface though because of typed ptr in functon
// calls (and I don't want to remove that.. it's bad enough using void *)

typedef struct M2_PropertyDef_s {
    // use an id instead of array position so I can have gaps in the number
    // range and have a smaller array in the resultant image.
    M2_AttributeID aid;
    void (*get)(M2_Interface1 const *const self,
                M2_Value *const rval,
                M2_Result *const ret
               );
    void (*set)(M2_Interface1 *const self,
                M2_Value const *const arg,
                M2_Result *const ret
               );
} M2_PropertyDef;


typedef struct M2__ActionDef {
    M2_ActionID aid;
    void (*action)(M2_Interface1 *const self,
                   M2_Value const *const arg,
                   M2_Value *const val,
                   M2_Result *const ret
                  );
} M2_ActionDef;


static const M2_PropertyDef M2_Interface1_propdefs[] = {
    {1, M2_Interface1_get_value, M2_Interface1_set_value},
};
// TODO: maybe wrap this into a DEFINE_PROPMAP/PROP()/END_PROPMAP macros

//static const M2_ActionDef M2_Interface1_actiondefs[] = {
//};
// TODO: maybe wrap this into a DEFINE_ACTIONMAP/ACTION()/END_ACTIONMAP macros

static void M2_Interface1_Propdef_lookup(M2_PropertyDef const *begin,
        M2_PropertyDef const *end,
        M2_AttributeID aid,
        M2_PropertyDef const **const val,
        M2_Result *const ret
                                        )
{
    for (M2_PropertyDef const *it = begin; it != end; ++it) {
        if (it->aid == aid) {
            *val = it;
            M2_Result_ok(ret, 0);
            return;
        }
    }
    M2_Result_err(ret, M2_Err_InvalidAttributeID);
}

#if 0
static void M2_Interface1_Actiondef_lookup(M2_ActionDef const *const begin,
        M2_ActionDef const *const end,
        M2_AttributeID aid,
        M2_ActionDef const **val,
        M2_Result *const ret)
{
    for (M2_ActionDef const *it = begin; it != end; ++it) {
        if (it->aid == aid) {
            *ret = it;
            M2_Result_ok(ret, 0);
            return;
        }
    }
    M2_Result_err(ret, M2_Err_InvalidActionID);
}
#endif

void M2_Interface1_get(M2_Interface1 const *const self,
                       M2_AttributeID const aid,
                       M2_Value *const val,
                       M2_Result *const ret
                      )
{
    M2_Interface1_get_vtbl(self);
    M2_PropertyDef const *def;
    M2_Interface1_Propdef_lookup(M2_CARRAY_BEGIN(M2_Interface1_propdefs),
                                 M2_CARRAY_END(M2_Interface1_propdefs),
                                 aid, &def, ret);
    M2_RESULT_TRY0(ret);
    def->get(self, val, ret);
}

void M2_Interface1_set(M2_Interface1 *const self,
                       M2_AttributeID const aid,
                       M2_Value const *const arg,
                       M2_Result *const ret
                      )
{
    M2_Interface1_get_vtbl(self);
    M2_PropertyDef const *def;
    M2_Interface1_Propdef_lookup(M2_CARRAY_BEGIN(M2_Interface1_propdefs),
                                 M2_CARRAY_END(M2_Interface1_propdefs),
                                 aid, &def, ret);
    M2_RESULT_TRY0(ret);
    def->set(self, arg, ret);
}


void M2_Interface1_action(M2_Interface1 *const self,
                          M2_ActionID const aid,
                          M2_Value const *const arg,
                          M2_Value *const val,
                          M2_Result *const ret
                         )
{
    ((void)aid);
    ((void)arg);
    ((void)val);
    ((void)self);
    M2_Interface1_get_vtbl(self);
    M2_Result_err(ret, M2_Err_InvalidActionID);
#if 0
    M2_ActionDef const *def;
    M2_Interface1_Actiondef_lookup(M2_CARRAY_BEGIN(M2_Interface1_actiondefs),
                                   M2_CARRAY_END(M2_Interface1_actiondefs),
                                   aid, &def, ret);
    M2_RESULT_TRY0(ret);
    def->action(self, arg, ret);
#endif
}


/////////////////////////////////////////////////////////////////////////////

void M2_Interface1_get_value(M2_Interface1 const *const self,
                             M2_Value *const val,
                             M2_Result *const ret
                            )
{
    M2_Interface1_get_vtbl(self)->get_value(self, val, ret);
}


void M2_Interface1_set_value(M2_Interface1 *const self,
                             M2_Value const *const arg,
                             M2_Result *const ret
                            )
{
    M2_Interface1_get_vtbl(self)->set_value(self, arg, ret);
}
