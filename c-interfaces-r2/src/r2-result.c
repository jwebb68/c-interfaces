#include "r2-result.h"
#include "r2-panic.h"

#include <assert.h>


void R2_ResultErr_destroy(R2_ResultErr *const self)
{
    ((void)self);
}
void R2_ResultErr_move(R2_ResultErr *const self, R2_ResultErr *const src)
{
    *self = *src;
}
R2_ResultErr R2_ResultErr_new(char const *file, size_t line,
                              R2_ResultErrType code)
{
    ((void)file);
    ((void)line);
    R2_ResultErr inst = {
        .code = code,
#if defined(R2_RESULTERR_INSTRUMENTED)
        .file = file,
        .line = line,
#endif
    };
    return inst;
}


#if R2_RESULT == 'I'

void R2_Result_destroy(R2_Result self)
{
}

R2_Result R2_Result_ok(R2_ResultOk val)
{
    assert(val >= 0);
    return val;
}

R2_Result R2_Result_err(R2_ResultErr val)
{
    assert(val > 0);
    return -val;
}

bool R2_Result_is_ok(R2_Result const *const self)
{
    return *self >= 0;
}

bool R2_Result_is_err(R2_Result const *const self)
{
    return *self < 0;
}

R2_ResultOk R2_Result_unwrap(R2_Result *const self)
{
    if (R2_Result_is_ok(self)) {
        return *self;
    }
    R2_PANIC("not ok");
}

R2_ResultErr R2_Result_unwrap_err(R2_Result *const self)
{
    if (R2_Result_is_err(self)) {
        return -*self;
    }
    R2_PANIC("not err");
}

bool R2_Result_try(R2_Result *const self)
{
    bool const is_ok = R2_Result_is_ok(self);
    return is_ok;
}

bool R2_Result_try_unwrap(R2_Result *const self, R2_ResultOk *const okv)
{
    bool const is_ok = R2_Result_is_ok(self);
    if (is_ok) {
        *okv = *self;
    }
    return is_ok;
}

#elif R2_RESULT == 'S'

void R2_Result_destroy(R2_Result *const self)
{
    ((void)self);
}

R2_Result R2_Result_ok(R2_ResultOk val)
{
    //Result res = {.type=Result_OK, .u={.ok=val}};
    R2_Result res;
    res.type = R2_Result_OK;
    res.u.ok = val;
    return res;
}

R2_Result R2_Result_err_(char const *file, size_t line, R2_ResultErrType val)
{
    //Result res = {.type=Result_ERR, .u={.err=val}};
    R2_Result res = {
        .type = R2_Result_ERR,
        .u = {
            .err = R2_ResultErr_new(file, line, val),
        },
    };
    return res;
}


bool R2_Result_is_ok(R2_Result const *const self)
{
    return self->type == R2_Result_OK;
}

bool R2_Result_is_err(R2_Result const *const self)
{
    return self->type == R2_Result_ERR;
}

R2_ResultOk R2_Result_unwrap(R2_Result *const self)
{
    if (R2_Result_is_ok(self)) {
        // move
        return self->u.ok;
    }
    R2_PANIC("not ok");
}

R2_ResultErr R2_Result_unwrap_err(R2_Result *const self)
{
    if (R2_Result_is_err(self)) {
        R2_ResultErr err;
        R2_ResultErr_move(&err, &self->u.err);
        return err;
    }
    R2_PANIC("not err");
}

bool R2_Result_try(R2_Result *const self)
{
    bool const is_ok = R2_Result_is_ok(self);
    return is_ok;
}

bool R2_Result_try_unwrap(R2_Result *const self, R2_ResultOk *const okv)
{
    bool const is_ok = R2_Result_is_ok(self);
    // this is quicker by 1 instruction, in both paths.
    // than
    // if (is_ok) {
    //     *okv = self->u.ok; // really, R2_ResultOk_move()..
    // } else {
    //     // res.u.ok must be destroyed mere
    // }
    // return is_ok;
    if (is_ok) {
        *okv = self->u.ok; // really, R2_ResultOk_move()..
        return true;
    }
    return false;
}

#else//
#error must have supported R2_result implementation
#endif//
