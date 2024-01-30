#include "CBinaryTree.h"
#include "CUtilsContainerLogStr.h"
#include "CLibLog.h"
typedef struct ___BinaryNode{
    void*                   data;
    Size                    dataSize;
    Size                    sonNodeNumber;
    struct ___BinaryNode*   leftNode;
    struct ___BinaryNode*   rightNode;
    struct ___BinaryNode*   father;
    FILE*                   logger;
}CBinaryTreeNode;
CBinaryTreeNode* CBinaryTree_CopyBinNode(CBinaryTreeNode* node, FILE* logger);

void privatePrintTree(CBinaryTreeNode* node, Printable p, int tab_size)
{
    if(node == NULL)
        return;
    privatePrintTree(node->leftNode, p, tab_size + 1);
    for(int i = 0; i < tab_size; i++) printf("          ");
    p(node->data);
    printf("\n");
    privatePrintTree(node->rightNode, p, tab_size + 1);
}

CBinaryTreeNode* private_CBinTree_Copy_IterNode(CBinaryTreeNode* copiee)
{
    if(copiee == NULL)
        return NULL;

    CBinaryTreeNode* newNode = CBinaryTree_CopyBinNode(copiee, copiee->logger);
    newNode->leftNode = private_CBinTree_Copy_IterNode(copiee->leftNode);
    newNode->rightNode = private_CBinTree_Copy_IterNode(copiee->rightNode);

    return newNode;
}

bool private_CBinTree_Find(CBinaryTreeNode* node, void* data, CompareFunc p, bool* find_flag, unsigned char** _SHOULD_BE_NULL _mem_data)
{
    if(node == NULL || *find_flag == true)
        return false; // stop

    private_CBinTree_Find(node->leftNode, data, p, find_flag, _mem_data);
    if(*find_flag == false) // unfound
    {
        if(p(node->data, data) == EQUAL)
        {
            unsigned char* mem_data = NULL;
            NMalloc(mem_data, sizeof(char), node->dataSize, node->logger);
            memcpy(mem_data, node->data, node->dataSize);
            *_mem_data = mem_data;
            return true;
        }
    }
    private_CBinTree_Find(node->rightNode, data, p, find_flag, _mem_data);
    return true;
}


bool private_CBinaryTree_SetAsSonPolicy(CBinaryTreeNode* node, CBinaryTreeNode* settee, CompareFunc p)
{
    if(node == NULL)
        return false; // stop! insert here
    node->sonNodeNumber++;
    switch (p(node->data, settee->data)) {
        case EQUAL:
        case SMALL:
            if(!private_CBinaryTree_SetAsSonPolicy(node->leftNode, settee, p))
            {
                // insert here
                node->leftNode = settee;
                node->sonNodeNumber += settee->sonNodeNumber + 1;
                settee->father = node;
                return true;
            }
            break;
        case BIGGER:
            if(!private_CBinaryTree_SetAsSonPolicy(node->rightNode, settee, p))
            {
                // insert here
                node->rightNode = settee;
                node->sonNodeNumber += settee->sonNodeNumber + 1;
                settee->father = node;
                return true;
            }
    }
    return true;
}

CBinaryTreeNode*    CBinaryTree_CreateBinNode(void* data, Size dataSize, FILE* logger)
{
    CBinaryTreeNode* node = NULL;
    CODE_MSG_FORMAT(logger, Create_A_Node_STR, Info, false);
    Malloc(node, CBinaryTreeNode, 1, logger);

    void* _data = NULL;
    NMalloc(_data, sizeof(char), dataSize, logger);
    memcpy(_data, data, dataSize);

    node->logger = logger;
    node->data = _data;
    node->dataSize = dataSize;
    node->leftNode = NULL;
    node->rightNode = NULL;
    node->sonNodeNumber = 0;
    node->father = NULL;
    return node;
}

CBinaryTreeNode* CBinaryTree_CopyBinNode(CBinaryTreeNode* node, FILE* logger)
{
    CBinaryTreeNode* other_node = NULL;
    CODE_MSG_FORMAT(logger, Copy_A_Node_STR, Info, false);

    Malloc(other_node, CBinaryTreeNode, 1, logger);

    void* _data = NULL;
    NMalloc(_data, sizeof(char), node->dataSize, logger);
    memcpy(_data, node->data, node->dataSize);

    node->logger = logger;
    node->data = _data;
    node->dataSize = node->dataSize;
    node->leftNode = NULL;
    node->rightNode = NULL;
    node->sonNodeNumber = 0;
    node->father = NULL;
    return node;
}

CBinaryTreeNode* CBinaryTree_EraseBinNode(CBinaryTreeNode* node)
{
    if(node == NULL)
        return NULL;

    CBinaryTree_EraseBinNode(node->leftNode);
    CBinaryTree_EraseBinNode(node->rightNode);
    FILE* p = node->logger;
    CODE_MSG_FORMAT(p, "Gonna Erase the node core data", Info, false);
    SafeFree(node->data, p);
    CODE_MSG_FORMAT(p, "Gonna Erase the node", Info, false);
    SafeFree(node, p);
    return node;
}

bool private_Iterate(CBinaryTreeNode* node, HandleEach f, void* args, Size argNum, IterateMethod m)
{
    if(node == NULL)
        return false;

    switch (m) {
        case PRE_ORDER:
        {
            f(node->data, args, argNum);
            private_Iterate(node->leftNode, f, args, argNum, m);
            private_Iterate(node->rightNode, f, args, argNum, m);
            return true;
        }
        case IN_ORDER:
        {
            private_Iterate(node->leftNode, f, args, argNum, m);
            f(node->data, args, argNum);
            private_Iterate(node->rightNode, f, args, argNum, m);
            return true;
        }
        case POST_ORDER:
        {
            private_Iterate(node->leftNode, f, args, argNum, m);
            private_Iterate(node->rightNode, f, args, argNum, m);
            f(node->data, args, argNum);
            return true;
        }
    }
    return false;
}

CBinaryTree* CBinaryTree_CreateAEmptyBinTree(FILE* l, CompareFunc f)
{
    CODE_MSG_FORMAT(l, Create_A_BinTree_STR, Info, true);
    CBinaryTree*  tree = NULL;
    Malloc(tree, CBinaryTree, 1, l);

    tree->logger = l;
    tree->root = NULL;
    tree->insertFunc = f;
    CODE_MSG_FORMAT(l, OPERATE_SUCCESS, Info, false);
    return tree;
}

CBinaryTree* CBinaryTree_CopyABinTree(CBinaryTree* tree, FILE* l)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(tree, NULL, stderr);
    CBinaryTree* new_tree = CBinaryTree_CreateAEmptyBinTree(l, tree->insertFunc);
    new_tree->root = private_CBinTree_Copy_IterNode(tree->root);
    return new_tree;
}

bool CBinaryTree_InsertData(CBinaryTree* tree,void* data, Size dataSize)
{
    CBinaryTreeNode* node = CBinaryTree_CreateBinNode(data, dataSize, tree->logger);
    if(tree->root == NULL)
    {
        tree->root = node;
        return true;
    }

    return private_CBinaryTree_SetAsSonPolicy(tree->root, node, tree->insertFunc);
}

bool CBinaryTree_IterateEach(CBinaryTree* tree, HandleEach f, void* args, Size argNum, IterateMethod m)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(tree, false, stderr);
    return private_Iterate(tree->root, f, args, argNum, m);
}

CBinaryTree* CBinaryTree_EraseTree(CBinaryTree* tree)
{
    NO_ALLOWED_OPERATE_NULL_CHECK(tree, false, stderr);
    CBinaryTree_EraseBinNode(tree->root);
    CODE_MSG_FORMAT(tree->logger, "Success erase code data", Info ,true);
    FILE* p = tree->logger;
    SafeFree(tree, p);
    CODE_MSG_FORMAT(p, "Success erase the tree", Info, false);
    return tree;
}

void*  CBinaryTree_Find(CBinaryTree* binTree, void* target)
{
    void* data = NULL;
    bool flag = false;
    private_CBinTree_Find(binTree->root, target, binTree->insertFunc,
                          &flag, (unsigned char**)&data);

    return data;
}

void CBinaryTree_PrintTree(CBinaryTree* tree, Printable f)
{
    privatePrintTree(tree->root, f, 0);
}

