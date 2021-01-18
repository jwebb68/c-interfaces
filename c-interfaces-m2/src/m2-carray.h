#ifndef M2_CARRAY_H
#define M2_CARRAY_H

#define M2_CARRAY_COUNT(carray) (sizeof(carray)/sizeof(carray[0]))
#define M2_CARRAY_LEN(carray) (sizeof(carray)/sizeof(carray[0]))
#define M2_CARRAY_BEGIN(carray) (&carray[0])
#define M2_CARRAY_END(carray) (M2_CARRAY_BEGIN(carray) + M2_CARRAY_COUNT(carray))
#define M2_CARRAY_SIZE(carray) sizeof(carray)

#endif//M2_CARRAY_H
