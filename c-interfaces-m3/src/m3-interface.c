#include "m3-interface.h"
//#include "m3-panic.h"


void M3_Interface_try_check(
    M3_Result *const ret,
    void const *const expected,
    void const *const actual
)
{
    if (expected == actual) {
        M3_Result_ok(ret, 0);
    } else {
        M3_Result_err(ret, M3_Err_InvalidInterface);
    }
}


#if 0
void M3_Interface_check_(char const *file, size_t line,
                         void const *const expected, void const *const actual)
{
    if (expected == actual) {
        return;
    }
    M3_panic_(file, line, "broken interface");
}
#endif


void M3_Interface_query_interface(M3_Result *const ret,
                                  void const *inst,
                                  M3_InterfaceID const *const iid,
                                  void const **val,
                                  M3_InterfaceLookup const *begin,
                                  M3_InterfaceLookup const *end)
{
    for (M3_InterfaceLookup const *it = begin; it != end; ++it) {
        if (it->iid == iid) {
            // nasty, casting away type.
            // but how else to get it generic in C..
            // also nastiness, adjusting pointers by bytes.
            *val = (void const *)((uint8_t const *)inst + it->offset);
            M3_Result_ok(ret, 0);
            return;
        }
    }
    M3_Result_err(ret, M3_Err_InvalidInterfaceID);
}


void M3_Interface_query_interface_mut(M3_Result *const ret,
                                      void *inst,
                                      M3_InterfaceID const *const iid,
                                      void **val,
                                      M3_InterfaceLookup const *begin,
                                      M3_InterfaceLookup const *end)
{
    for (M3_InterfaceLookup const *it = begin; it != end; ++it) {
        if (it->iid == iid) {
            // nasty, casting away type.
            // but how else to get it generic in C..
            // also nastiness, adjusting pointers by bytes.
            *val = (void *)((uint8_t *)inst + it->offset);
            M3_Result_ok(ret, 0);
            return;
        }
    }
    M3_Result_err(ret, M3_Err_InvalidInterfaceID);
}
