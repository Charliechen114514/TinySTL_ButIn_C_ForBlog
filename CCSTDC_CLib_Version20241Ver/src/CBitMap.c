#include "CBitMap.h"

#define SET_ZERO(bit, bit_pos) 	bit = ( (bit) | (~(1 << (bit_pos))) )
#define SET_ONE(bit, bit_pos)	bit = ( (bit) & (1 << (bit_pos)) )
#define GET_BIT(bits, bit_pos)  (((bits) >> (bit_pos)) & 1)
CBitMap* CBitMap_createBitMapGivenSize(Size bitmapSize)
{
    if(bitmapSize <= 0)
        return NULL;
    CBitMap* m = NULL;
    Malloc(m, CBitMap, 1, NULL);

    NMalloc(m->BitArray, sizeof(unsigned char), (bitmapSize/sizeof(unsigned char) + 1), NULL);

    m->bitmapSize = bitmapSize;

    return m;
}

CBitMap* CBitMap_copyBitMap(CBitMap* map)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(map, NULL, NULL);
    NO_ALLOWED_OPERATE_NULL_CHECK(map->BitArray, NULL, NULL);
    CBitMap* m = NULL;
    Malloc(m, CBitMap, 1, NULL);

    NMalloc(m->BitArray, sizeof(unsigned char), (map->bitmapSize/sizeof(unsigned char) + 1), NULL);

    m->bitmapSize = map->bitmapSize;

    return m;

}

void CBitMap_SetBit(CBitMap* map,int bitIndex, bool bitState)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(map , , NULL);
    NO_ALLOWED_OPERATE_NULL_CHECK(map->BitArray, , NULL);

    if(bitState == true)
    {
        SET_ONE( map->BitArray[bitIndex/sizeof(unsigned char)], (map->bitmapSize - bitIndex % sizeof(unsigned char)) );
    }
    else if(bitState == false)
    {
        SET_ZERO( map->BitArray[bitIndex/sizeof(unsigned char)], (map->bitmapSize - bitIndex % sizeof(unsigned char)) );
    }
}

void CBitMap_ClearBit(CBitMap* map)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(map , , NULL);
    NO_ALLOWED_OPERATE_NULL_CHECK(map->BitArray, , NULL);

    memset(map->BitArray, 0, (map->bitmapSize/sizeof(unsigned char) + 1));
}

bool CBitMap_GetBitState(CBitMap* map, Index bitIndex)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(map ,false , NULL);
    NO_ALLOWED_OPERATE_NULL_CHECK(map->BitArray, false, NULL);

    return (bool)GET_BIT(map->BitArray[bitIndex/sizeof(unsigned char)], (map->bitmapSize - bitIndex % sizeof(unsigned char)));
}