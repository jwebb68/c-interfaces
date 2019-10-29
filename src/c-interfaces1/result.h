#ifndef RESULT_H
#define RESULT_H

/*
A result type encapsulating a ok type and an error type.
Usuall in C a simple int is used, with -ve vlues used for errors and other values used for ok.
along with using tacit checks at each call return (well you should be).

This implementation uses the same underlying type (an int), but wraps the usage
in functions to be more explicit about what is being done.
if (Result_is_ok(res)) ..  vs if (res >= 0)..
the second is easer to type, but the reader needs to know that res >=0 is ok.
the first is explicit about what is going on.

Also, for errors, in the standard way, are converted to ints, and in the debugger
will not be presented in their symbolic form.
in this approach, they still aren't if treated as the result type.
to get to the error value you'd need to unrap_err() them.

note: this pattern is preserved if error or success types are not ints,
at that point the underlying implementation would use
 */
//#define RESULT 'I'
#define RESULT 'S'

#if RESULT == 'I'
#elif RESULT == 'S'
typedef struct _Result Result;
#else//
#endif//

#include <stdbool.h> // true,false

typedef enum _ResultErr {
    Err_InvalidParam=1,
    Err_NotImplemented,
    Err_InvalidInterfaceID,
    Err_InvalidAttributeID,
    Err_InvalidActionID,
    Err_InvalidInterface,
} ResultErr;

typedef int ResultOk;


#if RESULT == 'I'
typedef int Result;

#elif RESULT == 'S'
// note implementaion requires ok and Err types to be bitwise copyable.
struct _Result {
    enum {
        Result_OK=1,
        Result_ERR,
    } type;
    union {
        ResultOk ok;
        ResultErr err;
    };
};

#else//
#error must have supported result type

#endif//

Result Result_ok(ResultOk val);
Result Result_err(ResultErr val);

bool Result_is_ok(Result res);
bool Result_is_err(Result res);

ResultOk Result_unwrap(Result res);
ResultErr Result_unwrap_err(Result res);

#define RESULT_TRY(res) do{if(Result_is_err(res)) return (res);}while(0)

#endif//RESULT_H
