//
// Created by ³Â¹ÚºÀ on 2024/1/22.
//

#ifndef CUTILS_CDRLINKLIST_H
#define CUTILS_CDRLINKLIST_H

#include "CLibUtility.h"

typedef struct ___LinkNode
{
    void* elem;
    Size  elem_Size;
    struct ___LinkNode* next;
    struct ___LinkNode* prev;
    FILE*  logger;
}CLinkNode;

CLinkNode* CDRLinkList_CreateCLinkNode(void* elem, Size elem_Size, FILE* logger);
CLinkNode* CDRLinkList_CopyCLinkNode(CLinkNode* node, FILE* logger);
CLinkNode* CDRLinkList_EraseCLinkNode(CLinkNode* node);
CLinkNode* CDRLinkList_GetNext(CLinkNode* node);
CLinkNode* CDRLinkList_GetPrev(CLinkNode* node);
bool       CDRLinkList_HasNext(CLinkNode* node);
bool       CDRLinkList_HasPrev(CLinkNode* node);
void*      CDRLinkList_GetElem(CLinkNode* node);
CLinkNode* CDRLinkList_setNext(CLinkNode* node, CLinkNode* insert_node);
CLinkNode* CDRLinkList_setNextEx(CLinkNode* node, void* elem, Size elem_Size, FILE* logger);
CLinkNode* CDRLinkList_setPrev(CLinkNode* node, CLinkNode* insert_node);
CLinkNode* CDRLinkList_setPrevEx(CLinkNode* node, void* elem, Size elem_Size, FILE* logger);

typedef struct ___LinkList
{
    Size listSize;
    CLinkNode* head;
    CLinkNode* tail;
    FILE*  logger;
}CLinkList;

CLinkList*  CDRLinkList_CreateEmptyCLinkList(FILE* logger);
CLinkList*  CDRLinkList_CopyCDRLinkList(CLinkList* list, FILE* logger);
bool        CDRLinkList_IsListEmpty(CLinkList* list);
bool        CDRLinkList_PushBack(CLinkList* list, CLinkNode* node);
bool        CDRLinkList_PushBackEx(CLinkList* list, void* elem, Size elem_Size, FILE* logger);
bool        CDRLinkList_PushFront(CLinkList* list, CLinkNode* node);
bool        CDRLinkList_PushFrontEx(CLinkList* list, void* elem, Size elem_Size, FILE* logger);
CLinkNode*  CDRLinkList_PopBack(CLinkList* list, bool need_free_auto);
CLinkNode*  CDRLinkList_PopFront(CLinkList* list, bool need_free_auto);

void*       CDRLinkList_At(CLinkList* list, Index index);

bool        CDRLinkList_Insert(CLinkList* list, CLinkNode* node, Index index);
bool        CDRLinkList_InsertEx(CLinkList* list, Index index, void* elem, Size elem_Size, FILE* logger);
CLinkNode*  CDRLinkList_EraseElem(CLinkList* list, Index index, bool need_free_auto);

Size        CDRLinkList_GetSize(CLinkList* list);
CLinkNode*  CDRLinkList_GetHead(CLinkList* list);
CLinkNode*  CDRLinkList_GetTail(CLinkList* list);
CLinkList*  CDRLinkList_Erase(CLinkList* list);
#endif //CUTILS_CDRLINKLIST_H
