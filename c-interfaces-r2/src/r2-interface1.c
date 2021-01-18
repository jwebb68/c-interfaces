#include "r2-interface1.h"

#include "r2-carray.h"
#include "r2-ptrvalidate.h"

R2_InterfaceID const R2_Interface1_ID = "R2_Interface1";

R2_Interface1 R2_Interface1_new(R2_Interface1Vtbl const *const vtbl)
{
    R2_Interface1 inst = {
        ._vtbl = vtbl,
    };
    return inst;
}


// R2_Result R2_Interface1_check_guard(R2_Interface1 const *const self) {
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
// #endif//
//     return R2_Interface_check_guard(&R2_Interface1_ID, self->_vtbl->guard);
// }

void R2_Interface1_check_guard(R2_Interface1 const *const self)
{
    // Need to check vtbl is in valid readable range, which should be
    // flash (r/o memory).
    // And that will depend on CPU and platform architecture.
    // as the deref os ctbl causes a segf on amd64.
    // Not best solution, as now the
#if 0
    R2_CHECK_STRUCT_READABLE(self);
    R2_CHECK_STRUCT_READABLE(self->_vtbl);
#endif//
    R2_Interface_check_guard(&R2_Interface1_ID, self->_vtbl->guard);
}

R2_Result R2_Interface1_query_interface(R2_Interface1 const *const self,
                                        R2_InterfaceID const *const iid, void const **const val)
{
    // R2_Result r;
    // r = R2_Interface1_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface1_check_guard(self);
    return self->_vtbl->query_interface(self, iid, val);
}

R2_Result R2_Interface1_query_interface_mut(R2_Interface1 *const self,
        R2_InterfaceID const *const iid, void **const val)
{
    // R2_Result r;
    // r = R2_Interface1_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface1_check_guard(self);
    return self->_vtbl->query_interface_mut(self, iid, val);
}


/////////////////////////////////////////////////////////////////////////////

// an example of dynamic dispatch using ids for properties/actions
// needs re-implementing per interface though because of typed ptr in functon
// calls (and I don't want to remove that.. it's bad enough using void *)

typedef struct R2_PropertyDef_s {
    // use an id instead of array position so I can have gaps in the number
    // range and have a smaller array in the resultant image.
    R2_AttributeID aid;
    R2_Result(*get)(R2_Interface1 const *const self, R2_Value *const ret);
    R2_Result(*set)(R2_Interface1 *const self, R2_Value const *const arg);
} R2_PropertyDef;

typedef struct ActionDef_s {
    R2_ActionID aid;
    R2_Result(*action)(R2_Interface1 *const self, R2_Value const *const arg,
                       R2_Value *const val);
} R2_ActionDef;

static R2_PropertyDef const R2_Interface1_propdefs[] = {
    {1, R2_Interface1_get_value, R2_Interface1_set_value},
};
// TODO: maybe wrap this into a DEFINE_PROPMAP/PROP()/END_PROPMAP macros

//static const ActionDef Interface1_actiondefs[] = {
//};
// TODO: maybe wrap this into a DEFINE_ACTIONMAP/ACTION()/END_ACTIONMAP macros

static R2_Result R2_Interface1_Propdef_lookup(R2_PropertyDef const *begin,
        R2_PropertyDef const *end, R2_AttributeID aid,
        R2_PropertyDef const **const ret)
{
    for (R2_PropertyDef const *it = begin; it != end; ++it) {
        if (it->aid == aid) {
            *ret = it;
            return R2_Result_ok(0);
        }
    }
    return R2_Result_err(R2_Err_InvalidAttributeID);
}

// static Result Interface1_Actiondef_lookup(const ActionDef *begin, const ActionDef *end, AttributeID aid, const ActionDef **ret) {
//     for (const ActionDef *it = begin;it != end; ++it) {
//         if (it->aid == aid) {
//             *ret = it;
//             return Result_ok(0);
//         }
//     }
//     return Result_err(Err_InvalidActionID);
// }

R2_Result R2_Interface1_get(R2_Interface1 const *const self,
                            R2_AttributeID const aid, R2_Value *const ret)
{
    R2_Result r;
    // r = R2_Interface1_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface1_check_guard(self);
    R2_PropertyDef const *def;
    r = R2_Interface1_Propdef_lookup(R2_CARRAY_BEGIN(R2_Interface1_propdefs),
                                     R2_CARRAY_END(R2_Interface1_propdefs), aid, &def);
    R2_RESULT_TRY0(r);
    return def->get(self, ret);
}

R2_Result R2_Interface1_set(R2_Interface1 *const self, R2_AttributeID const aid,
                            R2_Value const *const arg)
{
    R2_Result r;
    // r = R2_Interface1_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface1_check_guard(self);
    R2_PropertyDef const *def;
    r = R2_Interface1_Propdef_lookup(R2_CARRAY_BEGIN(R2_Interface1_propdefs),
                                     R2_CARRAY_END(R2_Interface1_propdefs), aid, &def);
    R2_RESULT_TRY0(r);
    return def->set(self, arg);
}

R2_Result R2_Interface1_action(R2_Interface1 *const self, R2_ActionID const aid,
                               R2_Value const *const arg, R2_Value *const ret)
{
    ((void)aid);
    ((void)arg);
    ((void)ret);
    ((void)self);
    // R2_Result r;
    // r = R2_Interface1_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface1_check_guard(self);
    return R2_Result_err(R2_Err_InvalidActionID);
    //ActionDef const *def;
    //r = R2_Interface1_Actiondef_lookup(R2_CARRAY_BEGIN(Interface1_actiondefs), R2_CARRAY_END(Interface1_actiondefs), aid, &def);
    //R2_RESULT_TRY0(r);
    //return def->action(self, arg, ret);
}

/////////////////////////////////////////////////////////////////////////////

R2_Result R2_Interface1_get_value(R2_Interface1 const *const self,
                                  R2_Value *const ret)
{
    // R2_Result r;
    // r = R2_Interface1_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface1_check_guard(self);
    return self->_vtbl->get_value(self, ret);
}

R2_Result R2_Interface1_set_value(R2_Interface1 *const self,
                                  R2_Value const *const arg)
{
    // R2_Result r;
    // r = R2_Interface1_check_guard(self);
    // R2_RESULT_TRY0(r);
    R2_Interface1_check_guard(self);
    return self->_vtbl->set_value(self, arg);
}
