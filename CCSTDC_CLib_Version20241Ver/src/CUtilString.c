#include "CUtilString.h"
#include "CLibLog.h"
#include "CUtilsContainerLogStr.h"
#include "string.h"
#ifdef USE_RAW
#define StringLength    strlen
#define StringCompare   strcmp
#else
Size StringLength(const char* str)
{
    Size cnt = 0;
    while(*str++ != '\0') cnt++;
    return cnt;
}

Compare_State StringCompare(const char* c1, const char* c2)
{
    while(*c1 != '\0' && *c2 != '\0' && *c1 == *c2){
        c1++;c2++;
    }
    return (*c1 > *c2) - (*c2 > *c1);
}
#endif
char* partialCopy(const char* src, Index beg, Index end, Index limitSize)
{
    if(end > limitSize)
        end = limitSize;
    int realIndex = end - beg + 1;

    char* dst = NULL;
    NMalloc(dst, sizeof(char), realIndex, NULL);
    memcpy(dst, src + beg, realIndex);
    *(dst + realIndex) = '\0';
    return dst;
}


CUtilString* CUtilString_createCUtilString(const char* raw_string, FILE* l)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(raw_string, NULL, l);
    CUtilString* str = NULL;
    Malloc(str, CUtilString, 1, l);
    str->l = l;

    str->string_size = StringLength(raw_string) + 1;
    NMalloc(str->core, sizeof(char), str->string_size, l);
    memcpy(str->core, raw_string, str->string_size);
    *(str->core + str->string_size) = '\0';
    return str;
}

CUtilString*    CUtilString_copyCString(CUtilString* _str, FILE* l)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(_str, NULL, l);
    CUtilString* str = NULL;
    Malloc(str, CUtilString, 1, l);
    str->l = l;

    str->string_size = _str->string_size;
    NMalloc(str->core, sizeof(char), str->string_size, l);
    memcpy(str->core, _str->core, str->string_size);
    *(str->core + str->string_size) = '\0';
    return str;
}

CUtilString* CUtilString_concat(CUtilString* appendee, CUtilString* appender, bool need_release)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(appendee, NULL, appendee->l);
    NO_ALLOWED_OPERATE_NULL_CHECK(appender, NULL, appendee->l);
    Realloc(appendee->core, sizeof(char), appender->string_size + appendee->string_size - 1, appendee->l);
    memcpy(appendee->core + appendee->string_size, appender->core, appender->string_size);
    appendee->string_size += appender->string_size - 1;
    *(appendee->core + appendee->string_size) = '\0';
    if(need_release)
        CUtilString_Erase(appender);
    return appendee;
}

CUtilString* CUtilString_concatRaw(CUtilString* appendee, const char* appender)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(appendee, NULL, appendee->l);
    NO_ALLOWED_OPERATE_NULL_CHECK(appender, NULL, appendee->l);
    Size s = StringLength(appender);
    Realloc(appendee->core, sizeof(char), s + appendee->string_size + 1, appendee->l);
    memcpy(appendee->core + appendee->string_size - 1, appender, s);
    appendee->string_size += s;
    *(appendee->core + appendee->string_size) = '\0';
    return appendee;
}

CUtilString* CUtilString_split(CUtilString* str, Index index)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(str, NULL, str->l);
    NO_ALLOWED_OPERATE_NULL_CHECK(str->core, NULL, str->l);
    CUtilString* p1 = NULL;
    Malloc(p1, CUtilString, 1,str->l);
    p1->l = str->l;

    p1->core = partialCopy(str->core, index, str->string_size, str->string_size);
    p1->string_size = str->string_size - index;
    *(p1->core + p1->string_size) = '\0';

    Realloc(str->core, sizeof(char), index, str->l);
    str->string_size = index;
    *(str->core + str->string_size) = '\0';
    return p1;
}

Size CUtilString_strlen(CUtilString* str)
{
    return str->string_size;
}

const char* CUtilString_getRaw(CUtilString* str)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(str, NULL, str->l);
    NO_ALLOWED_OPERATE_NULL_CHECK(str->core, NULL, str->l);
    return partialCopy(str->core, 0, str->string_size, str->string_size);
}

CUtilString* CUtilString_Erase(CUtilString* str)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(str, NULL, str->l);
    FILE* p = str->l;
    SafeFree(str->core, p);
    CODE_MSG_FORMAT(p, "Safe free the core string\n", Info, true);
    SafeFree(str, p);
    CODE_MSG_FORMAT(p, "Safe free the string\n", Info, false);
    return str;
}

#include "CAlgorithm.h"

CUtilString* CUtilString_ToUpper(CUtilString* str)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(str, NULL, str->l);
    NO_ALLOWED_OPERATE_NULL_CHECK(str->core, NULL, str->l);

    const char* tmp = CAlg_ToUpperChar(str->core, -1);

    CUtilString_createCUtilString(tmp, str->l);

    SafeFree(tmp, NULL);
}

CUtilString* CUtilString_ToLower(CUtilString* str)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(str, NULL, str->l);
    NO_ALLOWED_OPERATE_NULL_CHECK(str->core, NULL, str->l);

    const char* tmp = CAlg_ToLowerChar(str->core, -1);

    CUtilString_createCUtilString(tmp, str->l);

    SafeFree(tmp, NULL);
}

CUtilString*    CUtilString_fromInt(int size,FILE* l)
{
    const char* tmp = CAlg_FromInt2Char(size);
    CUtilString* s = CUtilString_createCUtilString(tmp, l);
    SafeFree(tmp, NULL);
    return s;
}
CUtilString*    CUtilString_fromDouble(double size, int percision,FILE* l)
{
    const char* tmp = CAlg_FromDouble2Char(size, percision);
    CUtilString* s = CUtilString_createCUtilString(tmp, l);
    SafeFree(tmp, NULL);
    return s;
}