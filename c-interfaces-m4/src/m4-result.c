#include "m4-result.h"

#include "m4-panic.h"

#include <assert.h>


void M4_ResultErr_destroy(M4_ResultErr *const self)
{
    ((void)self);
}


void M4_ResultErr_move(M4_ResultErr *const self, M4_ResultErr *const src)
{
    *self = *src;
}


void M4_ResultErr_new(M4_ResultErr *const self, char const *file, size_t line,
                      M4_ResultErrType code)
{
    ((void)file);
    ((void)line);
    self->code = code;
#if defined(M4_RESULTERR_INSTRUMENTED)
    self->file = file;
    self->line = line;
#endif//
}


#if M4_RESULT == 'I'

void M4_Result_destroy(M4_Result *const self)
{
    ((void)self);
}

void M4_Result_ok(M4_Result *const self, M4_ResultOk val)
{
    assert(val >= 0);
    *self = val;
}

void M4_Result_err(M4_Result *const self, M4_ResultErr val)
{
    assert(val > 0);
    *self = -val;
}

bool M4_Result_is_ok(M4_Result const *const self)
{
    return *self >= 0;
}

bool M4_Result_is_err(M4_Result const *const self)
{
    return *self < 0;
}

M4_ResultOk M4_Result_unwrap(M4_Result *const self)
{
    if (M4_Result_is_ok(self)) {
        return *self;
    }
    M4_PANIC("not ok");
}

M4_ResultErr M4_Result_unwrap_err(M4_Result *const self)
{
    if (M4_Result_is_err(self)) {
        return -*self;
    }
    M4_PANIC("not err");
}

bool M4_Result_try(M4_Result *const self)
{
    bool const is_ok = M4_Result_is_ok(self);
    return is_ok;
}

bool M4_Result_try_unwrap(M4_Result *const self, M4_ResultOk *const okv)
{
    bool const is_ok = M4_Result_is_ok(self);
    if (is_ok) {
        *okv = *self;
    }
    return is_ok;
}


#elif M4_RESULT == 'S'

void M4_Result_destroy(M4_Result *const self)
{
    ((void)self);
}


void M4_Result_ok(M4_Result *const self, M4_ResultOk val)
{
    self->type = M4_Result_OK;
    self->u.ok = val;
}


void M4_Result_err_(M4_Result *const self, char const *file, size_t line,
                    M4_ResultErrType val)
{
    self->type = M4_Result_ERR;
    M4_ResultErr_new(&self->u.err, file, line, val);
}


bool M4_Result_is_ok(M4_Result const *const self)
{
    return self->type == M4_Result_OK;
}


bool M4_Result_is_err(M4_Result const *const self)
{
    return self->type == M4_Result_ERR;
}


M4_ResultOk M4_Result_unwrap(M4_Result *const self)
{
    if (M4_Result_is_ok(self)) {
        // move
        return self->u.ok;
    }
    M4_PANIC("not ok");

    // if (!M4_Result_is_ok(self)) {
    //     M4_PANIC("not ok");
    // }
    // return self->u.ok;
}


M4_ResultErr M4_Result_unwrap_err(M4_Result *const self)
{
    if (!M4_Result_is_err(self)) {
        M4_PANIC("not err");
    }
    M4_ResultErr err;
    M4_ResultErr_move(&err, &self->u.err);
    return err;
}


bool M4_Result_try(M4_Result *const self)
{
    bool const is_ok = M4_Result_is_ok(self);
    return is_ok;
}


bool M4_Result_try_unwrap(M4_Result *const self, M4_ResultOk *const okv)
{
    bool const is_ok = M4_Result_is_ok(self);
    // this is quicker/smaller by 1 instruction, in both paths.
    if (is_ok) {
        *okv = self->u.ok; // really, M4_ResultOk_move()..
        return true;
    }
    return false;

    // than this. so up yours misra
#if 0
    if (is_ok) {
        *okv = self->u.ok; // really, M4_ResultOk_move()..
    } else {
        // res.u.ok must be destroyed mere
    }
    return is_ok;
#endif
}

#else//
#error must have supported result implementation
#endif//
