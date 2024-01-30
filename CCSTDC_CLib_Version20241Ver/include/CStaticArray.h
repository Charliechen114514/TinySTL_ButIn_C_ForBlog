#ifndef CUTILS_CSTATICARRAY_H
#define CUTILS_CSTATICARRAY_H
#include "CLibUtility.h"

typedef struct ___CStaticArray
{
    // members
    void*   coreArray;
    Size    arraySize;
    Size    typeSize;
    FILE*   loggerPlace;
}CStaticArray;

// setNULL as NO_LOGGER
CStaticArray*   CStaticArray_createCStaticArray(Size type_size, Size num, FILE* file);
CStaticArray*   CStaticArray_copyCStaticArray(CStaticArray* arr, FILE* file);
void*           CStaticArray_At(CStaticArray* arr, Size index);
Size            CStaticArray_getSize(CStaticArray* arr);
CStaticArray*   CStaticArray_Erase(CStaticArray* arr);


#endif //CUTILS_CSTATICARRAY_H
