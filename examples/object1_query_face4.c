#include "m4-object1.h"
#include "m4-result.h"
#include "m4-interface1.h"
#include "m4-value.h"

#include <assert.h>


int main(int argc, char *argv[]) {
    ((void)argc);
    ((void)argv);

    M4_Result res;

    M4_Object1 o1;
    M4_Object1_new(&o1);

    M4_Interface1 *o1i1;
    M4_Object1_query_interface_mut(&o1, &res, &M4_Interface1_ID, (void **)&o1i1);
    M4_Result_unwrap(&res);

    M4_Object1_destroy(&o1); // invalidates all ptrs and interfaces to o1

    return 0;
}
