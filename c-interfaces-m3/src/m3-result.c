#include "m3-result.h"

#include "m3-panic.h"

#include <assert.h>


void M3_ResultErr_destroy(M3_ResultErr *const self)
{
    ((void)self);
}


void M3_ResultErr_move(M3_ResultErr *const self, M3_ResultErr *const src)
{
    *self = *src;
}


void M3_ResultErr_new(M3_ResultErr *const self, char const *file, size_t line,
                      M3_ResultErrType code)
{
    ((void)file);
    ((void)line);
    self->code = code;
#if defined(M3_RESULTERR_INSTRUMENTED)
    self->file = file;
    self->line = line;
#endif//
}


#if M3_RESULT == 'I'

void M3_Result_destroy(M3_Result *const self)
{
    ((void)self);
}

void M3_Result_ok(M3_Result *const self, M3_ResultOk val)
{
    assert(val >= 0);
    *self = val;
}

void M3_Result_err(M3_Result *const self, M3_ResultErr val)
{
    assert(val > 0);
    *self = -val;
}

bool M3_Result_is_ok(M3_Result const *const self)
{
    return *self >= 0;
}

bool M3_Result_is_err(M3_Result const *const self)
{
    return *self < 0;
}

M3_ResultOk M3_Result_unwrap(M3_Result *const self)
{
    if (M3_Result_is_ok(self)) {
        return *self;
    }
    M3_PANIC("not ok");
}

M3_ResultErr M3_Result_unwrap_err(M3_Result *const self)
{
    if (M3_Result_is_err(self)) {
        return -*self;
    }
    M3_PANIC("not err");
}

bool M3_Result_try(M3_Result *const self)
{
    bool const is_ok = M3_Result_is_ok(self);
    return is_ok;
}

bool M3_Result_try_unwrap(M3_Result *const self, M3_ResultOk *const okv)
{
    bool const is_ok = M3_Result_is_ok(self);
    if (is_ok) {
        *okv = *self;
    }
    return is_ok;
}


#elif M3_RESULT == 'S'

void M3_Result_destroy(M3_Result *const self)
{
    ((void)self);
}


void M3_Result_ok(M3_Result *const self, M3_ResultOk val)
{
    self->type = M3_Result_OK;
    self->u.ok = val;
}


void M3_Result_err_(M3_Result *const self, char const *file, size_t line,
                    M3_ResultErrType val)
{
    self->type = M3_Result_ERR;
    M3_ResultErr_new(&self->u.err, file, line, val);
}


bool M3_Result_is_ok(M3_Result const *const self)
{
    return self->type == M3_Result_OK;
}


bool M3_Result_is_err(M3_Result const *const self)
{
    return self->type == M3_Result_ERR;
}


M3_ResultOk M3_Result_unwrap(M3_Result *const self)
{
    if (M3_Result_is_ok(self)) {
        // move
        return self->u.ok;
    }
    M3_PANIC("not ok");

    // if (!M3_Result_is_ok(self)) {
    //     M3_PANIC("not ok");
    // }
    // return self->u.ok;
}


M3_ResultErr M3_Result_unwrap_err(M3_Result *const self)
{
    if (!M3_Result_is_err(self)) {
        M3_PANIC("not err");
    }
    M3_ResultErr err;
    M3_ResultErr_move(&err, &self->u.err);
    return err;
}


bool M3_Result_try(M3_Result *const self)
{
    bool const is_ok = M3_Result_is_ok(self);
    return is_ok;
}


bool M3_Result_try_unwrap(M3_Result *const self, M3_ResultOk *const okv)
{
    bool const is_ok = M3_Result_is_ok(self);
    // this is quicker/smaller by 1 instruction, in both paths.
    if (is_ok) {
        *okv = self->u.ok; // really, M3_ResultOk_move()..
        return true;
    }
    return false;

    // than this. so up yours misra
#if 0
    if (is_ok) {
        *okv = self->u.ok; // really, M3_ResultOk_move()..
    } else {
        // res.u.ok must be destroyed mere
    }
    return is_ok;
#endif
}

#else//
#error must have supported result implementation
#endif//
