#ifndef R2_INTERFACE_H
#define R2_INTERFACE_H

typedef struct _R2_InterfaceLookup R2_InterfaceLookup;
struct _R2_InterfaceLookup;

#include "r2-result.h"

#include <inttypes.h>
#include <stddef.h>

typedef const char *R2_InterfaceID;

typedef uint8_t R2_AttributeID;
typedef uint8_t R2_ActionID;

//R2_Result R2_Interface_check_guard(R2_InterfaceID const *const expected, R2_InterfaceID const *const actual);
void R2_Interface_check_guard(R2_InterfaceID const *const expected,
                              R2_InterfaceID const *const actual);

struct _R2_InterfaceLookup {
    R2_InterfaceID const *iid;
    size_t offset;
};
R2_Result R2_Interface_query_interface(void const *inst,
                                       R2_InterfaceID const *const iid, void const **const ret,
                                       R2_InterfaceLookup const *begin, R2_InterfaceLookup const *end);
R2_Result R2_Interface_query_interface_mut(void *inst,
        R2_InterfaceID const *const iid, void **const ret,
        R2_InterfaceLookup const *begin, R2_InterfaceLookup const *end);

#define R2_INTERFACE_GET_OBJPTR(objtype, ifaceptr) ((objtype const *)((uint8_t const *)ifaceptr - ifaceptr->_vtbl->offset))

#define R2_INTERFACE_GET_OBJPTR_MUT(objtype, ifaceptr) ((objtype *)((uint8_t *)ifaceptr - ifaceptr->_vtbl->offset))


#endif// R2_INTERFACE_H
