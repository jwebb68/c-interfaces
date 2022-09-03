#ifndef M3_RESULT_H
#define M3_RESULT_H

/*
A result type encapsulating a ok type and an error type.
Usuall in C a simple int is used, with -ve vlues used for errors and other values used for ok.
along with using tacit checks at each call return (well you should be).

This implementation uses the same underlying type (an int), but wraps the usage
in functions to be more explicit about what is being done.
if (M3_Result_is_ok(res)) ..  vs if (res >= 0)..
the second is easer to type, but the reader needs to know that res >=0 is ok.
the first is explicit about what is going on.

Also, for errors, in the standard way, are converted to ints, and in the debugger
will not be presented in their symbolic form.
in this approach, they still aren't if treated as the result type.
to get to the error value you'd need to unrap_err() them.

note: this pattern is preserved if error or success types are not ints,
at that point the underlying implementation would use
 */
//#define M3_RESULT 'I'
#define M3_RESULT 'S'


#if M3_RESULT == 'I'
#elif M3_RESULT == 'S'
    typedef struct M3_Result_s M3_Result;
#else//
#endif//


#include <stdbool.h> // true,false
#include <stddef.h> // size_t


#define M3_RESULTERR_INSTRUMENTED


typedef enum M3_ResultErrType_e {
    M3_Err_InvalidParam = 1,
    M3_Err_NotImplemented,
    M3_Err_InvalidInterfaceID,
    M3_Err_InvalidAttributeID,
    M3_Err_InvalidActionID,
    M3_Err_InvalidInterface,
} M3_ResultErrType;


typedef struct M3_Result_Err_s M3_ResultErr;
struct M3_Result_Err_s {
    M3_ResultErrType code;
#if defined(M3_RESULTERR_INSTRUMENTED)
    size_t line;
    char const *file;
#endif//
};

void M3_Result_Err_destroy(M3_ResultErr *const self);


void M3_Result_Err_move(M3_ResultErr *const self, M3_ResultErr *const src);


void M3_Result_Err_new(M3_ResultErr *const self, char const *file, size_t line,
                       M3_ResultErrType code);


typedef int M3_ResultOk;


#if M3_RESULT == 'I'

typedef int M3_Result;


#elif M3_RESULT == 'S'

// note implementaion requires ok and Err types to be bitwise copyable.
struct M3_Result_s {
    enum {
        M3_Result_OK = 1,
        M3_Result_ERR,
    } type;
    union {
        M3_ResultOk ok;
        M3_ResultErr err;
    } u;
};


#else//
#error must have supported result type

#endif//


void M3_Result_destroy(M3_Result *const self);


void M3_Result_ok(M3_Result *const self, M3_ResultOk val);


void M3_Result_err_(M3_Result *const self, const char *file, size_t line,
                    M3_ResultErrType val);
#define M3_Result_err(res, val) M3_Result_err_(res, __FILE__, __LINE__, val);


bool M3_Result_is_ok(M3_Result const *const res);


bool M3_Result_is_err(M3_Result const *const res);


M3_ResultOk M3_Result_unwrap(M3_Result *const res);


M3_ResultErr M3_Result_unwrap_err(M3_Result *const res);


bool M3_Result_try(M3_Result *const res);


bool M3_Result_try_unwrap(M3_Result *const res, M3_ResultOk *const okv);


#define M3_RESULT_TRY0(res) do{if(!M3_Result_try(res)) return;}while(0);


#define M3_RESULT_TRY1(res, okv) do{if(!M3_Result_try_unwrap(res, okv)) return;}while(0);


#endif//M3_RESULT_H
