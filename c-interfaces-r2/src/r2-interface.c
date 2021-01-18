#include "r2-interface.h"
#include "r2-panic.h"

// R2_Result R2_Interface_check_guard(R2_InterfaceID const *const expected, R2_InterfaceID const *const actual) {
//     if (expected == actual) {
//         return R2_Result_ok(0);
//     }
//     return R2_Result_err(R2_Err_InvalidInterface);
// }

void R2_Interface_check_guard(R2_InterfaceID const *const expected,
                              R2_InterfaceID const *const actual)
{
    if (expected != actual) {
        R2_PANIC("broken_interface");
    }
}

R2_Result R2_Interface_query_interface(void const *inst,
                                       R2_InterfaceID const *iid, void const **ret, R2_InterfaceLookup const *begin,
                                       R2_InterfaceLookup const *end)
{
    for (R2_InterfaceLookup const *it = begin; it != end; ++it) {
        if (it->iid == iid) {
            // nasty hobbitses, casting away type.
            // but how else to get it generic in C..
            // also nastiness, adjusting pointers by bytes.
            *ret = (void const *)((uint8_t const *)inst + it->offset);
            return R2_Result_ok(0);
        }
    }
    return R2_Result_err(R2_Err_InvalidInterfaceID);
}

R2_Result R2_Interface_query_interface_mut(void *inst,
        R2_InterfaceID const *iid, void **ret, R2_InterfaceLookup const *begin,
        R2_InterfaceLookup const *end)
{
    for (R2_InterfaceLookup const *it = begin; it != end; ++it) {
        if (it->iid == iid) {
            // nasty hobbitses, casting away type.
            // but how else to get it generic in C..
            // also nastiness, adjusting pointers by bytes.
            *ret = (void *)((uint8_t *)inst + it->offset);
            return R2_Result_ok(0);
        }
    }
    return R2_Result_err(R2_Err_InvalidInterfaceID);
}
