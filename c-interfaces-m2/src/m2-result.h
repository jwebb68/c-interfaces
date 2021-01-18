#ifndef M2_RESULT_H
#define M2_RESULT_H

/*
A result type encapsulating a ok type and an error type.
Usuall in C a simple int is used, with -ve vlues used for errors and other values used for ok.
along with using tacit checks at each call return (well you should be).

This implementation uses the same underlying type (an int), but wraps the usage
in functions to be more explicit about what is being done.
if (M2_Result_is_ok(res)) ..  vs if (res >= 0)..
the second is easer to type, but the reader needs to know that res >=0 is ok.
the first is explicit about what is going on.

Also, for errors, in the standard way, are converted to ints, and in the debugger
will not be presented in their symbolic form.
in this approach, they still aren't if treated as the result type.
to get to the error value you'd need to unrap_err() them.

note: this pattern is preserved if error or success types are not ints,
at that point the underlying implementation would use
 */
//#define M2_RESULT 'I'
#define M2_RESULT 'S'


#if M2_RESULT == 'I'
#elif M2_RESULT == 'S'
    typedef struct M2_Result_s M2_Result;
#else//
#endif//


#include <stdbool.h> // true,false
#include <stddef.h> // size_t


#define M2_RESULTERR_INSTRUMENTED


typedef enum M2_ResultErrType_e {
    M2_Err_InvalidParam = 1,
    M2_Err_NotImplemented,
    M2_Err_InvalidInterfaceID,
    M2_Err_InvalidAttributeID,
    M2_Err_InvalidActionID,
    M2_Err_InvalidInterface,
} M2_ResultErrType;


typedef struct M2_Result_Err_s M2_ResultErr;
struct M2_Result_Err_s {
    M2_ResultErrType code;
#if defined(M2_RESULTERR_INSTRUMENTED)
    size_t line;
    char const *file;
#endif//
};

void M2_Result_Err_destroy(M2_ResultErr *const self);


void M2_Result_Err_move(M2_ResultErr *const self, M2_ResultErr *const src);


void M2_Result_Err_new(M2_ResultErr *const self, char const *file, size_t line,
                       M2_ResultErrType code);


typedef int M2_ResultOk;


#if M2_RESULT == 'I'

typedef int M2_Result;


#elif M2_RESULT == 'S'

// note implementaion requires ok and Err types to be bitwise copyable.
struct M2_Result_s {
    enum {
        M2_Result_OK = 1,
        M2_Result_ERR,
    } type;
    union {
        M2_ResultOk ok;
        M2_ResultErr err;
    } u;
};


#else//
#error must have supported result type

#endif//


void M2_Result_destroy(M2_Result *const self);


void M2_Result_ok(M2_Result *const self, M2_ResultOk val);


void M2_Result_err_(M2_Result *const self, const char *file, size_t line,
                    M2_ResultErrType val);
#define M2_Result_err(res, val) M2_Result_err_(res, __FILE__, __LINE__, val);


bool M2_Result_is_ok(M2_Result const *const res);


bool M2_Result_is_err(M2_Result const *const res);


M2_ResultOk M2_Result_unwrap(M2_Result *const res);


M2_ResultErr M2_Result_unwrap_err(M2_Result *const res);


bool M2_Result_try(M2_Result *const res);


bool M2_Result_try_unwrap(M2_Result *const res, M2_ResultOk *const okv);


#define M2_RESULT_TRY0(res) do{if(!M2_Result_try(res)) return;}while(0);


#define M2_RESULT_TRY1(res, okv) do{if(!M2_Result_try_unwrap(res, okv)) return;}while(0);


#endif//M2_RESULT_H
