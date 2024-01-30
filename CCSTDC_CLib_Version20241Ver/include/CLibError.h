#ifndef CUTILS_CLIBERROR_H
#define CUTILS_CLIBERROR_H
#include "stdlib.h"
#include "stdio.h"


#define DEFAULT_DEAL_ERROR_HANDLE(ERROR_CODE)   exit(ERROR_CODE)
#define DEFAULT_SPIN_HANDLE                     while(1);
#define DEFAULT_MY_ASSERT(condition) do\
{\
    if(!(condition))\
         DEFAULT_SPIN_HANDLE;           \
}while(0)

#define DEFAULT_MY_EXIT(condition, ERROR_CODE) do \
{\
    if(!(condition))\
        DEFAULT_DEAL_ERROR_HANDLE(ERROR_CODE);\
}while(0)

// USE THIS MACRO is better
#define CCSTD_LIB_EXIT(condition, ERROR_CODE)    DEFAULT_MY_EXIT(condition, ERROR_CODE)
#define CCSTD_LIB_SPIN(condition)                DEFAULT_MY_ASSERT(condition)

#define NO_ALLOWED_OPERATE_NULL_CHECK(ptr, error_return, logger) do{\
    if(!ptr){CODE_MSG_FORMAT(logger, VISIT_NULL_BUFFER, Error, true); return error_return;}}while(0)

#define ERASE_POP_EMPTY_WARNING(size, logger, return_what) do{\
        if(size == 0) {CODE_MSG_FORMAT(logger, EMPTY_POP_ERASE_STR, Warning, true); return return_what;}}while(0)

#define INDEX_INVALID_OPERATE(index,how_is_not_invalid, logger, allowed_index_max, return_what) do{ \
    if(!(how_is_not_invalid)) {CODE_MSG_FORMAT(logger,INVALID_INDEX_OPERATE, Error, true); return return_what;}}while(0)

#define MALLOC_FAILED   (-2)
#define FREE_INVALID    (-3)
#endif //CUTILS_CLIBERROR_H
