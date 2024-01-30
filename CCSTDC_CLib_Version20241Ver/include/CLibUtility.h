#ifndef CUTILS_CLIBUTILITY_H
#define CUTILS_CLIBUTILITY_H
// preIncludes
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "CLibLog.h"
#include "CLibError.h"
#include "CUtilsLibLogStr.h"
// types
// size
typedef int     Size;
typedef int    Index;
#ifndef bool
typedef char bool;
#endif
#ifndef true
#define true            1
#endif
#ifndef false
#define false           0
#endif

#define USE_LIB // CUtils String

// utils func

/// NEED RETURN
typedef bool(*CompareFunc)(const void* elem1 ,const void* elem2);
typedef enum {
    SMALL   = -1,
    EQUAL   = 0,
    BIGGER  = 1
}Compare_State;


bool compInt(const int* a,const int* b);
bool compDouble(const double* a, const double* b);
bool compChar(const char* a, const char* b);

// Reminders

#define _GETTER_
#define _SHOULD_BE_NULL


// Macros
#define Malloc(ptr, type, type_num, logger) do{ \
    if(ptr)                                     \
    {                                           \
        CODE_MSG_FORMAT(logger, OVERLAP_INITED_MEMORY, Warning, true);\
    }\
    type* _CCSTDC_MALLOC_PTR = (type*)calloc(type_num, sizeof(type));\
    if(!_CCSTDC_MALLOC_PTR)/* here means failed malloc*/            \
    {                                          \
        CODE_MSG_FORMAT(logger, MALLOC_FAILED_STR, Error, true);    \
        CCSTD_LIB_EXIT(false, MALLOC_FAILED);\
    }                                          \
    ptr = _CCSTDC_MALLOC_PTR;\
}while(0)

#define NMalloc(ptr, type_size, type_num, logger) \
do{                                               \
    if(ptr)                                     \
    {                                           \
        CODE_MSG_FORMAT(logger, OVERLAP_INITED_MEMORY, Warning, true);\
    }                                              \
    void* _CCSTDC_MALLOC_PTR = calloc(type_num, ((type_size) * (type_num)) );\
    if(!_CCSTDC_MALLOC_PTR)/* here means failed malloc*/            \
    {                                          \
        CODE_MSG_FORMAT(logger, MALLOC_FAILED_STR, Error, true);    \
        CCSTD_LIB_EXIT(false, MALLOC_FAILED);\
    }                                          \
    ptr = _CCSTDC_MALLOC_PTR;\
}while(0)

#define Realloc(ptr, type_size, new_type_num, logger) \
do{                                                   \
    void* _CCSTDC_MALLOC_PTR = realloc(ptr, ((type_size) * (new_type_num)) );\
    if(!_CCSTDC_MALLOC_PTR)/* here means failed malloc*/            \
    {                                          \
        CODE_MSG_FORMAT(logger, MALLOC_FAILED_STR, Error, true);    \
        CCSTD_LIB_EXIT(false, MALLOC_FAILED);\
    }                                          \
    ptr = _CCSTDC_MALLOC_PTR;\
}while(0)

#define SafeFree(ptr, logger) \
do{                   \
    if(!(ptr))                      \
    {                 \
        CODE_MSG_FORMAT(logger, FREE_INVALID_SIZE, Error, true); \
        CCSTD_LIB_EXIT(false, FREE_INVALID);\
    }                  \
    free(ptr);                \
    ptr = NULL;               \
}while(0)

#endif //CUTILS_CLIBUTILITY_H
