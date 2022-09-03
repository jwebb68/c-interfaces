#ifndef M4_CARRAY_H
#define M4_CARRAY_H

#define M4_CARRAY_COUNT(carray) (sizeof(carray)/sizeof(carray[0]))
#define M4_CARRAY_LEN(carray) (sizeof(carray)/sizeof(carray[0]))
#define M4_CARRAY_BEGIN(carray) (&carray[0])
#define M4_CARRAY_END(carray) (M4_CARRAY_BEGIN(carray) + M4_CARRAY_COUNT(carray))
#define M4_CARRAY_SIZE(carray) sizeof(carray)

#endif//M4_CARRAY_H
