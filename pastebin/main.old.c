#include "object1.h"
#include "object2.h"
#include "result.h"
#include "interface1.h"
#include "interface2.h"
#include "value.h"

#include <assert.h>


int main(int argc, char *argv[]) {
    ((void)argc);
    ((void)argv);

    Result res;

    Object1 o1 = Object1_new();
    Object2 o2 = Object2_new();

    Interface1 *o1i1;

    res = Object1_query_interface_mut(&o1, &Interface1_ID, (void **)&o1i1);
    assert(Result_is_ok(&res));

    Interface1 const *o2ci1;
    res = Object2_query_interface(&o2, &Interface1_ID, (const void **)&o2ci1);
    assert(Result_is_ok(&res));


    Value value1;
    Value value2;
    // can call mut method on mut interface
    res = Interface1_get_value(o1i1, &value1);
    // can call const method on const interface
    res = Interface1_get_value(o2ci1, &value2);

    value2 = 23465;
    res = Interface1_set(o1i1, 1, &value2);
    res = Interface1_get(o1i1, 1, &value1);
    assert(value1 == value2);

    res = Interface1_action(o1i1, 1, &value1, &value2);
    assert(Result_is_err(&res));

    // cannot get mut interface from const interface
    // hmph, get warning from compilier..
    // Interface2 *o2i2;
    // res = Interface1_query_interface_mut(o2ci1, &Interface2_ID, (void **)&o2i2);
    // assert(Result_is_ok(res));

    // can get const interface from const interface
    Interface2 const *o2ci2;
    res = Interface1_query_interface(o2ci1, &Interface2_ID, (const void **)&o2ci2);
    assert(Result_is_ok(&res));


    Value valuei3 = 2345;
    Value valueo3;
    // cannot call mut method on const interface
    // res = Interface2_set_value(o2ci2, &valuei3);
    // can call const method on const interface
    res = Interface2_get_value(o2ci2, &valueo3);
    assert(valueo3 == valuei3);

    res = Interface2_get_objects(o2ci2, &valueo3);

    // cannot get mut interface from const interface
    // hmph, get warning from compilier..
    //Interface1 *o2i11;
    // res = Interface2_query_interface_mut(o2ci2, &Interface1_ID, (void **)&o2i11);
    // assert(o2i11 == o2ci1);

    Object1_destroy(&o1); // invalidates all ptrs and interfaces to o1
    Object2_destroy(&o2); // invalidates all ptrs and interfaces to o2

    // should be able to call via interface pointers and have it fail without
    // undefined things happening.
    // hmph, get warning from compilier..
    //res = Interface2_query_interface_mut(o2ci2, &Interface1_ID, (void **)&o2i11);
    //assert(Result_is_err(res));
    //res = Interface2_get_value(o2ci2, &valueo3);
    //assert(Result_is_err(res));
    res = Interface1_get_value(o2ci1, &value2);
    assert(Result_is_err(&res));

    return 0;
}
