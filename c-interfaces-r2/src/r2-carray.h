#ifndef R2_CARRAY_H
#define R2_CARRAY_H

#define R2_CARRAY_COUNT(carray) (sizeof(carray)/sizeof(carray[0]))
#define R2_CARRAY_LEN(carray) (sizeof(carray)/sizeof(carray[0]))
#define R2_CARRAY_BEGIN(carray) (&carray[0])
#define R2_CARRAY_END(carray) (R2_CARRAY_BEGIN(carray) + R2_CARRAY_COUNT(carray))
#define R2_CARRAY_SIZE(carray) sizeof(carray)

#endif//CARRAY_H
