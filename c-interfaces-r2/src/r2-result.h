#ifndef R2_RESULT_H
#define R2_RESULT_H

/*
A result type encapsulating a ok type and an error type.
Usuall in C a simple int is used, with -ve vlues used for errors and other values used for ok.
along with using tacit checks at each call return (well you should be).

This implementation uses the same underlying type (an int), but wraps the usage
in functions to be more explicit about what is being done.
if (R2_Result_is_ok(res)) ..  vs if (res >= 0)..
the second is easer to type, but the reader needs to know that res >=0 is ok.
the first is explicit about what is going on.

Also, for errors, in the standard way, are converted to ints, and in the debugger
will not be presented in their symbolic form.
in this approach, they still aren't if treated as the result type.
to get to the error value you'd need to unrap_err() them.

note: this pattern is preserved if error or success types are not ints,
at that point the underlying implementation would use
 */
//#define R2_RESULT 'I'
#define R2_RESULT 'S'

#if R2_RESULT == 'I'
#elif R2_RESULT == 'S'
    typedef struct R2_Result_s R2_Result;
#else//
#endif//

#include <stdbool.h> // true,false
#include <stddef.h> // size_t

#define R2_RESULTERR_INSTRUMENTED

typedef enum R2_ResultErrType_e {
    R2_Err_InvalidParam = 1,
    R2_Err_NotImplemented,
    R2_Err_InvalidInterfaceID,
    R2_Err_InvalidAttributeID,
    R2_Err_InvalidActionID,
    R2_Err_InvalidInterface,
} R2_ResultErrType;

typedef struct R2_ResultErr_s R2_ResultErr;
struct R2_ResultErr_s {
    R2_ResultErrType code;
#if defined(R2_RESULTERR_INSTRUMENTED)
    size_t line;
    char const *file;
#endif//
};
void ResultErr_destroy(R2_ResultErr *const self);
void R2_ResultErr_move(R2_ResultErr *const self, R2_ResultErr *const src);
R2_ResultErr R2_ResultErr_new(char const *file, size_t line,
                              R2_ResultErrType code);


typedef int R2_ResultOk;


#if R2_RESULT == 'I'
typedef int R2_Result;

#elif R2_RESULT == 'S'
// note implementaion requires ok and Err types to be bitwise copyable.
struct R2_Result_s {
    enum {
        R2_Result_OK = 1,
        R2_Result_ERR,
    } type;
    union {
        R2_ResultOk ok;
        R2_ResultErr err;
    } u;
};

#else//
#error must have supported result type

#endif//

void R2_Result_destroy(R2_Result *const self);
R2_Result R2_Result_ok(R2_ResultOk val);
R2_Result R2_Result_err_(const char *file, size_t line, R2_ResultErrType val);
#define R2_Result_err(val) R2_Result_err_(__FILE__, __LINE__, val);

bool R2_Result_is_ok(R2_Result const *const res);
bool R2_Result_is_err(R2_Result const *const res);

R2_ResultOk R2_Result_unwrap(R2_Result *const res);
R2_ResultErr R2_Result_unwrap_err(R2_Result *const res);

bool R2_Result_try(R2_Result *const res);
bool R2_Result_try_unwrap(R2_Result *const res, R2_ResultOk *const okv);

#define R2_RESULT_TRY0(res) do{if(!R2_Result_try(&res)) return (res);}while(0);
#define R2_RESULT_TRY1(res, okv) do{if(!R2_Result_try_unwrap(&res, okv)) return (res);}while(0);

#endif//RESULT_H
