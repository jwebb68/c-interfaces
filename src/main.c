#include "object1.h"
#include "object2.h"
#include "result.h"
#include "interface1.h"
#include "interface2.h"
#include "value.h"

#include <assert.h>


int main(int argc, char *argv[]) {
    Result res;

    Object1 o1 = Object1_new();
    Object2 o2 = Object2_new();

    Interface1 *o1i1;

    res = Object1_query_interface(&o1, &Interface1_ID, (void **)&o1i1);
    assert(Result_is_ok(res));

    Interface1 *o2i1;
    res = Object2_query_interface(&o2, &Interface1_ID, (void **)&o2i1);
    assert(Result_is_ok(res));


    Value value1;
    Value value2;
    res = Interface1_get_value(o1i1, &value1);
    res = Interface1_get_value(o2i1, &value2);

    value2 = 23465;
    res = Interface1_set(o1i1, 1, &value2);
    res = Interface1_get(o1i1, 1, &value1);
    assert(value1 == value2);

    res = Interface1_action(o1i1, 1, &value1, &value2);
    assert(Result_is_err(res));

    Interface2 *o2i2;
    res = Interface1_query_interface(o2i1, &Interface2_ID, (void **)&o2i2);
    assert(Result_is_ok(res));

    Value valuei3 = 2345;
    Value valueo3;
    res = Interface2_set_value(o2i2, &valuei3);
    res = Interface2_get_value(o2i2, &valueo3);
    assert(valueo3 == valuei3);

    res = Interface2_get_objects(o2i2, &valueo3);

    Interface1 *o2i11;
    res = Interface2_query_interface(o2i2, &Interface1_ID, (void **)&o2i11);
    assert(o2i11 == o2i1);

    Object1_destroy(&o1); // invalidates all ptrs and interfaces to o1
    Object2_destroy(&o2); // invalidates all ptrs and interfaces to o2

    // should be able to call via interface pointers and have it fail without
    // undefined things happening.
    res = Interface2_query_interface(o2i2, &Interface1_ID, (void **)&o2i11);
    assert(Result_is_err(res));
    res = Interface2_get_value(o2i2, &valueo3);
    assert(Result_is_err(res));
    res = Interface1_get_value(o2i1, &value2);
    assert(Result_is_err(res));

    return 0;
}
