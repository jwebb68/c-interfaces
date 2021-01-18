#include "r2-object1.h"
#include "r2-result.h"
#include "r2-interface1.h"
#include "r2-value.h"

#include <assert.h>


int main(int argc, char *argv[]) {
    ((void)argc);
    ((void)argv);

    R2_Result res;

    R2_Object1 o1 = R2_Object1_new();

    R2_Interface1 *const o1i1;
    res = R2_Object1_query_interface_mut(&o1, &R2_Interface1_ID, (void **)&o1i1);
    R2_Result_unwrap(&res);

    R2_Interface1 const *const o2ci1;
    res = R2_Object1_query_interface(&o1, &R2_Interface1_ID, (void const **)&o2ci1);
    R2_Result_unwrap(&res);

    R2_Value value1;
    R2_Value value2;
    // can call mut method on mut interface
    res = R2_Interface1_get_value(o1i1, &value1);
    R2_Result_unwrap(&res);

    // can call const method on const interface
    res = R2_Interface1_get_value(o2ci1, &value2);
    R2_Result_unwrap(&res);

    R2_Object1_destroy(&o1); // invalidates all ptrs and interfaces to o1

    return 0;
}
