#include "result.h"
#include <assert.h>

void panic(const char *reason) {
    assert(false);
}

#if RESULT == 'I'

Result Result_ok(ResultOk val) {
    assert(val >= 0);
    return val;
}

Result Result_err(ResultErr val) {
    assert(val > 0);
    return -val;
}

bool Result_is_ok(Result res) {
    return res >= 0;
}

bool Result_is_err(Result res) {
    return res < 0;
}

ResultOk Result_unwrap(Result res) {
    if (Result_is_ok(res)) return res;
    panic("not ok");
}

ResultErr Result_unwrap_err(Result res) {
    if (Result_is_err(res)) return -res;
    panic("not err");
}

#elif RESULT == 'S'

Result Result_ok(ResultOk val) {
    Result res = {.type=Result_OK, .ok=val};
    return res;
}

Result Result_err(ResultErr val) {
    Result res = {.type=Result_ERR, .err=val};
    return res;
}

bool Result_is_ok(Result res) {
    return res.type == Result_OK;
}

bool Result_is_err(Result res) {
    return res.type == Result_ERR;
}

ResultOk Result_unwrap(Result res) {
    if (Result_is_ok(res)) return res.ok;
    panic("not ok");
}

ResultErr Result_unwrap_err(Result res) {
    if (Result_is_err(res)) return res.err;
    panic("not err");
}

#else//
#error must have supported result implementation
#endif//
