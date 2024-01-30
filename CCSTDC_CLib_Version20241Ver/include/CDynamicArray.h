//
// Created by ³Â¹ÚºÀ on 2024/1/21.
//

#ifndef CUTILS_CDYNAMICARRAY_H
#define CUTILS_CDYNAMICARRAY_H
#include "CLibUtility.h"

#define DEFAULT_DYNAMIC_ARR_SIZE            10
#define DEFAULT_NEED_EXPAND(arr)            (arr->cur_size >= arr->capacity - 1)
#define DEFAULT_NEED_SHRINK(arr)            (arr->cur_size <= arr->capacity / 3)
#define DEFAULT_EXPAND_NEW_SIZE(arr)        (arr->capacity * 2)

typedef struct __CDynamicArr{
    Size        cur_size;
    Size        type_size;
    Size        capacity;
    void*       array;
    FILE*       logger;
}CDynamicArray;

CDynamicArray* CDynamicArray_CreateCDynamicArr(int type_size, int init_capacity, FILE* logger);
CDynamicArray* CDynamicArray_CopyCDynamicArr(CDynamicArray* arr, FILE* logger);
#ifdef CStaticArray
CDynamicArray* CDynamicArray_Update2CDynamic(CStaticArray* arr);
CStaticArray*  CDynamicArray_DownToStatic(CDynamicArray* arr);
#endif

bool            CDynamicArray_PushBack(CDynamicArray* who, void* elem);
void*           CDynamicArray_PopBack(CDynamicArray* who, bool need_freeAuto);
bool            CDynamicArray_PushFront(CDynamicArray* who, void* elem);
void*           CDynamicArray_PopFront(CDynamicArray* who, bool need_freeAuto);

bool            CDynamicArray_Insert(CDynamicArray* arr, void* elem , Index index);
void*           CDynamicArray_Kick(CDynamicArray* arr, Index index);
bool            CDynamicArray_Merge(CDynamicArray* appendee, CDynamicArray* appender,
                                    Index where, bool reserve_appender);
void*           CDynamicArray_At(CDynamicArray* arr, Index index);
CDynamicArray*  CDynamicArray_Split(CDynamicArray* arr, Index index);

CDynamicArray*  CDynamicArray_Erase(CDynamicArray* arr);

#endif //CUTILS_CDYNAMICARRAY_H
