#include "CStack.h"
#include "CDynamicArray.h"
#include "CLibLog.h"
#include "CLibUtility.h"
#include "CUtilsContainerLogStr.h"

bool StackConfigAdapter(StackSizeConfig c)
{
    if(c == Stack_STATIC)
        return false;
    else
        return true;
}

CStack* CStack_Init(Size init_size, Size type_size, StackSizeConfig config, FILE* f)
{
    CStack* stack = NULL;
    Malloc(stack, CStack, 1, f);

    CODE_MSG_FORMAT(
            f,
            (StackConfigAdapter(config) ? Create_A_Stack_As_Dynamic_STR : Create_A_Stack_As_Static_STR),
            Info, true
            );

    stack->array = CDynamicArray_CreateCDynamicArr(type_size, init_size, f);
    stack->size = 0;
    stack->type_size = type_size;
    stack->logger = f;
    stack->config = config;
    stack->capacity = init_size;

    return stack;
}

CStack* CStack_Copy(CStack* stack, FILE* f)
{
    CStack* other_stack = NULL;
    Malloc(other_stack, CStack, 1, f);

    CODE_MSG_FORMAT(f,Copy_A_Stack,Info, true);

    other_stack->array = CDynamicArray_CopyCDynamicArr(stack->array, f);
    other_stack->config = stack->config;
    other_stack->logger = f;
    other_stack->type_size = stack->type_size;
    other_stack->size = stack->size;
    other_stack->capacity = stack->capacity;
    return other_stack;
}

bool CStack_IsFull(CStack* stack)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(stack, false, stderr);
    return stack->size >= stack->capacity && !StackConfigAdapter(stack->config);
}

bool CStack_IsEmpty(CStack* stack)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(stack, false, stderr);
    return stack->size == 0;
}

bool CStack_PushBack(CStack* stack, void* elem)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(stack, false, stderr);

    CODE_MSG_FORMAT(stack->logger, PUSH_BACK_STR, Info, true);

    if(CStack_IsFull(stack)) {
        CODE_MSG_FORMAT(stack->logger, STACK_FULL_STR, Warning, false);
        return false;
    }

    CDynamicArray_PushBack(stack->array, elem);

    stack->size++;

    return true;
}

void* CStack_PopBack(CStack* stack, bool need_erase)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(stack, false, stderr);

    CODE_MSG_FORMAT(stack->logger, POP_BACK_STR, Info, true);

    if(CStack_IsEmpty(stack)) {
        CODE_MSG_FORMAT(stack->logger, STACK_IS_EMPTY, Warning, false);
        return false;
    }

    stack->size--;

    return CDynamicArray_PopBack(stack->array, need_erase);
}

bool CStack_SetConfig(CStack* stack, StackSizeConfig config)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(stack, false, stderr);
    if(config == stack->config)
        return false;

    stack->config = config;

    return true;
}

CStack* CStack_Erase(CStack* stack)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(stack, false, stderr);
    FILE* p = stack->logger;

    CDynamicArray_Erase(stack->array);

    SafeFree(stack, p);

    CODE_MSG_FORMAT(p, "Erase Stack!\n", Info, true);

    return stack;
}