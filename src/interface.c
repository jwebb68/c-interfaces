#include "interface.h"

Result Interface_check_guard(const InterfaceID *expected, const InterfaceID *actual) {
    if (expected == actual) return Result_ok(0);
    return Result_err(Err_InvalidInterface);
}

Result Interface_query_interface(const InterfaceLookup *begin, const InterfaceLookup *end, const void *inst, const InterfaceID *iid, void **ret) {
    for (const InterfaceLookup *it = begin; it != end; ++it) {
        if (it->iid == iid) {
            // nasty hobbitses, casting away const and type.
            // but how else to get it generic in C..
            // also nastiness, adjusting pointers by bytes.
            *ret = (void *)((const uint8_t *)inst + it->offset);
            return Result_ok(0);
        }
    }
    return Result_err(Err_InvalidInterfaceID);
}
