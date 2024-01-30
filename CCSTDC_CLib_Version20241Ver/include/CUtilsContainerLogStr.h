//
// Created by ³Â¹ÚºÀ on 2024/1/21.
//

#ifndef CUTILS_CUTILSCONTAINERLOGSTR_H
#define CUTILS_CUTILSCONTAINERLOGSTR_H
#define OPERATE_SUCCESS     "success!\n"

#define CREATE_ARRAY_STR    "start creating an array\n"
#define COPY_ARRAY_STR      "start copying array\n"

#define CREATE_DYNAMIC_ARR_STR  "start creating a dynamic array\n"
#define COPY_DYNAMIC_ARR_STR    "start copying a dynamic array\n"

#define CREATE_LinkNode_STR     "Create a node"
#define CREATE_LinkList_STR     "Create a dr_list"
#define Copy_LinkNode_STR       "Copy a node"
#define Copy_LinkList_STR       "Copy a dr_list"


#define REALLOC_SIZE_STR            "reallocateSize happen!"
#define PUSH_BACK_STR               "push back an elem into the array"
#define POP_BACK_STR                "pop back an elem from the array"
#define PUSH_FRONT_STR              "push front an elem into the array"
#define POP_FRONT_STR               "pop front an elem from the array"
#define INSERT_STR(index)           "insert into the array:> %d\n"
#define KICK_STR(index)             "will kick the index:> %d\n"

#define CStaticArray_Infos(arr)  "[ArrInfo]:\nArray_begin_addr:> %p\nArray_size:> %d\nArray_type_size:> %d\n", \
                                arr->coreArray, arr->arraySize, arr->typeSize

#define CDynamicArray_Infos(arr) "[DynamicInfo]:\n Array_begin_addr:> %p\nArray_size_current:> %d\n Array_capacity:> %d\nArray_type_size:> %d\n", \
                       arr->array, arr->cur_size, arr->capacity, arr->type_size

#define WRITE_CStaticArray_Info(arr, logger)    if(logger) fprintf(logger, CStaticArray_Infos(arr))
#define WRITE_CDynamicArray_Info(arr, logger)   if(logger) fprintf(logger, CDynamicArray_Infos(arr))

#define Create_A_Stack_As_Static_STR        "Creating a static stack\n"
#define Create_A_Stack_As_Dynamic_STR       "Creating a dynamic stack\n"
#define Copy_A_Stack                        "Copying A Stack\n"

#define STACK_FULL_STR                      "Stack is full!\n"
#define STACK_IS_EMPTY                      "Stack is empty!\n"


#define Create_A_Pair_STR                   "Creating a pair"
#define Copy_A_Pair_STR                     "Copy a pair"

#define Create_A_LinearMap_STR              "Creating a LinearMap"
#define Copy_A__LinearMap_STR               "Copying a LinearMap"

#define Create_A_Node_STR                   "Creating a node"
#define Copy_A_Node_STR                     "Copying a node"

#define Create_A_BinTree_STR                "Creating a Binary Searching Tree"
#define Copy_A_Bin_Tree_STR                 "Copying a Binary Searching Tree"

#endif //CUTILS_CUTILSCONTAINERLOGSTR_H
