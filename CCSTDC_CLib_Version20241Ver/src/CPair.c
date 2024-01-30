#include "CPair.h"
#include "CLibLog.h"
#include "CUtilsContainerLogStr.h"

CPair*  CPair_CreateCPair(void* elem1, void* elem2, Size first_size, Size second_size, FILE* logger)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(elem1, NULL, logger);
    NO_ALLOWED_OPERATE_NULL_CHECK(elem2, NULL, logger);
    CODE_MSG_FORMAT(logger, Create_A_Pair_STR, Info, true);
    CPair* pair = NULL;
    Malloc(pair, CPair, 1, logger);
    void* data1 = NULL;
    void* data2 = NULL;

    NMalloc(data1, sizeof(char), first_size, logger);
    NMalloc(data2, sizeof(char), second_size, logger);

    memcpy(data1, elem1, first_size);
    memcpy(data2, elem2, second_size);

    pair->first_size = first_size;
    pair->second_size = second_size;
    pair->first = data1;
    pair->second = data2;
    pair->logger = logger;
    CODE_MSG_FORMAT(logger, OPERATE_SUCCESS, Info, true);
    return pair;
}

CPair*  CPair_CopyCPair(CPair* pair, FILE* logger)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(pair, NULL, logger);
    CODE_MSG_FORMAT(logger, Copy_A_Pair_STR, Info, true);
    CPair* other_pair = NULL;
    Malloc(other_pair, CPair, 1, logger);
    void* data1 = NULL;
    void* data2 = NULL;

    NMalloc(data1, sizeof(char), pair->first_size, logger);
    NMalloc(data2, sizeof(char), pair->second_size, logger);

    memcpy(data1, pair->first, pair->first_size);
    memcpy(data2, pair->second, pair->second_size);

    other_pair->first_size = pair->first_size;
    other_pair->second_size = pair->second_size;
    other_pair->first = data1;
    other_pair->second = data2;
    other_pair->logger = logger;

    return other_pair;
}

void* CPair_GetFirst(CPair* pair, bool isInterFace)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(pair, NULL, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(pair->first, NULL, pair->logger);
    if(isInterFace)
    {
        return pair->first;
    }
    else
    {
        void* data1 = NULL;
        NMalloc(data1, sizeof(char), pair->first_size, pair->logger);
        memcpy(data1, pair->first, pair->first_size);
        return data1;
    }
}

void*   CPair_GetSecond(CPair* pair, bool isInterFace)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(pair, NULL, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(pair->second, NULL, pair->logger);
    if(isInterFace)
    {
        return pair->second;
    }
    else
    {
        void* data1 = NULL;
        NMalloc(data1, sizeof(char), pair->second_size, pair->logger);
        memcpy(data1, pair->second, pair->second_size);
        return data1;
    }
}

CPair*  CPair_EraseCPair(CPair* pair)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(pair, NULL, stderr);
    FILE* p = pair->logger;
    SafeFree(pair->first, p);
    CODE_MSG_FORMAT(p, "Successfully free the pair first\n", Info, true);
    SafeFree(pair->second, p);
    CODE_MSG_FORMAT(p, "Successfully free the pair second\n", Info, false);
    SafeFree(pair, p);
    CODE_MSG_FORMAT(p, "Successfully free the pair\n", Info, false);
    return pair;
}