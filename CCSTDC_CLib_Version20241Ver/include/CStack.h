//
// Created by ³Â¹ÚºÀ on 2024/1/22.
//

#ifndef CUTILS_CSTACK_H
#define CUTILS_CSTACK_H
#include "CLibUtility.h"

struct __CDynamicArr;

typedef enum{
    Stack_STATIC,
    Stack_DYNAMIC
}StackSizeConfig;

typedef struct ___Stack
{
    struct __CDynamicArr*   array;
    Size                    size;
    Size                    type_size;
    Size                    capacity;
    StackSizeConfig         config;
    FILE*                   logger;

}CStack;



CStack* CStack_Init(Size init_size, Size type_size, StackSizeConfig config, FILE* f);
CStack* CStack_Copy(CStack* stack, FILE* f);
bool    CStack_PushBack(CStack* stack, void* elem);
void*   CStack_PopBack(CStack* stack, bool need_erase);
CStack* CStack_Erase(CStack* stack);
bool    CStack_IsFull(CStack* stack);
bool    CStack_IsEmpty(CStack* stack);
bool    CStack_SetConfig(CStack* stack, StackSizeConfig config);





#endif //CUTILS_CSTACK_H
