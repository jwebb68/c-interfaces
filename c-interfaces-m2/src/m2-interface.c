#include "m2-interface.h"
//#include "m2-panic.h"


void M2_Interface_try_check(void const *const expected,
                            void const *const actual,
                            M2_Result *const ret
                           )
{
    if (expected == actual) {
        M2_Result_ok(ret, 0);
    } else {
        M2_Result_err(ret, M2_Err_InvalidInterface);
    }
}


#if 0
void M2_Interface_check_(char const *file, size_t line,
                         void const *const expected, void const *const actual)
{
    if (expected == actual) {
        return;
    }
    M2_panic_(file, line, "broken interface");
}
#endif


void M2_Interface_query_interface(void const *inst,
                                  M2_InterfaceID const *const iid,
                                  void const **val,
                                  M2_Result *const ret,
                                  M2_InterfaceLookup const *begin,
                                  M2_InterfaceLookup const *end)
{
    for (M2_InterfaceLookup const *it = begin; it != end; ++it) {
        if (it->iid == iid) {
            // nasty, casting away type.
            // but how else to get it generic in C..
            // also nastiness, adjusting pointers by bytes.
            *val = (void const *)((uint8_t const *)inst + it->offset);
            M2_Result_ok(ret, 0);
            return;
        }
    }
    M2_Result_err(ret, M2_Err_InvalidInterfaceID);
}


void M2_Interface_query_interface_mut(void *inst,
                                      M2_InterfaceID const *const iid,
                                      void **val,
                                      M2_Result *const ret,
                                      M2_InterfaceLookup const *begin,
                                      M2_InterfaceLookup const *end)
{
    for (M2_InterfaceLookup const *it = begin; it != end; ++it) {
        if (it->iid == iid) {
            // nasty, casting away type.
            // but how else to get it generic in C..
            // also nastiness, adjusting pointers by bytes.
            *val = (void *)((uint8_t *)inst + it->offset);
            M2_Result_ok(ret, 0);
            return;
        }
    }
    M2_Result_err(ret, M2_Err_InvalidInterfaceID);
}
