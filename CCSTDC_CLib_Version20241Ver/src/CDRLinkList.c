#include "CDRLinkList.h"
#include "CUtilsContainerLogStr.h"
#include "CLibLog.h"
/// private func
// from zero start
bool isIndexValid_Find(CLinkList* l, Index index)
{
    return index >=0 && index < l->listSize;
}

bool isIndexValid_Insert(CLinkList* l, Index index)
{
    return index >=0 && index <= l->listSize;
}



CLinkNode* private_CDRLinkList_At(CLinkList* list, Index index)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(list, NULL, stderr);
    INDEX_INVALID_OPERATE(index, isIndexValid_Find(list, index), list->logger, list->listSize, NULL);

    if(index == 0)
        return list->head;
    if(index == list->listSize - 1)
        return list->tail;

    CLinkNode* cur = list->head;

    for(int i = 0; i < index; i++)
    {
        cur = CDRLinkList_GetNext(cur);
    }

    return cur;
}



CLinkNode* CDRLinkList_CreateCLinkNode(void* elem, Size elem_Size, FILE* logger)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(elem, NULL, logger);
    // malloc space
    CLinkNode* node = NULL;
    Malloc(node, CLinkNode, 1, logger);
    CODE_MSG_FORMAT(logger, CREATE_LinkNode_STR, Info, true);
    // handle data
    void* data = NULL;
    NMalloc(data, sizeof(char), elem_Size, logger);
    memcpy(data, elem, elem_Size);

    node->elem_Size = elem_Size;
    node->elem = data;
    node->logger = logger;
    node->next = NULL;
    node->prev = NULL;
    CODE_MSG_FORMAT(logger, OPERATE_SUCCESS, Info, false);
    return node;
}

CLinkNode* CDRLinkList_CopyCLinkNode(CLinkNode* node, FILE* logger)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(node, NULL, logger);
    // malloc space
    CLinkNode* other = NULL;
    Malloc(other, CLinkNode, 1, logger);
    CODE_MSG_FORMAT(logger, CREATE_LinkNode_STR, Info, true);

    // handle data
    void* data = NULL;
    NMalloc(data, sizeof(char), node->elem_Size, logger);
    memcpy(data, node->elem, node->elem_Size);

    other->logger = logger;
    other->elem = data;
    other->elem_Size = node->elem_Size;
    other->prev = NULL;
    other->next = NULL;

    return other;
}

CLinkNode* CDRLinkList_GetNext(CLinkNode* node)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(node, NULL, stderr);
    return node->next;
}

CLinkNode* CDRLinkList_GetPrev(CLinkNode* node)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(node, NULL, stderr);
    return node->prev;
}

bool CDRLinkList_HasNext(CLinkNode* node)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(node, false, stderr);
    return node->next == NULL;
}

bool CDRLinkList_HasPrev(CLinkNode* node)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(node, false, stderr);
    return node->prev == NULL;
}

void* CDRLinkList_GetElem(CLinkNode* node)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(node, false, stderr);
    return node->elem;
}

CLinkNode* CDRLinkList_setNext(CLinkNode* node, CLinkNode* insert_node)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(node, NULL, stderr);
    node->next = insert_node;
    if(insert_node != NULL)
    {
        // adjust relationship
        insert_node->prev = node;
    }
    return node;
}

CLinkNode* CDRLinkList_setPrev(CLinkNode* node, CLinkNode* insert_node)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(node, NULL, stderr);
    node->prev = insert_node;
    if(insert_node != NULL)
    {
        // adjust relationship
        insert_node->next = node;
    }
    return node;
}

CLinkNode* CDRLinkList_setNextEx(CLinkNode* node, void* elem, Size elem_Size, FILE* logger)
{
    CLinkNode* newNode = CDRLinkList_CreateCLinkNode(elem, elem_Size, logger);
    return CDRLinkList_setNext(node, newNode);
}

CLinkNode* CDRLinkList_setPrevEx(CLinkNode* node, void* elem, Size elem_Size, FILE* logger)
{
    CLinkNode* newNode = CDRLinkList_CreateCLinkNode(elem, elem_Size, logger);
    return CDRLinkList_setPrev(node, newNode);
}

CLinkNode* CDRLinkList_EraseCLinkNode(CLinkNode* node)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(node, NULL, stderr);
    FILE* p = node->logger;
    SafeFree(node->elem, p);
    CODE_MSG_FORMAT(node->logger, "free link_node core success", Info, true);

    SafeFree(node, p);
    CODE_MSG_FORMAT(p, "free link_node success", Info, false);
    return node;
}

CLinkList*  CDRLinkList_CreateEmptyCLinkList(FILE* logger)
{
    CLinkList* list = NULL;
    CODE_MSG_FORMAT(logger, CREATE_LinkNode_STR, Info, true);
    Malloc(list, CLinkList, 1, logger);

    list->logger = logger;
    list->listSize = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

CLinkList*  CDRLinkList_CopyCDRLinkList(CLinkList* list, FILE* logger)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(list, NULL, stderr);
    CLinkList* l = CDRLinkList_CreateEmptyCLinkList(logger);
    for(CLinkNode* node = list->head; node != list->tail || !node; node = CDRLinkList_GetNext(node))
    {
        CLinkNode* new_node = CDRLinkList_CopyCLinkNode(node, logger);
        CDRLinkList_PushBack(l, new_node);
    }

    CDRLinkList_PushBack(l, CDRLinkList_CopyCLinkNode(list->tail, logger));

    return l;
}



bool CDRLinkList_IsListEmpty(CLinkList* list)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(list, false, stderr);
    return list->listSize == 0;
}

bool CDRLinkList_PushBack(CLinkList* list, CLinkNode* node)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(list, false, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(node, false, list->logger);
    CODE_MSG_FORMAT(list->logger, PUSH_BACK_STR, Info, true);
    if(CDRLinkList_IsListEmpty(list))
    {
        // config node:> point to itself
        node->next = node->prev = node;
        // empty, config the only one, head and tail is itself
        list->head = list->tail = node;
    }
    else
    {
        // config the node
        CDRLinkList_setNext(node, list->head);
        CDRLinkList_setPrev(node, list->tail);
        // update the list info
        list->tail = node;
    }

    list->listSize++;
    return true;
}

bool CDRLinkList_PushBackEx(CLinkList* list, void* elem, Size elem_Size, FILE* logger)
{
    CLinkNode* newNode = CDRLinkList_CreateCLinkNode(elem, elem_Size, logger);
    return CDRLinkList_PushBack(list, newNode);
}

bool CDRLinkList_PushFront(CLinkList* list, CLinkNode* node)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(list, false, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(node, false, list->logger);
    CODE_MSG_FORMAT(list->logger, PUSH_FRONT_STR, Info, true);
    if(CDRLinkList_IsListEmpty(list))
    {
        // config node:> point to itself
        node->next = node->prev = node;
        // empty, config the only one, head and tail is itself
        list->head = list->tail = node;
    }
    else
    {
        // config the node
        CDRLinkList_setNext(node, list->head);
        CDRLinkList_setPrev(node, list->tail);
        // update the list info
        list->head = node;
    }
    list->listSize++;
    return true;
}

bool CDRLinkList_PushFrontEx(CLinkList* list, void* elem, Size elem_Size, FILE* logger)
{
    CLinkNode* newNode = CDRLinkList_CreateCLinkNode(elem, elem_Size, logger);
    return CDRLinkList_PushFront(list, newNode);
}

CLinkNode* CDRLinkList_PopBack(CLinkList* list, bool need_free_auto)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(list, NULL, stderr);
    CODE_MSG_FORMAT(list->logger, POP_BACK_STR, Info, true);
    if(list->listSize == 0)
    {
        CODE_MSG_FORMAT(list->logger, "List is empty, no need to pop!\n", Info, true);
        return NULL;
    }

    // Find Last
    CLinkNode* node = private_CDRLinkList_At(list, list->listSize - 1);

    // reset list info
    list->tail = node->prev;

    // reset the list-rela node info
    CDRLinkList_setPrev(list->head, list->tail);
    CDRLinkList_setNext(list->tail, list->head);

    // reset the node-rela as empty
    node->next = NULL;
    node->prev = NULL;

    if(need_free_auto)
        CDRLinkList_EraseCLinkNode(node);
    list->listSize--;

    if(list->listSize == 0)
    {
        list->head = NULL;
        list->tail = NULL;
    }

    return node;
}

CLinkNode*  CDRLinkList_PopFront(CLinkList* list, bool need_free_auto)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(list, NULL, stderr);
    CODE_MSG_FORMAT(list->logger, POP_FRONT_STR, Info, true);
    if(list->listSize == 0)
    {
        CODE_MSG_FORMAT(list->logger, "List is empty, no need to pop!\n", Info, true);
        return NULL;
    }

    // Find First
    CLinkNode* node = private_CDRLinkList_At(list, 0);

    // reset list info
    list->head = node->next;

    // reset the list-rela node info
    CDRLinkList_setPrev(list->head, list->tail);
    CDRLinkList_setNext(list->tail, list->head);

    // reset the node-rela as empty
    node->next = NULL;
    node->prev = NULL;
    if(need_free_auto)
        CDRLinkList_EraseCLinkNode(node);

    list->listSize--;

    if(list->listSize == 0)
    {
        list->head = NULL;
        list->tail = NULL;
    }

    return node;
}

void* CDRLinkList_At(CLinkList* list, Index index)
{
    CLinkNode* node = private_CDRLinkList_At(list, index);
    return node ? node->elem : NULL;
}






bool CDRLinkList_Insert(CLinkList* list, CLinkNode* node, Index index)
{
    if(index == 0)
        return CDRLinkList_PushFront(list, node);
    if(index == list->listSize)
        return CDRLinkList_PushBack(list, node);

    NO_ALLOWED_OPERATE_NULL_CHECK(list, false, stderr);
    NO_ALLOWED_OPERATE_NULL_CHECK(node, false, list->logger);
    CODE_MSG_FORMAT_Self_def(
            list->logger,
            fprintf(list->logger,
                    "Will insert to the index to the dr_list:> %d\n", index),
            Info,
            true);
    // special accelerate, and settings

    CLinkNode* prev_node = private_CDRLinkList_At(list, index);
    if(!prev_node || !prev_node->prev)
        return false;

    // [prev_node] -> [curNode]  node

    CLinkNode* curNode = prev_node;
    prev_node = CDRLinkList_GetPrev(prev_node);

    // set Node Info
    CDRLinkList_setNext(node, curNode);
    CDRLinkList_setPrev(node, prev_node);

    // update node info
    CDRLinkList_setPrev(curNode, node);
    CDRLinkList_setNext(prev_node, node);

    list->listSize++;
    return true;
}

bool CDRLinkList_InsertEx(CLinkList* list, Index index, void* elem, Size elem_Size, FILE* logger)
{
    CLinkNode* node = CDRLinkList_CreateCLinkNode(elem, elem_Size, logger);
    return CDRLinkList_Insert(list, node, index);
}

CLinkNode* CDRLinkList_EraseElem(CLinkList* list, Index index, bool need_free_auto)
{
    if(index == 0)
        return CDRLinkList_PopFront(list, need_free_auto);
    if(index == list->listSize - 1)
        return CDRLinkList_PopBack(list, need_free_auto);

    NO_ALLOWED_OPERATE_NULL_CHECK(list, false, stderr);

    CODE_MSG_FORMAT_Self_def(
            list->logger,
            fprintf(list->logger,
                    "Will erase to the index to the dr_list:> %d\n", index),
            Info,
            true);

    CLinkNode* node = private_CDRLinkList_At(list, index);
    if(!node || !node->prev)
        return false;

    CLinkNode* cur_node = private_CDRLinkList_At(list, index);
    CLinkNode* prev = CDRLinkList_GetPrev(cur_node);

    // update list-node info
    CDRLinkList_setNext(prev, cur_node->next);
    CDRLinkList_setPrev(cur_node->next, prev);

    // reset the node-rela
    cur_node->next = NULL;
    cur_node->prev = NULL;
    if(need_free_auto)
        CDRLinkList_EraseCLinkNode(cur_node);
    list->listSize--;
    return cur_node;
}

Size CDRLinkList_GetSize(CLinkList* list){
    NO_ALLOWED_OPERATE_NULL_CHECK(list, 0 , stderr);
    return list->listSize;
}

CLinkNode* CDRLinkList_GetHead(CLinkList* list)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(list, NULL , stderr);
    return list->head;
}

CLinkNode*  CDRLinkList_GetTail(CLinkList* list)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(list, NULL , stderr);
    return list->tail;
}

CLinkList* CDRLinkList_Erase(CLinkList* list)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(list, NULL , stderr);
    CLinkNode* cur =    list->head;
    CLinkNode* next =   list->head;
    for(int cur_index = 0; cur_index < list->listSize; cur_index++)
    {
        next = cur->next;
        CDRLinkList_EraseCLinkNode(cur);
        cur = next;
    }

    FILE* logger = list->logger;
    list->listSize = 0;
    SafeFree(list, logger);
    return list;
}