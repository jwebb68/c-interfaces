#ifndef RESULT_H
#define RESULT_H

#include <stdbool.h> // true,false

typedef enum _Result_Err {
    Err_InvalidParam=1,
    Err_NotImplemented
} Result_Err;
typedef int Result_Ok;
typedef int Result;

Result Result_ok(Result_Ok val);
Result Result_err(Result_Err val);

bool Result_is_ok(Result res);
bool Result_is_err(Result res);

Result_Ok Result_unwrap(Result res);
Result_Err Result_unwrap_err(Result res);

#endif//RESULT_H
