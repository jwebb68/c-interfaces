#include "m2-object1.h"
#include "m2-result.h"
#include "m2-interface1.h"
#include "m2-value.h"

#include <assert.h>


int main(int argc, char *argv[]) {
    ((void)argc);
    ((void)argv);

    M2_Result res;

    M2_Object1 o1;
    M2_Object1_new(&o1);

    M2_Interface1 *const o1i1;
    M2_Object1_query_interface_mut(&o1, &M2_Interface1_ID, (void **)&o1i1, &res);
    M2_Result_unwrap(&res);


    M2_Interface1 const *const o2ci1;
    M2_Object1_query_interface(&o1, &M2_Interface1_ID, (void const **)&o2ci1, &res);
    M2_Result_unwrap(&res);

    M2_Value value1;
    M2_Value value2;
    // can call mut method on mut interface
    M2_Interface1_get_value(o1i1, &value1, &res);
    M2_Result_unwrap(&res);
    // can call const method on const interface
    M2_Interface1_get_value(o2ci1, &value2, &res);
    M2_Result_unwrap(&res);

    M2_Object1_destroy(&o1); // invalidates all ptrs and interfaces to o1

    return 0;
}
