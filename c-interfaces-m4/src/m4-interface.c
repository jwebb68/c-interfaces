#include "m4-interface.h"
//#include "m4-panic.h"


void M4_Interface_try_check(
    M4_Result *const ret,
    void const *const expected,
    void const *const actual
)
{
    if (expected == actual) {
        M4_Result_ok(ret, 0);
    } else {
        M4_Result_err(ret, M4_Err_InvalidInterface);
    }
}


#if 0
void M4_Interface_check_(char const *file, size_t line,
                         void const *const expected, void const *const actual)
{
    if (expected == actual) {
        return;
    }
    M4_panic_(file, line, "broken interface");
}
#endif


void M4_Interface_query_interface(
    void const *inst,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void const **val,
    M4_InterfaceLookup const *begin,
    M4_InterfaceLookup const *end)
{
    for (M4_InterfaceLookup const *it = begin; it != end; ++it) {
        if (it->iid == iid) {
            // nasty, casting away type.
            // but how else to get it generic in C..
            // also nastiness, adjusting pointers by bytes.
            *val = (void const *)((uint8_t const *)inst + it->offset);
            M4_Result_ok(ret, 0);
            return;
        }
    }
    M4_Result_err(ret, M4_Err_InvalidInterfaceID);
}


void M4_Interface_query_interface_mut(
    void *inst,
    M4_Result *const ret,
    M4_InterfaceID const *const iid,
    void **val,
    M4_InterfaceLookup const *begin,
    M4_InterfaceLookup const *end)
{
    for (M4_InterfaceLookup const *it = begin; it != end; ++it) {
        if (it->iid == iid) {
            // nasty, casting away type.
            // but how else to get it generic in C..
            // also nastiness, adjusting pointers by bytes.
            *val = (void *)((uint8_t *)inst + it->offset);
            M4_Result_ok(ret, 0);
            return;
        }
    }
    M4_Result_err(ret, M4_Err_InvalidInterfaceID);
}
