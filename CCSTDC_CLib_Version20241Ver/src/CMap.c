#include "CMap.h"
#include "CDRLinkList.h"
#include "CLibLog.h"
#include "CUtilsContainerLogStr.h"
#include "CPair.h"

CLinkNode* private_findTargetKey(CLinkList* l, void* value, CompareFunc f, int* index)
{
    if(l->listSize == 0)
        return NULL;
    int idx = 0;
    // as is private, no need to check validity
    for(CLinkNode* privateNode = l->head;
        privateNode != l->tail;
        privateNode = CDRLinkList_GetNext(privateNode), idx++)
    {
        CPair* pair = (CPair*)(privateNode->elem);
        void* nodeValue = pair->second;
        if(f(nodeValue, value) == EQUAL) {
            if(index)
                *index = idx;
            return privateNode;
        }
    }

    // specially check the last one
    CPair* pair = (CPair*)(l->tail->elem);
    void* nodeValue = pair->second;
    if(f(nodeValue, value) == EQUAL) {
        if(index) *index = idx;
        return l->tail;
    }
    else
    {
        if(index) *index = -1;
        return NULL;
    }
}

CLinkNode* private_findTarget(CLinkList* l, void* key, CompareFunc f, int* index)
{
    if(l->listSize == 0)
        return NULL;
    int idx = 0;
    // as is private, no need to check validity
    for(CLinkNode* privateNode = l->head;
        privateNode != l->tail;
        privateNode = CDRLinkList_GetNext(privateNode), idx++)
    {
        CPair* pair = (CPair*)(privateNode->elem);
        void* nodeKey = pair->first;
        if(f(nodeKey, key) == EQUAL) {
            if(index)
                *index = idx;
            return privateNode;
        }
    }

    // specially check the last one
    CPair* pair = (CPair*)(l->tail->elem);
    void* nodeKey = pair->first;
    if(f(nodeKey, key) == EQUAL) {
        if(index) *index = idx;
        return l->tail;
    }
    else
    {
        if(index) *index = -1;
        return NULL;
    }
}

int private_findTargetSuitNode(CLinkList* l, void* key, CompareFunc f)
{
    if(l->listSize == 0)
        return 0;
    int indexFound = 0;
    for(CLinkNode* privateNode = l->head;
        privateNode != l->tail;
        privateNode = CDRLinkList_GetNext(privateNode), indexFound++)
    {
        CPair* pair = (CPair*)(privateNode->elem);
        void* nodeKey = pair->first;
        if(f(nodeKey, key) == BIGGER)
            return indexFound;
    }
    CPair* fin = (CPair*)(l->tail->elem);
    if(f(fin->first, key) == BIGGER)
        return indexFound;

    return indexFound + 1;
}

CLinearMap* CLinearMap_CreateAEmptyCMap(FILE* logger, CompareFunc func)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(func, NULL, logger);
    CLinearMap* map = NULL;
    CODE_MSG_FORMAT(logger, Create_A_LinearMap_STR, Info, true);

    Malloc(map, CLinearMap, 1, logger);

    map->logger = logger;
    map->mapActually = NULL;
    map->compFunc = func;
    CODE_MSG_FORMAT(logger, OPERATE_SUCCESS, Info, true);
    return map;
}

void* CLinearMap_Key(CLinearMap* map, void* value, CompareFunc val_func)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(map, NULL, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(value, NULL, map->logger);

    CPair* p = (CPair*)private_findTarget(map->mapActually, value, val_func, NULL);
    if(!p)
        return NULL;
    else
    {
        void* data = NULL;
        NMalloc(data, sizeof(char), p->first_size, map->logger);
        memcpy(data, p->first, p->first_size);
        return data;
    }
}

void* CLinearMap_Value(CLinearMap* map, void* key)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(map, NULL, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(key, NULL, map->logger);

    CLinkNode* _p = (CLinkNode*)private_findTarget(map->mapActually, key, map->compFunc, NULL);
    if(!_p)
        return NULL;
    else
    {
        CPair* p = (CPair*)_p->elem;
        void* data = NULL;
        NMalloc(data, sizeof(char), p->second_size, map->logger);
        memcpy(data, p->second, p->second_size);
        return data;
    }
}


CLinearMap* CLinearMap_CopyACLinearMap(CLinearMap* map, FILE* logger)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(map->compFunc, NULL, logger);
    CLinearMap* other_map = NULL;
    CODE_MSG_FORMAT(logger, Copy_A__LinearMap_STR, Info, true);

    Malloc(other_map, CLinearMap, 1, logger);

    other_map->logger = logger;
    other_map->compFunc = map->compFunc;
    other_map->mapActually = CDRLinkList_CopyCDRLinkList(map->mapActually, logger);

    return other_map;
}

bool CLinearMap_ContainsKey(CLinearMap* map, void* key)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(map, false, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(key, false, map->logger);
    if(!map->mapActually){
        return false;
    }
    return !private_findTarget(map->mapActually, key, map->compFunc, NULL);
}

bool CLinearMap_InsertAKey_Value_Pair(CLinearMap* map, void* key, Size key_size,
                                                 void* value, Size value_size)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(map, false, stderr);
    if(!map->mapActually){
        map->mapActually = CDRLinkList_CreateEmptyCLinkList(NULL);
    }

    CLinkNode* key_value_node = private_findTarget(map->mapActually, key, map->compFunc, NULL);
    // find if the key is duplicated
    if(!key_value_node)
    {
        CPair* key_value_pair =  CPair_CreateCPair(key, value, key_size, value_size, map->logger);
        int insertIndex = private_findTargetSuitNode(map->mapActually, key, map->compFunc);
        if(insertIndex == -1)
        {
            CPair_EraseCPair(key_value_pair);
            return false;
        }
        CDRLinkList_InsertEx(map->mapActually, insertIndex, key_value_pair, sizeof(CPair), map->logger);
        return true;
    }
    else
    {
        CPair* key_value_pair = (CPair*)key_value_node->elem;
        SafeFree(key_value_pair->second, map->logger);
        NMalloc(key_value_pair->second, sizeof(char),value_size, key_value_pair->logger);
        memcpy(key_value_pair->second, value, value_size);
    }
    return false;
}

bool CLinearMap_PopPairOfKeyValue(CLinearMap* map, void* key)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(map, false, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(key, false, map->logger);
    int index;
    private_findTarget(map->mapActually, key, map->compFunc, &index);
    if(index == -1)
    {
        return false;
    }
    else
    {
        CDRLinkList_EraseElem(map->mapActually, index, true);
    }

    return true;
}

CLinearMap* CLinearMap_EraseMap(CLinearMap* map)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(map, NULL, stderr);
    FILE* p = map->logger;
    CDRLinkList_Erase(map->mapActually);
    CODE_MSG_FORMAT(p, "Successfully free the core", Info, true);
    SafeFree(map, p);
    CODE_MSG_FORMAT(p, "Successfully free the map", Info, true);
    return map;
}