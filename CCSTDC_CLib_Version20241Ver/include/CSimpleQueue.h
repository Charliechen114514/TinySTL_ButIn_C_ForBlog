#ifndef CUTILS_CSIMPLEQUEUE_H
#define CUTILS_CSIMPLEQUEUE_H
#include "CLibUtility.h"
struct __CDynamicArr;

typedef enum {
    Queue_Static,
    Queue_Dynamic
}QueueSizeConfig;


typedef struct ___SimpleQueue
{
    struct __CDynamicArr* queueCore;
    Size                    size;
    Size                    type_size;
    Size                    capacity;
    QueueSizeConfig         config;
    FILE*                   logger;
}CSimpleQueue;

CSimpleQueue* CSimpleQueue_CreateSimpleQueue(Size init_size,
                                             Size type_size,
                                             QueueSizeConfig config, FILE* f);

CSimpleQueue* CSimpleQueue_CopySimpleQueue(CSimpleQueue* simpleQueue, FILE* f);

bool    CSimpleQueue_enQueue(CSimpleQueue* simpleQueue, void* elem);
void*   CSimpleQueue_deQueue(CSimpleQueue* simpleQueue, bool dontReturn);
bool    CSimpleQueue_isFull(CSimpleQueue* simpleQueue);
bool    CSimpleQueue_isEmpty(CSimpleQueue* simpleQueue);

CSimpleQueue* CSimpleQueue_EraseCSimpleQueue(CSimpleQueue* queue);
bool CSimpleQueue_SetConfig(CSimpleQueue* stack, QueueSizeConfig config);

#endif //CUTILS_CSIMPLEQUEUE_H
