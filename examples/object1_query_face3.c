#include "m3-object1.h"
#include "m3-result.h"
#include "m3-interface1.h"
#include "m3-value.h"

#include <assert.h>


int main(int argc, char *argv[]) {
    ((void)argc);
    ((void)argv);

    M3_Result res;

    M3_Object1 o1;
    M3_Object1_new(&o1);

    M3_Interface1 *o1i1;
    M3_Object1_query_interface_mut(&res, &o1, &M3_Interface1_ID, (void **)&o1i1);
    M3_Result_unwrap(&res);

    M3_Object1_destroy(&o1); // invalidates all ptrs and interfaces to o1

    return 0;
}
