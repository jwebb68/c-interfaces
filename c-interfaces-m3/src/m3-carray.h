#ifndef M3_CARRAY_H
#define M3_CARRAY_H

#define M3_CARRAY_COUNT(carray) (sizeof(carray)/sizeof(carray[0]))
#define M3_CARRAY_LEN(carray) (sizeof(carray)/sizeof(carray[0]))
#define M3_CARRAY_BEGIN(carray) (&carray[0])
#define M3_CARRAY_END(carray) (M3_CARRAY_BEGIN(carray) + M3_CARRAY_COUNT(carray))
#define M3_CARRAY_SIZE(carray) sizeof(carray)

#endif//M3_CARRAY_H
