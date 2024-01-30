//
// Created by ³Â¹ÚºÀ on 2024/1/23.
//

#ifndef CUTILS_CMAP_H
#define CUTILS_CMAP_H
#include "CLibUtility.h"

struct ___LinkList;


typedef struct ___Map // One Key, One Value
{
    FILE*               logger;
    struct ___LinkList* mapActually;
    CompareFunc         compFunc;
}CLinearMap;

CLinearMap*     CLinearMap_CreateAEmptyCMap(FILE* logger, CompareFunc func);
CLinearMap*     CLinearMap_CopyACLinearMap(CLinearMap* map, FILE* logger);
void*           CLinearMap_Key(CLinearMap* map, void* value, CompareFunc val_func);
void*           CLinearMap_Value(CLinearMap* map, void* key);
bool            CLinearMap_InsertAKey_Value_Pair(CLinearMap* map, void* key, Size key_size, void* value, Size map_size);
bool            CLinearMap_ContainsKey(CLinearMap* map, void* key);
bool            CLinearMap_PopPairOfKeyValue(CLinearMap* map, void* key);
CLinearMap*     CLinearMap_EraseMap(CLinearMap* map);



#endif //CUTILS_CMAP_H
