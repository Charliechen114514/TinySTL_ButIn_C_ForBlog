#ifndef CUTILS_CLIBLOG_H
#define CUTILS_CLIBLOG_H
#include <stdio.h>

enum Info_Level{
    Info,
    Warning,
    Error
};

#define CLOSE_LOG   NULL

#define CODE_MSG_RELATED \
"\n****************************************************************\n\
In the file:> %s\n\
In the line:> %d\n\
In the function:> %s\n\
In the time:> %s %s\n\
****************************************************************\n", \
 __FILE__, __LINE__, __FUNCTION__, __DATE__, __TIME__\

// generate as __FILE__, __LINE__, __FUNCTION__, __DATE__, __TIME__
#define CODE_MSG_FORMAT_STD(MSG, info_level, required_info) \
do{\
    switch(info_level)              \
    {                               \
        case Error:                 \
            CODE_MSG_FORMAT(stderr, MSG, info_level, required_info);break;\
        case Info:                  \
        case Warning:               \
        default:\
            CODE_MSG_FORMAT(stdout, MSG, info_level, required_info);break;\
    }                                    \
}while(0)

#define CODE_MSG_FORMAT(FilePlace, MSG, info_level, required_info) \
do{                                                 \
    if(!FilePlace)                                  \
        break;\
    switch(info_level)              \
    {                               \
        case Info:                       \
            if((required_info))fprintf(FilePlace, CODE_MSG_RELATED);\
            fprintf(FilePlace, "\n[Info]:> %s\n", MSG);  break;\
        case Warning:                                     \
            if((required_info))fprintf(FilePlace, CODE_MSG_RELATED);\
            fprintf(FilePlace, "\n[Warning]:> %s\n", MSG); break; \
        case Error:                      \
            if((required_info))fprintf(FilePlace, CODE_MSG_RELATED); \
            fprintf(FilePlace, "\n[Error]:> %s\n", MSG);break;  \
        default:  \
            if((required_info))fprintf(FilePlace, CODE_MSG_RELATED);\
            fprintf(FilePlace, "\n[Unknown state]:> %s\n", MSG);break;\
    }                                    \
}while(0)

#define CODE_MSG_FORMAT_Self_def(FilePlace, OP, info_level, required_info) \
do{                                                 \
    if(!FilePlace)                                  \
        break;\
    switch(info_level)              \
    {                               \
        case Info:                       \
            if((required_info))fprintf(FilePlace, CODE_MSG_RELATED);\
            OP;break;\
        case Warning:                                     \
            if((required_info))fprintf(FilePlace, CODE_MSG_RELATED);\
            OP;break;\
        case Error:                      \
            if((required_info))fprintf(FilePlace, CODE_MSG_RELATED); \
            OP;break;\
        default:  \
            if((required_info))fprintf(FilePlace, CODE_MSG_RELATED);\
            OP;break;\
    }\
}while(0)


#endif //CUTILS_CLIBLOG_H
