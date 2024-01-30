#include "CDynamicArray.h"
#include "CLibLog.h"
#include "CLibUtility.h"
#include "CUtilsContainerLogStr.h"
#include <stdio.h>
#define GET_END_PTR(arr)            ((char*)(arr->array) + (arr->cur_size) * (arr->type_size))
#define GET_LAST_PTR(arr)           ((char*)(arr->array) + (arr->cur_size - 1) * (arr->type_size))
#define GET_INDEXED_PTR(arr, index) ((char*)(arr->array) + (index)*(arr->type_size))
#define GET_FIRST_ELEM(arr)         ((char*)(arr->array))
#define INDEX_VALID(arr, index)     (index >= 0 && index <= arr->cur_size)
#define KICK_INDEX_VALID(arr, index) (index >= 0 && index < arr->cur_size)


// private interface
void expandArray(CDynamicArray* arr, int new_size)
{
    Realloc(arr->array, arr->type_size, new_size, arr->logger);
    CODE_MSG_FORMAT(arr->logger, REALLOC_SIZE_STR, Info, true);

    // update capacity
    arr->capacity = new_size;
}

void shrinkArrayToFit(CDynamicArray* arr)
{
    Realloc(arr->array, arr->type_size, arr->cur_size + 2, arr->logger);
    CODE_MSG_FORMAT(arr->logger, REALLOC_SIZE_STR, Info, true);

    // update capacity
    arr->capacity = arr->cur_size + 2;
}

void fastShrink(CDynamicArray* arr, int size)
{
    Realloc(arr->array, arr->type_size, size, arr->logger);
    CODE_MSG_FORMAT(arr->logger, REALLOC_SIZE_STR, Info, true);
    // update capacity
    arr->capacity = size;
    arr->cur_size = size;
}

void checkSizeAndHandle(CDynamicArray* arr)
{
    if(DEFAULT_NEED_EXPAND(arr))
        expandArray(arr,DEFAULT_EXPAND_NEW_SIZE(arr));
    else if(DEFAULT_NEED_SHRINK(arr))
        shrinkArrayToFit(arr);
}

void checkSizeAndHandleWhenMerge(CDynamicArray* arr, int new_size)
{
    if(new_size >= arr->cur_size - 1)
        expandArray(arr,new_size + 1);
}

CDynamicArray* CDynamicArray_CreateCDynamicArr(int type_size, int init_capacity, FILE* logger)
{
    CDynamicArray* arr = NULL;
    CODE_MSG_FORMAT(logger, CREATE_DYNAMIC_ARR_STR, Info, true);
    // malloc space
    Malloc(arr, CDynamicArray, 1, logger);
    NMalloc(arr->array, init_capacity, type_size, logger);

    // init
    arr->cur_size = 0;
    arr->type_size = type_size;
    arr->capacity = init_capacity;
    arr->logger = logger;

    CODE_MSG_FORMAT(logger, OPERATE_SUCCESS, Info, true);
    WRITE_CDynamicArray_Info(arr, logger);
    return arr;
}

CDynamicArray* CDynamicArray_CopyCDynamicArr(CDynamicArray* arr, FILE* logger)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(arr, NULL, stderr);
    CDynamicArray* other = NULL;
    CODE_MSG_FORMAT(logger, COPY_DYNAMIC_ARR_STR, Info, true);
    // malloc space
    Malloc(other, CDynamicArray, 1, logger);
    NMalloc(other->array, arr->capacity, arr->type_size, logger);

    // copy data
    memcpy(other->array, arr->array, arr->cur_size * arr->type_size);

    // config
    other->logger = logger;
    other->type_size = arr->type_size;
    other->cur_size = arr->cur_size;
    other->capacity = arr->capacity;

    CODE_MSG_FORMAT(logger, OPERATE_SUCCESS, Info, true);
    WRITE_CDynamicArray_Info(other, logger);
    return other;
}

bool CDynamicArray_PushBack(CDynamicArray* who, void* elem)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(who, false, stderr);
    CODE_MSG_FORMAT(who->logger, PUSH_BACK_STR, Info, true);
    checkSizeAndHandle(who);

    memcpy(GET_END_PTR(who), elem, who->type_size);

    who->cur_size++;

    return true;
}

void* CDynamicArray_PopBack(CDynamicArray* who, bool need_freeAuto)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(who, false, stderr);
    ERASE_POP_EMPTY_WARNING(who->cur_size ,who->logger, NULL);

    CODE_MSG_FORMAT(who->logger, POP_BACK_STR, Info, true);
    checkSizeAndHandle(who);

    void* fin_elem = NULL;
    if(!need_freeAuto)
    {
        Malloc(fin_elem, char, who->type_size, who->logger);

        memcpy(fin_elem, GET_LAST_PTR(who), who->type_size);
    }

    who->cur_size--;

    return fin_elem;
}

bool CDynamicArray_PushFront(CDynamicArray* who, void* elem)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(who, false, stderr);
    CODE_MSG_FORMAT(who->logger, PUSH_FRONT_STR, Info, true);
    checkSizeAndHandle(who);

    for(int i = who->cur_size; i >= 1; i--)
        memcpy(GET_INDEXED_PTR(who, i), GET_INDEXED_PTR(who, i - 1),  who->type_size);

    memcpy(GET_FIRST_ELEM(who), elem, who->type_size);
    who->cur_size++;

    return true;
}

void* CDynamicArray_PopFront(CDynamicArray* who, bool need_freeAuto)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(who, false, stderr);
    CODE_MSG_FORMAT(who->logger, POP_FRONT_STR, Info, true);
    ERASE_POP_EMPTY_WARNING(who->cur_size ,who->logger, NULL);
    checkSizeAndHandle(who);

    void* elem = NULL;
    if(!need_freeAuto)
    {
        Malloc(elem, char, who->type_size, who->logger);

        memcpy(elem, GET_LAST_PTR(who), who->type_size);
    }

    for(int i = 1; i < who->cur_size; i++)
        memcpy(GET_INDEXED_PTR(who, i - 1), GET_INDEXED_PTR(who, i),  who->type_size);

    who->cur_size--;

    return elem;
}

bool CDynamicArray_Insert(CDynamicArray* arr, void* elem, Index index)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(arr, false, stderr);
    CODE_MSG_FORMAT_Self_def(arr->logger, fprintf(arr->logger, INSERT_STR(index), index), Info, true);
    INDEX_INVALID_OPERATE(index, INDEX_VALID(arr, index), arr->logger, arr->cur_size, false);
    checkSizeAndHandle(arr);

    for(int i = arr->cur_size; i >= index; i--)
        memcpy(GET_INDEXED_PTR(arr, i + 1), GET_INDEXED_PTR(arr, i), arr->type_size);

    memcpy(GET_INDEXED_PTR(arr, index), elem, arr->type_size);
    arr->cur_size++;

    return true;
}

void* CDynamicArray_Kick(CDynamicArray* arr, Index index)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(arr, false, stderr);
    CODE_MSG_FORMAT_Self_def(arr->logger, fprintf(arr->logger, INSERT_STR(index), index), Info, true);
    INDEX_INVALID_OPERATE(index, KICK_INDEX_VALID(arr, index), arr->logger, arr->cur_size, false);
    checkSizeAndHandle(arr);

    void* kicked = NULL;
    Malloc(kicked, char, arr->type_size, arr->logger);
    memcpy(kicked, GET_INDEXED_PTR(arr,index), arr->type_size);

    for(int i = index; i < arr->cur_size; i++)
        memcpy(GET_INDEXED_PTR(arr, i), GET_INDEXED_PTR(arr, i + 1), arr->type_size);

    arr->cur_size--;
    return kicked;
}

bool CDynamicArray_Merge(CDynamicArray* appendee,
                         CDynamicArray* appender,
                         Index index,
                         bool reserve_appender)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(appendee, false, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(appender, false, stderr);
    INDEX_INVALID_OPERATE(index, KICK_INDEX_VALID(appendee, index), appendee->logger, arr->cur_size, false);
    checkSizeAndHandleWhenMerge(appendee, appendee->cur_size + appender->cur_size);

    for(int appendee_index = index + appender->cur_size - 1,appender_index = appender->cur_size - 1;
        appender_index >= 0; appendee_index--, appender_index--)
    {
        // make move
        memcpy(GET_INDEXED_PTR(appendee, appendee_index + appender->cur_size),
               GET_INDEXED_PTR(appendee, appendee_index),
               appendee->type_size);

        memcpy(GET_INDEXED_PTR(appendee, appendee_index),
               GET_INDEXED_PTR(appender, appender_index),
               appendee->type_size);
    }

    appendee->cur_size += appender->cur_size;

    if(reserve_appender && appendee != appender)
        CDynamicArray_Erase(appender);
    return true;
}

void* CDynamicArray_At(CDynamicArray* arr, Index index)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(arr, NULL, stderr);
    INDEX_INVALID_OPERATE(index, KICK_INDEX_VALID(arr, index), arr->logger, arr->cur_size, false);

    return GET_INDEXED_PTR(arr, index);
}

// return the second part
CDynamicArray*  CDynamicArray_Split(CDynamicArray* arr, Index index)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(arr, NULL, stderr);
    INDEX_INVALID_OPERATE(index, KICK_INDEX_VALID(arr, index), arr->logger, arr->cur_size, false);

    // if only one, no splits
    if(arr->cur_size <= 1)
        return NULL;

    CDynamicArray* sec = CDynamicArray_CreateCDynamicArr(arr->type_size, arr->cur_size - index - 1, arr->logger);

    for(int i = index + 1; i < arr->cur_size; i++)
        CDynamicArray_PushBack(sec, GET_INDEXED_PTR(arr, i));

    fastShrink(arr, index + 1);

    return sec;
}

CDynamicArray* CDynamicArray_Erase(CDynamicArray* arr)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(arr, NULL, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(arr->array, NULL, stderr);
    WRITE_CDynamicArray_Info(arr, arr->logger);
    SafeFree(arr->array, arr->logger);
    CODE_MSG_FORMAT(arr->logger, "free success the core arr\n", Info, true);
    FILE* logger = arr->logger;
    SafeFree(arr, logger);
    CODE_MSG_FORMAT(logger, "free success arr\n", Info, true);
    return arr;
}