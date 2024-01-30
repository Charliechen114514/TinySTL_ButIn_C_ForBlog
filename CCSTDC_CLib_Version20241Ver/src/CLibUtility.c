#include "CLibUtility.h"
bool compInt(const int* a,const int* b)
{
    return *a > *b ? BIGGER:SMALL;
}

bool compDouble(const double* a, const double* b)
{
    return *a > *b ? BIGGER:SMALL;
}

bool compChar(const char* a, const char* b)
{
    return *a > *b ? BIGGER:SMALL;
}
