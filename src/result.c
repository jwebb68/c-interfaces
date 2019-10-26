#include "result.h"
#include <assert.h>

void panic(const char *reason) {
    assert(false);
}
Result Result_ok(Result_Ok val) {
    assert(val >= 0);
    return val;
}
Result Result_err(Result_Err val) {
    assert(val > 0);
    return -val;
}
bool Result_is_ok(Result res) {
    return res >= 0;
}
bool Result_is_err(Result res) {
    return res < 0;
}
Result_Ok Result_unwrap(Result res) {
    if (Result_is_ok(res)) return res;
    panic("not ok");
}
Result_Err Result_unwrap_err(Result res) {
    if (Result_is_err(res)) return -res;
    panic("not err");
}
