#include "m2-object1.h"
#include "m2-result.h"
#include "m2-interface1.h"
#include "m2-interface3.h"
#include "m2-value.h"

#include <assert.h>


void foo(M2_Object1 const *const o)
{
    M2_Result res;

    M2_Interface3 const *const ci3;
    M2_Object1_query_interface(o, &M2_Interface3_ID, (void const **)&ci3, &res);
    M2_Result_unwrap(&res);

    M2_Value value1;
    // can call const method on const interface
    M2_Interface3_get_value1(ci3, &value1, &res);
    M2_Result_unwrap(&res);

    // interfaces do not need to be destroyed.
}

void foo_mut(M2_Object1 *const o)
{
    M2_Result res;

    M2_Interface3 const *const ci3;
    M2_Object1_query_interface(o, &M2_Interface3_ID, (void const **)&ci3, &res);
    M2_Result_unwrap(&res);

    M2_Interface3 *const mi3;
    M2_Object1_query_interface_mut(o, &M2_Interface3_ID, (void  **)&mi3, &res);
    M2_Result_unwrap(&res);

    M2_Value value1;
    // can call const method on mut interface
    M2_Interface3_get_value1(ci3, &value1, &res);
    M2_Result_unwrap(&res);

    M2_Value value2 = value1;
    // can call mut method on mut interface
    M2_Interface3_set_value1(mi3, &value2, &res);
    M2_Result_unwrap(&res);

    M2_Value value3;
    // can call const method on mut interface
    M2_Interface3_get_value1(ci3, &value3, &res);
    M2_Result_unwrap(&res);
    assert(value3 == value2);

    // interfaces do not need to be destroyed.
}

int main(int argc, char *argv[]) {
    ((void)argc);
    ((void)argv);

    M2_Result res;

    M2_Object1 o1;
    M2_Object1_new(&o1);

    M2_Interface1 *const o1i1;
    M2_Object1_query_interface_mut(&o1, &M2_Interface1_ID, (void **)&o1i1, &res);
    M2_Result_unwrap(&res);

    foo(&o1);
    foo_mut(&o1);

    M2_Object1_destroy(&o1); // invalidates all ptrs and interfaces to o1

    return 0;
}
