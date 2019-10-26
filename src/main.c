#include "object1.h"
#include "result.h"
#include "interface1.h"
#include "interface2.h"
#include "value.h"

#include <assert.h>


int main(int argc, char *argv[]) {
    Result res;

    Object1 o = Object1_new();

    Interface1 *oi1;

    res = Object1_query_interface(&o, &Interface1_ID, (void **)&oi1);
    assert(Result_is_ok(res));

    Value value1;
    res = Interface1_get_value(oi1, &value1);

    Interface2 *oi2;
    res = Interface1_query_interface(oi1, &Interface2_ID, (void **)&oi2);
    assert(Result_is_ok(res));

    Value value2;
    res = Interface2_get_value(oi2, &value2);
    res = Interface2_get_objects(oi2, &value2);

    Interface1 *oi3;
    res = Interface2_query_interface(oi2, &Interface1_ID, (void **)&oi3);
    assert(oi3 == oi1);

    Object1_destroy(&o); // invalidates all ptrs and interfaces to o

    // and can use same Interface ptrs for Object2, if it supports the interface.

    return 0;
}
