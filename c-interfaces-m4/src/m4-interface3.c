#include "m4-interface3.h"

#include "m4-carray.h"
#include "m4-ptrvalidate.h"
#include "m4-panic.h"


M4_InterfaceID const M4_Interface3_ID = "M4_Interface3";


#if 0
#define M4_Interface3_new(self, vtbl) \
    { uint8_t *s = (uint8_t *)(self); \
        M4_Interface3Vtbl const **p = (M4_Interface3Vtbl const **)(s + offsetof(M4_Interface3, _vtbl)); \
        *p = (vtbl); }
#endif


#if 0
void M4_Interface3_new(M4_Interface3 *const self,
                       M4_Interface3Vtbl const *const vtbl)
{
    // annoyingly, I cannot get this to auto-inline.
    // in fast/-O3 or minsize, unless I use a macro

    // // HAAACK: dirty nasty hack to write to a const * const
    // // and compiler still does not inline it.
    M4_Interface3Vtbl const **p = (M4_Interface3Vtbl const **)&self->_vtbl;
    *p = vtbl;

    // // HAAACK: dirty nasty hack to write to a const * const
    // // and compiler still does not inline it.
    // uint8_t *s = (uint8_t *)self;
    // M4_Interface3Vtbl const **p = (M4_Interface3Vtbl const **)(s + offsetof(M4_Interface3, _vtbl));
    // *p = vtbl;

    // // HAAACK: dirty nasty hack to write to a const * const
    // // and compiler still does not inline it.
    // typedef struct Interface1Mut_s {
    //     M4_Interface3Vtbl const *_vtbl;
    // } Interface1Mut;
    // Interface1Mut *const mself = (Interface1Mut *)self;
    // mself->_vtbl = vtbl;
}
#endif

#if 0
void M4_Interface3_try_check_vtbl(M4_Interface3 const *const self,
                                  M4_Result *const ret,
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
    if (!M4_IS_STRUCT_READABLE(self)) {
        M4_Result_err(ret, M4_Err_InvalidInterface);
        return;
    }
    if (!M4_IS_STRUCT_READABLE(self->_vtbl)) {
        M4_Result_err(ret, M4_Err_InvalidInterface);
        return
    }
#endif//
    M4_Interface_try_check(&self->_vtbl, ret, self->_vtbl->token);
}
#endif

void M4_Interface3_check_vtbl_(char const *file, size_t line,
                               M4_Interface3 const *const self)
{
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
#if 0
    M4_check_struct_readable(file, line, self);
    M4_check_struct_readable(file, line, self->_vtbl);
#endif//
    M4_Interface_check_(file, line, self->_vtbl, self->_vtbl->token);
}


static M4_Interface3Vtbl const *M4_Interface3_get_vtbl(
    M4_Interface3 const *const self)
{
    M4_Interface3_check_vtbl(self);
    return self->_vtbl;
}


void M4_Interface3_query_interface(
    M4_Interface3 const *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **const val
)
{
    M4_Interface3_get_vtbl(self)->query_interface(self, ret, iid, val);
}


void M4_Interface3_query_interface_mut(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **const val
)
{
    M4_Interface3_get_vtbl(self)->query_interface_mut(self,  ret, iid, val);
}


/////////////////////////////////////////////////////////////////////////////

// an example of dynamic dispatch using ids for properties/actions
// needs re-implementing per interface though because of typed ptr in functon
// calls (and I don't want to remove that.. it's bad enough using void *)

typedef struct M4_PropertyDef_s {
    // use an id instead of array position so I can have gaps in the number
    // range and have a smaller array in the resultant image.
    M4_AttributeID aid;
    void (*get)(
        M4_Interface3 const *const self,
        M4_Result *const ret,
        M4_Value *const rval
    );
    void (*set)(
        M4_Interface3 *const self,
        M4_Result *const ret,
        M4_Value const *const arg
    );
} M4_PropertyDef;


typedef struct M4__ActionDef {
    M4_ActionID aid;
    void (*action)(
        M4_Interface3 *const self,
        M4_Result *const ret,
        M4_Value const *const arg,
        M4_Value *const val
    );
} M4_ActionDef;


static const M4_PropertyDef M4_Interface3_propdefs[] = {
    {1, M4_Interface3_get_value1, M4_Interface3_set_value1},
    {2, M4_Interface3_get_value2, M4_Interface3_set_value2},
    {2, M4_Interface3_get_value3, M4_Interface3_set_value3},
};
// TODO: maybe wrap this into a DEFINE_PROPMAP/PROP()/END_PROPMAP macros

static const M4_ActionDef M4_Interface3_actiondefs[] = {
    {1, M4_Interface3_action1},
    {2, M4_Interface3_action2},
};
// TODO: maybe wrap this into a DEFINE_ACTIONMAP/ACTION()/END_ACTIONMAP macros

static M4_PropertyDef const *M4_Interface3_Propdef_lookup(
    M4_Result *const ret,
    M4_PropertyDef const *begin,
    M4_PropertyDef const *end,
    M4_AttributeID aid
)
{
    for (M4_PropertyDef const *it = begin; it != end; ++it) {
        if (it->aid == aid) {
            M4_Result_ok(ret, 0);
            return it;
        }
    }
    M4_Result_err(ret, M4_Err_InvalidAttributeID);
    return NULL;
}


static M4_ActionDef const *M4_Interface3_Actiondef_lookup(
    M4_Result *const ret,
    M4_ActionDef const *const begin,
    M4_ActionDef const *const end,
    M4_AttributeID const aid)
{
    for (M4_ActionDef const *it = begin; it != end; ++it) {
        if (it->aid == aid) {
            M4_Result_ok(ret, 0);
            return it;
        }
    }
    M4_Result_err(ret, M4_Err_InvalidActionID);
    return NULL;
}


void M4_Interface3_get(
    M4_Interface3 const *const self,
    M4_Result *const ret,
    M4_AttributeID const aid,
    M4_Value *const val
)
{
    // don't check self/iface here as will be checked in setter..
    //M4_Interface3_get_vtbl(self);
    M4_PropertyDef const *def;
    def = M4_Interface3_Propdef_lookup(ret,
                                       M4_CARRAY_BEGIN(M4_Interface3_propdefs),
                                       M4_CARRAY_END(M4_Interface3_propdefs),
                                       aid);
    M4_RESULT_TRY0(ret);
    def->get(self, ret, val);
}


void M4_Interface3_set(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_AttributeID const aid,
    M4_Value const *const arg
)
{
    // don't check self/iface here as will be checked in setter..
    //M4_Interface3_get_vtbl(self);
    M4_PropertyDef const *def;
    def = M4_Interface3_Propdef_lookup(ret,
                                       M4_CARRAY_BEGIN(M4_Interface3_propdefs),
                                       M4_CARRAY_END(M4_Interface3_propdefs),
                                       aid);
    M4_RESULT_TRY0(ret);
    def->set(self, ret, arg);
}


void M4_Interface3_action(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_ActionID const aid,
    M4_Value const *const arg,
    M4_Value *const out
)
{
    // don't check self/iface here as will be checked in what's called..
    //M4_Interface3_get_vtbl(self);
    M4_ActionDef const *def;
    def = M4_Interface3_Actiondef_lookup(ret,
                                         M4_CARRAY_BEGIN(M4_Interface3_actiondefs),
                                         M4_CARRAY_END(M4_Interface3_actiondefs),
                                         aid);
    M4_RESULT_TRY0(ret);
    def->action(self, ret, arg, out);
}


/////////////////////////////////////////////////////////////////////////////

void M4_Interface3_get_value1(
    M4_Interface3 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    M4_Interface3_get_vtbl(self)->get_value1(self, ret, val);
}


void M4_Interface3_set_value1(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    M4_Interface3_get_vtbl(self)->set_value1(self, ret, arg);
}


void M4_Interface3_get_value2(
    M4_Interface3 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    M4_Interface3_get_vtbl(self)->get_value2(self, ret, val);
}


void M4_Interface3_set_value2(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    M4_Interface3_get_vtbl(self)->set_value2(self, ret, arg);
}


void M4_Interface3_get_value3(
    M4_Interface3 const *const self,
    M4_Result *const ret,
    M4_Value *const val
)
{
    M4_Interface3_get_vtbl(self)->get_value3(self, ret, val);
}


void M4_Interface3_set_value3(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_Value const *const arg
)
{
    M4_Interface3_get_vtbl(self)->set_value3(self, ret, arg);
}


void M4_Interface3_action1(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_Value const *const arg,
    M4_Value *const out
)
{
    M4_Interface3_get_vtbl(self)->action1(self, ret, arg, out);
}


void M4_Interface3_action2(
    M4_Interface3 *const self,
    M4_Result *const ret,
    M4_Value const *const arg,
    M4_Value *const out
)
{
    M4_Interface3_get_vtbl(self)->action2(self, ret, arg, out);
}
