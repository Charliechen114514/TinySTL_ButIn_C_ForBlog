#ifndef CUTILS_CUTILSTRING_H
#define CUTILS_CUTILSTRING_H
#include "CLibUtility.h"


#ifndef USE_LIB
#define USE_RAW
#else
#define USE_RAW
#endif


typedef struct ___String
{
    Size            string_size;
    char*           core;
    FILE*           l;
}CUtilString;

CUtilString*    CUtilString_createCUtilString(const char* raw_string, FILE* l);
CUtilString*    CUtilString_copyCString(CUtilString* str, FILE* l);
CUtilString*    CUtilString_fromInt(int size ,FILE* l);
CUtilString*    CUtilString_fromDouble(double size, int percision, FILE* l);
CUtilString*    CUtilString_concat(CUtilString* appendee, CUtilString* appender, bool need_release);
CUtilString*    CUtilString_concatRaw(CUtilString* appendee, const char* appender);
CUtilString*    CUtilString_split(CUtilString* str, Index index);
Size            CUtilString_strlen(CUtilString* str);
const char*     CUtilString_getRaw(CUtilString* str);
CUtilString*    CUtilString_Erase(CUtilString* str);

CUtilString*    CUtilString_ToUpper(CUtilString* str);
CUtilString*    CUtilString_ToLower(CUtilString* str);


#endif //CUTILS_CUTILSTRING_H
