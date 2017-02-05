#ifndef __TYPE
#define __TYPE

typedef char                int8_t;
typedef unsigned char       uint8_t;
typedef short               int16_t;
typedef unsigned short      uint16_t;
typedef int                 int32_t;
typedef unsigned int        uint32_t;
typedef long long           int64_t;
typedef unsigned long long  uint64_t;
typedef uint32_t            size_t;
typedef int32_t             ssize_t;
typedef uint64_t            offset_t;

#define NULL                ((void *)0)
#define Unused(x)           (void)x

#define MemberOffset(type, member)          ((size_t)&((type *)0) -> member)
#define MemberContainer(ptr, type, member)  ({\
    const typeof(((type *)0) -> member) *__ptr = (ptr);\
    (type *)((char *)__ptr - MemberOffset(type, member));\
})

#endif
