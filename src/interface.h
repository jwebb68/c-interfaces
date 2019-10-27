#ifndef INTERFACE_H
#define INTERFACE_H

typedef struct _InterfaceLookup InterfaceLookup;
struct _InterfaceLookup;

#include "result.h"

#include <inttypes.h>
#include <stddef.h>

typedef const char * InterfaceID;

typedef uint8_t AttributeID;
typedef uint8_t ActionID;

Result Interface_check_guard(const InterfaceID *expected, const InterfaceID *actual);

Result Interface_query_interface(const InterfaceLookup *begin, const InterfaceLookup *end, const void *inst, const InterfaceID *iid, void **ret);


struct _InterfaceLookup {
    const InterfaceID *iid;
    size_t offset;
};


#endif// INTERFACE_H
