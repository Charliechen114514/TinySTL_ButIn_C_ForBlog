#ifndef CUTILS_CBINARYTREE_H
#define CUTILS_CBINARYTREE_H
#include "CLibUtility.h"

struct ___BinaryNode;

typedef void(*HandleEach)(void* p, void* arg, Size argNum);
typedef void(*Printable)(const void* const);
typedef enum{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
}IterateMethod;

typedef struct ___BinaryTree
{
    FILE*                   logger;
    struct ___BinaryNode*   root;
    CompareFunc             insertFunc;
}CBinaryTree;

CBinaryTree*        CBinaryTree_CreateAEmptyBinTree(FILE* l, CompareFunc f);
CBinaryTree*        CBinaryTree_CopyABinTree(CBinaryTree* tree, FILE* l);
bool                CBinaryTree_InsertData(CBinaryTree* tree,void* data, Size dataSize);
bool                CBinaryTree_EraseData(CBinaryTree* tree, void* data);
bool                CBinaryTree_IterateEach(CBinaryTree* tree,
                                            HandleEach f, void* args, Size argNum,
                                            IterateMethod m);
CBinaryTree*        CBinaryTree_EraseTree(CBinaryTree* tree);
void*               CBinaryTree_Find(CBinaryTree* binTree, void* target);

void                CBinaryTree_PrintTree(CBinaryTree* tree, Printable f);

#endif //CUTILS_CBINARYTREE_H
