#include "m2-result.h"

#include "m2-panic.h"

#include <assert.h>


void M2_ResultErr_destroy(M2_ResultErr *const self)
{
    ((void)self);
}


void M2_ResultErr_move(M2_ResultErr *const self, M2_ResultErr *const src)
{
    *self = *src;
}


void M2_ResultErr_new(M2_ResultErr *const self, char const *file, size_t line,
                      M2_ResultErrType code)
{
    ((void)file);
    ((void)line);
    self->code = code;
#if defined(M2_RESULTERR_INSTRUMENTED)
    self->file = file;
    self->line = line;
#endif//
}


#if M2_RESULT == 'I'

void M2_Result_destroy(M2_Result *const self)
{
    ((void)self);
}

void M2_Result_ok(M2_Result *const self, M2_ResultOk val)
{
    assert(val >= 0);
    *self = val;
}

void M2_Result_err(M2_Result *const self, M2_ResultErr val)
{
    assert(val > 0);
    *self = -val;
}

bool M2_Result_is_ok(M2_Result const *const self)
{
    return *self >= 0;
}

bool M2_Result_is_err(M2_Result const *const self)
{
    return *self < 0;
}

M2_ResultOk M2_Result_unwrap(M2_Result *const self)
{
    if (M2_Result_is_ok(self)) {
        return *self;
    }
    M2_PANIC("not ok");
}

M2_ResultErr M2_Result_unwrap_err(M2_Result *const self)
{
    if (M2_Result_is_err(self)) {
        return -*self;
    }
    M2_PANIC("not err");
}

bool M2_Result_try(M2_Result *const self)
{
    bool const is_ok = M2_Result_is_ok(self);
    return is_ok;
}

bool M2_Result_try_unwrap(M2_Result *const self, M2_ResultOk *const okv)
{
    bool const is_ok = M2_Result_is_ok(self);
    if (is_ok) {
        *okv = *self;
    }
    return is_ok;
}


#elif M2_RESULT == 'S'

void M2_Result_destroy(M2_Result *const self)
{
    ((void)self);
}


void M2_Result_ok(M2_Result *const self, M2_ResultOk val)
{
    self->type = M2_Result_OK;
    self->u.ok = val;
}


void M2_Result_err_(M2_Result *const self, char const *file, size_t line,
                    M2_ResultErrType val)
{
    self->type = M2_Result_ERR;
    M2_ResultErr_new(&self->u.err, file, line, val);
}


bool M2_Result_is_ok(M2_Result const *const self)
{
    return self->type == M2_Result_OK;
}


bool M2_Result_is_err(M2_Result const *const self)
{
    return self->type == M2_Result_ERR;
}


M2_ResultOk M2_Result_unwrap(M2_Result *const self)
{
    if (M2_Result_is_ok(self)) {
        // move
        return self->u.ok;
    }
    M2_PANIC("not ok");

    // if (!M2_Result_is_ok(self)) {
    //     M2_PANIC("not ok");
    // }
    // return self->u.ok;
}


M2_ResultErr M2_Result_unwrap_err(M2_Result *const self)
{
    if (!M2_Result_is_err(self)) {
        M2_PANIC("not err");
    }
    M2_ResultErr err;
    M2_ResultErr_move(&err, &self->u.err);
    return err;
}


bool M2_Result_try(M2_Result *const self)
{
    bool const is_ok = M2_Result_is_ok(self);
    return is_ok;
}


bool M2_Result_try_unwrap(M2_Result *const self, M2_ResultOk *const okv)
{
    bool const is_ok = M2_Result_is_ok(self);
    // this is quicker/smaller by 1 instruction, in both paths.
    if (is_ok) {
        *okv = self->u.ok; // really, M2_ResultOk_move()..
        return true;
    }
    return false;

    // than this. so up yours misra
#if 0
    if (is_ok) {
        *okv = self->u.ok; // really, M2_ResultOk_move()..
    } else {
        // res.u.ok must be destroyed mere
    }
    return is_ok;
#endif
}

#else//
#error must have supported result implementation
#endif//
