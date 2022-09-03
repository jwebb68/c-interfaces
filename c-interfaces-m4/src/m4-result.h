#ifndef M4_RESULT_H
#define M4_RESULT_H

/*
A result type encapsulating a ok type and an error type.
Usuall in C a simple int is used, with -ve vlues used for errors and other values used for ok.
along with using tacit checks at each call return (well you should be).

This implementation uses the same underlying type (an int), but wraps the usage
in functions to be more explicit about what is being done.
if (M4_Result_is_ok(res)) ..  vs if (res >= 0)..
the second is easer to type, but the reader needs to know that res >=0 is ok.
the first is explicit about what is going on.

Also, for errors, in the standard way, are converted to ints, and in the debugger
will not be presented in their symbolic form.
in this approach, they still aren't if treated as the result type.
to get to the error value you'd need to unrap_err() them.

note: this pattern is preserved if error or success types are not ints,
at that point the underlying implementation would use
 */
//#define M4_RESULT 'I'
#define M4_RESULT 'S'


#if M4_RESULT == 'I'
#elif M4_RESULT == 'S'
    typedef struct M4_Result_s M4_Result;
#else//
#endif//


#include <stdbool.h> // true,false
#include <stddef.h> // size_t


#define M4_RESULTERR_INSTRUMENTED


typedef enum M4_ResultErrType_e {
    M4_Err_InvalidParam = 1,
    M4_Err_NotImplemented,
    M4_Err_InvalidInterfaceID,
    M4_Err_InvalidAttributeID,
    M4_Err_InvalidActionID,
    M4_Err_InvalidInterface,
} M4_ResultErrType;


typedef struct M4_Result_Err_s M4_ResultErr;
struct M4_Result_Err_s {
    M4_ResultErrType code;
#if defined(M4_RESULTERR_INSTRUMENTED)
    size_t line;
    char const *file;
#endif//
};

void M4_Result_Err_destroy(M4_ResultErr *const self);


void M4_Result_Err_move(M4_ResultErr *const self, M4_ResultErr *const src);


void M4_Result_Err_new(M4_ResultErr *const self, char const *file, size_t line,
                       M4_ResultErrType code);


typedef int M4_ResultOk;


#if M4_RESULT == 'I'

typedef int M4_Result;


#elif M4_RESULT == 'S'

// note implementaion requires ok and Err types to be bitwise copyable.
struct M4_Result_s {
    enum {
        M4_Result_OK = 1,
        M4_Result_ERR,
    } type;
    union {
        M4_ResultOk ok;
        M4_ResultErr err;
    } u;
};


#else//
#error must have supported result type

#endif//


void M4_Result_destroy(M4_Result *const self);


void M4_Result_ok(M4_Result *const self, M4_ResultOk val);


void M4_Result_err_(M4_Result *const self, const char *file, size_t line,
                    M4_ResultErrType val);
#define M4_Result_err(res, val) M4_Result_err_(res, __FILE__, __LINE__, val);


bool M4_Result_is_ok(M4_Result const *const res);


bool M4_Result_is_err(M4_Result const *const res);


M4_ResultOk M4_Result_unwrap(M4_Result *const res);


M4_ResultErr M4_Result_unwrap_err(M4_Result *const res);


bool M4_Result_try(M4_Result *const res);


bool M4_Result_try_unwrap(M4_Result *const res, M4_ResultOk *const okv);


#define M4_RESULT_TRY0(res) do{if(!M4_Result_try(res)) return;}while(0);


#define M4_RESULT_TRY1(res, okv) do{if(!M4_Result_try_unwrap(res, okv)) return;}while(0);


#endif//M4_RESULT_H
