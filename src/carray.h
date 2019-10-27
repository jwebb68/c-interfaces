#ifndef CARRAY_H
#define CARRAY_H

#define CARRAY_COUNT(carray) (sizeof(carray)/sizeof(carray[0]))
#define CARRAY_BEGIN(carray) (&carray[0])
#define CARRAY_END(carray) CARRAY_BEGIN(carray)+CARRAY_COUNT(carray)
#define CARRAY_SIZE(carray) sizeof(carray)

#endif//CARRAY_H
