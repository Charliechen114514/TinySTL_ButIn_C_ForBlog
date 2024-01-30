//
// Created by ³Â¹ÚºÀ on 2024/1/30.
//

#ifndef CUTILS_CBITMAP_H
#define CUTILS_CBITMAP_H
#include "CLibUtility.h"

typedef struct ___BitMap
{
    unsigned char*  BitArray;
    Size            bitmapSize;
}CBitMap;

CBitMap* CBitMap_createBitMapGivenSize(Size bitmapSize);
CBitMap* CBitMap_copyBitMap(CBitMap* map);


void CBitMap_SetBit(CBitMap*m ,int bitIndex, bool bitState);
void CBitMap_ClearBit(CBitMap*m);

bool     CBitMap_GetBitState(CBitMap* m, Index index);

#endif //CUTILS_CBITMAP_H
