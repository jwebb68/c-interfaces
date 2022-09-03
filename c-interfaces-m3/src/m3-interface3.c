#include "m3-interface3.h"

#include "m3-carray.h"
#include "m3-ptrvalidate.h"
#include "m3-panic.h"


M3_InterfaceID const M3_Interface3_ID = "M3_Interface3";


#if 0
#define M3_Interface3_new(self, vtbl) \
    { uint8_t *s = (uint8_t *)(self); \
        M3_Interface3Vtbl const **p = (M3_Interface3Vtbl const **)(s + offsetof(M3_Interface3, _vtbl)); \
        *p = (vtbl); }
#endif


#if 0
void M3_Interface3_new(M3_Interface3 *const self,
                       M3_Interface3Vtbl const *const vtbl)
{
    // annoyingly, I cannot get this to auto-inline.
    // in fast/-O3 or minsize, unless I use a macro

    // // HAAACK: dirty nasty hack to write to a const * const
    // // and compiler still does not inline it.
    M3_Interface3Vtbl const **p = (M3_Interface3Vtbl const **)&self->_vtbl;
    *p = vtbl;

    // // HAAACK: dirty nasty hack to write to a const * const
    // // and compiler still does not inline it.
    // uint8_t *s = (uint8_t *)self;
    // M3_Interface3Vtbl const **p = (M3_Interface3Vtbl const **)(s + offsetof(M3_Interface3, _vtbl));
    // *p = vtbl;

    // // HAAACK: dirty nasty hack to write to a const * const
    // // and compiler still does not inline it.
    // typedef struct Interface1Mut_s {
    //     M3_Interface3Vtbl const *_vtbl;
    // } Interface1Mut;
    // Interface1Mut *const mself = (Interface1Mut *)self;
    // mself->_vtbl = vtbl;
}
#endif

#if 0
void M3_Interface3_try_check_vtbl(M3_Result *const ret,
                                  M3_Interface3 const *const self
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
    if (!M3_IS_STRUCT_READABLE(self)) {
        M3_Result_err(ret, M3_Err_InvalidInterface);
        return;
    }
    if (!M3_IS_STRUCT_READABLE(self->_vtbl)) {
        M3_Result_err(ret, M3_Err_InvalidInterface);
        return
    }
#endif//
    M3_Interface_try_check(ret, &self->_vtbl, self->_vtbl->token);
}
#endif

void M3_Interface3_check_vtbl_(char const *file, size_t line,
                               M3_Interface3 const *const self)
{
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
#if 0
    M3_check_struct_readable(file, line, self);
    M3_check_struct_readable(file, line, self->_vtbl);
#endif//
    M3_Interface_check_(file, line, self->_vtbl, self->_vtbl->token);
}


static M3_Interface3Vtbl const *M3_Interface3_get_vtbl(
    M3_Interface3 const *const self)
{
    M3_Interface3_check_vtbl(self);
    return self->_vtbl;
}


void M3_Interface3_query_interface(M3_Result *const ret,
                                   M3_Interface3 const *const self,
                                   M3_InterfaceID const *const iid,
                                   void const **const val
                                  )
{
    M3_Interface3_get_vtbl(self)->query_interface(ret, self, iid, val);
}


void M3_Interface3_query_interface_mut(M3_Result *const ret,
                                       M3_Interface3 *const self,
                                       M3_InterfaceID const *const iid,
                                       void **const val
                                      )
{
    M3_Interface3_get_vtbl(self)->query_interface_mut(ret, self, iid, val);
}


/////////////////////////////////////////////////////////////////////////////

// an example of dynamic dispatch using ids for properties/actions
// needs re-implementing per interface though because of typed ptr in functon
// calls (and I don't want to remove that.. it's bad enough using void *)

typedef struct M3_PropertyDef_s {
    // use an id instead of array position so I can have gaps in the number
    // range and have a smaller array in the resultant image.
    M3_AttributeID aid;
    void (*get)(M3_Result *const ret,
                M3_Interface3 const *const self,
                M3_Value *const rval
               );
    void (*set)(M3_Result *const ret,
                M3_Interface3 *const self,
                M3_Value const *const arg
               );
} M3_PropertyDef;


typedef struct M3__ActionDef {
    M3_ActionID aid;
    void (*action)(M3_Result *const ret,
                   M3_Interface3 *const self,
                   M3_Value const *const arg,
                   M3_Value *const val
                  );
} M3_ActionDef;


static const M3_PropertyDef M3_Interface3_propdefs[] = {
    {1, M3_Interface3_get_value1, M3_Interface3_set_value1},
    {2, M3_Interface3_get_value2, M3_Interface3_set_value2},
    {2, M3_Interface3_get_value3, M3_Interface3_set_value3},
};
// TODO: maybe wrap this into a DEFINE_PROPMAP/PROP()/END_PROPMAP macros

static const M3_ActionDef M3_Interface3_actiondefs[] = {
    {1, M3_Interface3_action1},
    {2, M3_Interface3_action2},
};
// TODO: maybe wrap this into a DEFINE_ACTIONMAP/ACTION()/END_ACTIONMAP macros

static M3_PropertyDef const *M3_Interface3_Propdef_lookup(
    M3_Result *const ret,
    M3_PropertyDef const *begin,
    M3_PropertyDef const *end,
    M3_AttributeID aid
)
{
    for (M3_PropertyDef const *it = begin; it != end; ++it) {
        if (it->aid == aid) {
            M3_Result_ok(ret, 0);
            return it;
        }
    }
    M3_Result_err(ret, M3_Err_InvalidAttributeID);
    return NULL;
}


static M3_ActionDef const *M3_Interface3_Actiondef_lookup(
    M3_Result *const ret,
    M3_ActionDef const *const begin,
    M3_ActionDef const *const end,
    M3_AttributeID const aid)
{
    for (M3_ActionDef const *it = begin; it != end; ++it) {
        if (it->aid == aid) {
            M3_Result_ok(ret, 0);
            return it;
        }
    }
    M3_Result_err(ret, M3_Err_InvalidActionID);
    return NULL;
}


void M3_Interface3_get(M3_Result *const ret,
                       M3_Interface3 const *const self,
                       M3_AttributeID const aid,
                       M3_Value *const val
                      )
{
    // don't check self/iface here as will be checked in setter..
    //M3_Interface3_get_vtbl(self);
    M3_PropertyDef const *def;
    def = M3_Interface3_Propdef_lookup(ret,
                                       M3_CARRAY_BEGIN(M3_Interface3_propdefs),
                                       M3_CARRAY_END(M3_Interface3_propdefs),
                                       aid);
    M3_RESULT_TRY0(ret);
    def->get(ret, self, val);
}


void M3_Interface3_set(M3_Result *const ret,
                       M3_Interface3 *const self,
                       M3_AttributeID const aid,
                       M3_Value const *const arg
                      )
{
    // don't check self/iface here as will be checked in setter..
    //M3_Interface3_get_vtbl(self);
    M3_PropertyDef const *def;
    def = M3_Interface3_Propdef_lookup(ret,
                                       M3_CARRAY_BEGIN(M3_Interface3_propdefs),
                                       M3_CARRAY_END(M3_Interface3_propdefs),
                                       aid);
    M3_RESULT_TRY0(ret);
    def->set(ret, self, arg);
}


void M3_Interface3_action(M3_Result *const ret,
                          M3_Interface3 *const self,
                          M3_ActionID const aid,
                          M3_Value const *const arg,
                          M3_Value *const out
                         )
{
    // don't check self/iface here as will be checked in what's called..
    //M3_Interface3_get_vtbl(self);
    M3_ActionDef const *def;
    def = M3_Interface3_Actiondef_lookup(ret,
                                         M3_CARRAY_BEGIN(M3_Interface3_actiondefs),
                                         M3_CARRAY_END(M3_Interface3_actiondefs),
                                         aid);
    M3_RESULT_TRY0(ret);
    def->action(ret, self, arg, out);
}


/////////////////////////////////////////////////////////////////////////////

void M3_Interface3_get_value1(M3_Result *const ret,
                              M3_Interface3 const *const self,
                              M3_Value *const val
                             )
{
    M3_Interface3_get_vtbl(self)->get_value1(ret, self, val);
}


void M3_Interface3_set_value1(M3_Result *const ret,
                              M3_Interface3 *const self,
                              M3_Value const *const arg
                             )
{
    M3_Interface3_get_vtbl(self)->set_value1(ret, self, arg);
}


void M3_Interface3_get_value2(M3_Result *const ret,
                              M3_Interface3 const *const self,
                              M3_Value *const val
                             )
{
    M3_Interface3_get_vtbl(self)->get_value2(ret, self, val);
}


void M3_Interface3_set_value2(M3_Result *const ret,
                              M3_Interface3 *const self,
                              M3_Value const *const arg
                             )
{
    M3_Interface3_get_vtbl(self)->set_value2(ret, self, arg);
}


void M3_Interface3_get_value3(M3_Result *const ret,
                              M3_Interface3 const *const self,
                              M3_Value *const val
                             )
{
    M3_Interface3_get_vtbl(self)->get_value3(ret, self, val);
}


void M3_Interface3_set_value3(M3_Result *const ret,
                              M3_Interface3 *const self,
                              M3_Value const *const arg
                             )
{
    M3_Interface3_get_vtbl(self)->set_value3(ret, self, arg);
}


void M3_Interface3_action1(M3_Result *const ret,
                           M3_Interface3 *const self,
                           M3_Value const *const arg,
                           M3_Value *const out
                          )
{
    M3_Interface3_get_vtbl(self)->action1(ret, self, arg, out);
}


void M3_Interface3_action2(M3_Result *const ret,
                           M3_Interface3 *const self,
                           M3_Value const *const arg,
                           M3_Value *const out
                          )
{
    M3_Interface3_get_vtbl(self)->action2(ret, self, arg, out);
}
