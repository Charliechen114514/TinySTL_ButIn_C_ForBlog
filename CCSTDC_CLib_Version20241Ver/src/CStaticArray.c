#include "CLibLog.h"
#include "CLibUtility.h"
#include "CStaticArray.h"
#include "CUtilsContainerLogStr.h"

CStaticArray* CStaticArray_createCStaticArray(Size type_size, Size num, FILE* file)
{
    CODE_MSG_FORMAT(file, CREATE_ARRAY_STR, Info, true);
    CStaticArray* arr = NULL;
    Malloc(arr, CStaticArray, 1, file);
    NMalloc(arr->coreArray, type_size, num, file);
    arr->arraySize = num;
    arr->typeSize = type_size;
    arr->loggerPlace = file;
    CODE_MSG_FORMAT(file, OPERATE_SUCCESS, Info, false);
    WRITE_CStaticArray_Info(arr, file);
    return arr;
}

CStaticArray* CStaticArray_copyCStaticArray(CStaticArray* arr, FILE* file)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(arr, NULL, file);
    CODE_MSG_FORMAT(file, COPY_ARRAY_STR, Info, true);
    CStaticArray* other_arr = NULL;
    Malloc(other_arr, CStaticArray, 1, file);
    NMalloc(other_arr->coreArray, arr->typeSize, arr->arraySize, file);
    // make copy elems
    memcpy(other_arr->coreArray, arr->coreArray,
           other_arr->typeSize * other_arr->arraySize);
    other_arr->arraySize = arr->arraySize;
    other_arr->typeSize = arr->typeSize;
    other_arr->loggerPlace = file;
    CODE_MSG_FORMAT(file, OPERATE_SUCCESS, Info, true);
    WRITE_CStaticArray_Info(arr, file);
    return other_arr;
}

void* CStaticArray_At(CStaticArray* arr, Size index)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(arr, NULL, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(arr->coreArray, NULL, stderr);
    return (char*)arr->coreArray + index * arr->typeSize;
}

Size CStaticArray_getSize(CStaticArray* arr)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(arr, 0, stderr);
    return arr->arraySize;
}

CStaticArray* CStaticArray_Erase(CStaticArray* arr)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(arr, NULL, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(arr->coreArray, NULL, stderr);
    SafeFree(arr->coreArray, arr->coreArray);
    CODE_MSG_FORMAT(arr->loggerPlace, "free success the core arr\n", Info, true);
    FILE* p = arr->loggerPlace;
    CODE_MSG_FORMAT(arr->loggerPlace, "free success the arr struct\n", Info, false);
    SafeFree(arr, p);
    return arr;
}