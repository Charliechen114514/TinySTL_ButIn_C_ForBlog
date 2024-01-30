//
// Created by ³Â¹ÚºÀ on 2024/1/22.
//

#include "CSimpleQueue.h"

#include "CDynamicArray.h"
#include "CLibLog.h"
#include "CLibUtility.h"
#include "CUtilsContainerLogStr.h"

bool QueueConfigAdapter(QueueSizeConfig c)
{
    if(c == Queue_Static)
        return false;
    else
        return true;
}

CSimpleQueue* CSimpleQueue_CreateSimpleQueue(Size init_size, Size type_size, QueueSizeConfig config, FILE* f)
{
    CSimpleQueue* stack = NULL;
    Malloc(stack, CSimpleQueue, 1, f);

    CODE_MSG_FORMAT(
            f,
            (QueueConfigAdapter(config) ? Create_A_Stack_As_Dynamic_STR : Create_A_Stack_As_Static_STR),
            Info, true
    );

    stack->queueCore = CDynamicArray_CreateCDynamicArr(type_size, init_size, f);
    stack->size = 0;
    stack->type_size = type_size;
    stack->logger = f;
    stack->config = config;
    stack->capacity = init_size;

    return stack;
}

CSimpleQueue* CSimpleQueue_CopySimpleQueue(CSimpleQueue* stack, FILE* f)
{
    CSimpleQueue* other_stack = NULL;
    Malloc(other_stack, CSimpleQueue, 1, f);

    CODE_MSG_FORMAT(f,Copy_A_Stack,Info, true);

    other_stack->queueCore = CDynamicArray_CopyCDynamicArr(stack->queueCore, f);
    other_stack->config = stack->config;
    other_stack->logger = f;
    other_stack->type_size = stack->type_size;
    other_stack->size = stack->size;
    other_stack->capacity = stack->capacity;
    return other_stack;
}

bool CSimpleQueue_isFull(CSimpleQueue* stack)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(stack, false, stderr);
    return stack->size >= stack->capacity && !QueueConfigAdapter(stack->config);
}

bool CSimpleQueue_isEmpty(CSimpleQueue* simpleQueue)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(simpleQueue, false, stderr);
    return simpleQueue->size == 0;
}

bool CSimpleQueue_enQueue(CSimpleQueue* stack, void* elem)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(stack, false, stderr);

    CODE_MSG_FORMAT(stack->logger, PUSH_BACK_STR, Info, true);

    if(CSimpleQueue_isFull(stack)) {
        CODE_MSG_FORMAT(stack->logger, STACK_FULL_STR, Warning, false);
        return false;
    }

    CDynamicArray_PushFront(stack->queueCore, elem);

    stack->size++;

    return true;
}

void* CSimpleQueue_deQueue(CSimpleQueue* simpleQueue, bool dontReturn)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(simpleQueue, false, stderr);

    CODE_MSG_FORMAT(simpleQueue->logger, POP_BACK_STR, Info, true);

    if(CSimpleQueue_isEmpty(simpleQueue)) {
        CODE_MSG_FORMAT(simpleQueue->logger, STACK_IS_EMPTY, Warning, false);
        return false;
    }

    simpleQueue->size--;

    return CDynamicArray_PopBack(simpleQueue->queueCore, dontReturn);
}

bool CSimpleQueue_SetConfig(CSimpleQueue* stack, QueueSizeConfig config)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(stack, false, stderr);
    if(config == stack->config)
        return false;

    stack->config = config;

    return true;
}

CSimpleQueue* CSimpleQueue_EraseCSimpleQueue(CSimpleQueue* queue)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(queue, false, stderr);
    FILE *p = queue->logger;

    CDynamicArray_Erase(queue->queueCore);

    SafeFree(queue, p);

    CODE_MSG_FORMAT(p, "Erase SimpleQueue!\n", Info, true);

    return queue;
}