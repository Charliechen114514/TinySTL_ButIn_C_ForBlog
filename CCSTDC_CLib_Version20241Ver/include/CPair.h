#ifndef CUTILS_CPAIR_H
#define CUTILS_CPAIR_H
#include "CLibUtility.h"

typedef struct ___Pair
{
    void* first;
    void* second;

    Size first_size;
    Size second_size;

    FILE* logger;
}CPair;

CPair*  CPair_CreateCPair(void* elem1, void* elem2, Size first_size, Size second_size, FILE* logger);
CPair*  CPair_CopyCPair(CPair* pair, FILE* logger);
void*   CPair_GetFirst(CPair* pair, bool isInterFace);
void*   CPair_GetSecond(CPair* pair, bool isInterFace);
CPair*  CPair_EraseCPair(CPair* pair);


#endif //CUTILS_CPAIR_H
