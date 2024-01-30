#include "CAlgorithm.h"
#include "string.h"
typedef char Byte;
#define ThisElem(elem)       (elem)
#define NextElem(elem, size) (elem + size)
#define PrevElem(elem, size) (elem - size)
#define ToNext(elem, size)   elem += size
#define ToPrev(elem, size)   elem -= size
bool private_isUpper(char a){
    return (bool)(a >= 'A' && a <= 'Z');
}

bool private_isLower(char a){
    return (bool)(a >= 'a' && a <= 'z');
}

int private_getIntSize(int num)
{
    if(num == 0)
        return 1;
    int s = 0;
    while(num != 0){
        num /= 10;
        s++;
    }
    return s;
}

char private_getEachIndexNum(int num, Index i)
{
    if(i < 0)
        return 0;
    if(i == 0)
        return '0';
    while(i > 0){
        num /= 10;
        i--;
    }

    return (char)(num % 10+ '0');
}

void CAlg_SwapBufOnce(void* buf1, void* buf2, Size elemSize)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(buf1,,NULL);
    NO_ALLOWED_OPERATE_NULL_CHECK(buf2,,NULL);
    char* tmpBuf = NULL;
    NMalloc(tmpBuf, sizeof(char), elemSize, NULL);
    memcpy(tmpBuf, buf1, elemSize);

    memcpy(buf1, buf2, elemSize);
    memcpy(buf2, tmpBuf, elemSize);
    SafeFree(tmpBuf, NULL);
}

void CAlg_SwapBuf(void* buf1, void* buf2, void* tmpBuf, Size elemSize)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(buf1,,NULL);
    NO_ALLOWED_OPERATE_NULL_CHECK(buf2,,NULL);
    NO_ALLOWED_OPERATE_NULL_CHECK(tmpBuf,, NULL);
    memcpy(tmpBuf, buf1, elemSize);
    memcpy(buf1, buf2, elemSize);
    memcpy(buf2, tmpBuf, elemSize);
}

void CAlg_BubbleSort(void* begin, Size numSize, Size elemSize, CompareFunc f)
{
   Byte* end = (Byte*)begin + (numSize - 1)* elemSize;
    if((Byte*)begin >= end)
        return;

    NO_ALLOWED_OPERATE_NULL_CHECK(begin,,NULL);
    NO_ALLOWED_OPERATE_NULL_CHECK(end,,NULL);
    char* tmpBuf = NULL;
    NMalloc(tmpBuf, sizeof(char), elemSize, NULL);
    int fin = 0;
    for(Byte* current = begin; current < (Byte*)end; current += elemSize, fin++)
    {
        for(Byte* thisRoutine = begin; thisRoutine < (Byte*)end - fin * elemSize; thisRoutine += elemSize)
        {
            if(f(thisRoutine, thisRoutine + elemSize) == BIGGER)
            {
                CAlg_SwapBuf(thisRoutine, thisRoutine + elemSize,
                             tmpBuf, elemSize);
            }
        }
    }

    SafeFree(tmpBuf ,NULL);
}

bool CAlg_isCharNum(const char* numString, int how_much)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(numString, false, NULL);

    if(how_much == -1)
        how_much = (int)strlen(numString);

    if(how_much > strlen(numString))
        return false;


    int i = 0;
    while(*numString++ != '\0' && i <= how_much)
    {
        if(*numString <= '0' || *numString >= '9')
            return false;
    }

    return true;
}

bool CAlg_isUpperAlphaBit(const char* numString, int how_much)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(numString, false, NULL);

    if(how_much == -1)
        how_much = (int)strlen(numString);

    if(how_much > strlen(numString))
        return false;


    int i = 0;
    while(*numString++ != '\0' && i <= how_much)
    {
        if(*numString <= 'A' || *numString >= 'Z')
            return false;
    }

    return true;
}
bool CAlg_isLowerAlphaBit(const char* numString, int how_much)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(numString, false, NULL);
    if(how_much == -1)
        how_much = (int)strlen(numString);

    if(how_much > strlen(numString))
        return false;



    int i = 0;
    while(*numString++ != '\0' && i <= how_much)
    {
        if(*numString <= 'a' || *numString >= 'z')
            return false;
    }

    return true;
}

bool CAlg_isCharAlphaBet(const char* numString, int how_much)
{
    return (bool)(CAlg_isLowerAlphaBit(numString, how_much) || CAlg_isUpperAlphaBit(numString, how_much));
}

char* CAlg_ToUpperChar(const char* numString, int how_much)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(numString, false, NULL);
    if(how_much == -1)
        how_much = (int)strlen(numString);

    if(how_much > strlen(numString))
        return false;

    char* newStr = NULL;
    Malloc(newStr, char, how_much, NULL);

    int i = 0;
    while(*numString != '\0' && i <= how_much)
    {
        if(private_isLower(*numString))
            newStr[i] = (*numString) - ((char)'a' - (char)'A');
        else
            newStr[i] = (*numString);
        i++;
        numString++;
    }
    return newStr;
}

char* CAlg_ToLowerChar(const char* numString, int how_much)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(numString, false, NULL);
    if(how_much == -1)
        how_much = (int)strlen(numString);

    if(how_much > strlen(numString))
        return false;



    char* newStr = NULL;
    Malloc(newStr, char, how_much, NULL);

    int i = 0;
    while(*numString != '\0' && i <= how_much)
    {
        if(private_isUpper(*numString))
            newStr[i] = (*numString) + ((char)'a' - (char)'A');
        else
            newStr[i] = (*numString);
        i++;
        numString++;
    }
    return newStr;
}

char* CAlg_FromInt2Char(int num)
{
    int newStrSize = 0;
    if(num < 0) {
        newStrSize = 1; // for the -
    }
    int numSize = private_getIntSize(num);
    newStrSize += numSize;
    char* newStr = NULL;
    Malloc(newStr, char, (newStrSize + 1), NULL);
    if(num >= 0)
    {
        for (int cur = numSize - 1 , i = 0; cur >= 0; cur--, i++)
            newStr[i] = private_getEachIndexNum(num, cur);
    }
    else
    {
        num = abs(num);
        newStr[0] = '-';
        for (int cur = numSize - 1, i = 1; cur >= 0; cur--, i++)
            newStr[i] = private_getEachIndexNum(num, cur);
    }
    newStr[newStrSize] = '\0';
    return newStr;
}

char* CAlg_FromDouble2Char(double num, int percision)
{
    if(percision <= 0)
        return NULL;
    char* tmp = NULL;
    Malloc(tmp, char, percision + 1, NULL);
    sprintf(tmp, "%.12f", num);
    return tmp;
}