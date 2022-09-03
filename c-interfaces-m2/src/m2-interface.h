#ifndef M2_INTERFACE_H
#define M2_INTERFACE_H


typedef struct M2_InterfaceLookup_s M2_InterfaceLookup;
struct M2_InterfaceLookup_s;


#include "m2-result.h"
#include "m2-panic.h"

#include <inttypes.h>
#include <stddef.h>


// maybe use a uuid, then fixed size regardless
// but need some sort of reg to map uuid to string name.
typedef char const *M2_InterfaceID;

typedef uint8_t M2_AttributeID;
typedef uint8_t M2_ActionID;


// compare two pointers for equality, panic if not equal
// assert(expected == actual)..
void M2_Interface_try_check(void const *const expected,
                            void const *const actual, M2_Result *const ret);


#if 0
void M2_Interface_check_guard_(char const *file, size_t line,
                               void const *const expected,
                               void const *const actual);
#define M2_Interface_check_guard(expected, actual) \
    M2_Interface_check_guard(__FILE__, __LINE__, expected, actual)
#else
// if check_guard is a function, gcc isn't inlining it.. and don't know why.
// using a macro gets it inlined
#define M2_Interface_check_(file, line, expected, actual) do{if((expected)!=(actual)){M2_panic_(file, line, "Bad Interface");}}while(0);
#endif


struct M2_InterfaceLookup_s {
    M2_InterfaceID const *iid;
    size_t offset;
};


void M2_Interface_query_interface(void const *inst,
                                  M2_InterfaceID const *const iid,
                                  void const **const val,
                                  M2_Result *const ret,
                                  M2_InterfaceLookup const *begin,
                                  M2_InterfaceLookup const *end);


void M2_Interface_query_interface_mut(void *inst,
                                      M2_InterfaceID const *const iid,
                                      void **const val,
                                      M2_Result *const ret,
                                      M2_InterfaceLookup const *begin,
                                      M2_InterfaceLookup const *end);


#define M2_INTERFACE_GET_OBJPTR(objtype, ifaceptr) ((objtype const *)((uint8_t const *)ifaceptr - ifaceptr->_vtbl->offset))


#define M2_INTERFACE_GET_OBJPTR_MUT(objtype, ifaceptr) ((objtype *)((uint8_t *)ifaceptr - ifaceptr->_vtbl->offset))

#if 0
#define FDECL_INTERFACE(iname) \
    typedef struct ##iname_VTBL_s ##iname_VTBL; \
    typedef struct ##iname_s ##iname

#define DEF_INTERFACE(iname) \
    struct ##iname_s { \
        ##iname_VTBL const * const _vtbl; \
    }; \
    extern InterfaceID const * const ##iname_iid;
struct ##iname_VTBL_s {
    \
##iname_VTBL const * const token; \
        size_t adj;

#define ENDDEF_INTERFACE }

#define IMPL_INTERFACE(iname) \
    InterfaceID const ##iname_iid = "##iname"


#define DECL_INTERFACE_FOR(iname, sname) \
    ##iname _##iname

#define IMPL_INTERFACE_FOR(iname, sname) \
    static ##iname_VTBL const ##iname = { \
                                          .token = &##iname,
    .adj = offsetof(sname, _##iname),

#define ENDIMPL_INTERFACE }

#define IMPL_INTERFACE_MAP_FOR(sname) \
    static InterfaceEntry const ##sname_ifacemap[] = {

#define INTERFACE_ENTRY_FOR(iid, iname) \
    {iid, offsetof(sname, _##iname)},

#define END_INTERFACE_MAP_FOR };
#endif

#endif// M2_INTERFACE_H
