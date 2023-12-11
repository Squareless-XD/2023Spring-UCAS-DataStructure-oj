// 9.42-9.43 Trie 树插入删除和查找
// Description
// 假设Trie树上同义词放在同一叶子结点中，请实现 Trie 树的插入、删除、查找功能

// Input
// 输入为若干行，每行包括一个数字和一个字符串(只包含小写字母)，数字 1、2、3 分别表示插入、删除、查找。如果删除的元素不存在，则不作任何操作。查找的元素存在输出为 True, 不存在输出为 False.

// Output
// 输出的行数为查找操作的次数，若查找的元素存在输出为 True, 不存在输出为 False。

// Sample Input 1       Sample Output 1
// 1 apple              True
// 1 app                False
// 1 at
// 2 app
// 3 apple
// 2 apple
// 3 apple
// Sample Input 2       Sample Output 2
// 1 a                  False
// 1 b                  False
// 1 c                  True
// 1 ab
// 1 acd
// 2 ac
// 3 ac
// 3 abc
// 3 ab

#include <bits/stdc++.h>
using namespace std;

#define STACK_INIT_SIZE 100 // 存储空间初始分配量 单位：stackElemType
#define STACK_INCREMENT 10  // 存储空间分配增量

#define OK 0
#define ERROR 1
#define INFEASIBLE -1
#define OVERFLOW_TREE -2
#define OVERFLOW_STACK -2

typedef int status;
// typedef char biTElemType;

#define DATA 0
#define POINTER 1

typedef struct _trieNode
{
    int dataKind;
    union
    {
        struct _trieNode *next[27];
        char *data;
    } data;
} trieNode;

typedef trieNode *stackElemType;

typedef struct
{
    stackElemType *base;
    stackElemType *top;
    int stacksize;
} sqStack;


sqStack *stackAlloc(void);
status initStack_Sq(sqStack *stack);
status destroyStack_Sq(sqStack *stack);
status stackEmpty_Sq(sqStack *stack);
status getTop_Sq(sqStack *stack, stackElemType *e);
status push_Sq(sqStack *stack, stackElemType e);
status pop_Sq(sqStack *stack, stackElemType *e);

sqStack *stackAlloc(void)
{
    sqStack *stack;
    stack = (sqStack *)malloc(sizeof(sqStack));
    if (!stack)
        return NULL;
    return stack;
}

status initStack_Sq(sqStack *stack)
{
    stack->base = (stackElemType *)malloc(STACK_INIT_SIZE * sizeof(stackElemType));
    if (!stack->base)
        exit(OVERFLOW_STACK);
    stack->top = stack->base;
    stack->stacksize = STACK_INIT_SIZE;
    return OK;
}

status destroyStack_Sq(sqStack *stack)
{
    free(stack->base);
    return OK;
}

status stackEmpty_Sq(sqStack *stack)
{
    if (stack->top == stack->base)
        return true;
    return false;
}

status getTop_Sq(sqStack *stack, stackElemType *e)
{
    if (stack->top == stack->base)
        return ERROR;
    *e = *(stack->top - 1);
    return OK;
}

status push_Sq(sqStack *stack, stackElemType e)
{
    if (stack->top - stack->base >= stack->stacksize)
    {
        stack->base = (stackElemType *)realloc(stack->base, (stack->stacksize + STACK_INCREMENT) * sizeof(stackElemType));
        if (!stack->base)
            exit(OVERFLOW_STACK);
        stack->top = stack->base + stack->stacksize;
        stack->stacksize += STACK_INCREMENT;
    }
    *(stack->top++) = e;
    return OK;
}

status pop_Sq(sqStack *stack, stackElemType *e)
{
    if (stack->top == stack->base)
        return ERROR;
    *e = *--stack->top;
    return OK;
}

// insert a new node into the trie tree, which is a pointer node
status triePointerAlloc(trieNode **triePointer)
{
    int i;
    *triePointer = (trieNode *)malloc(sizeof(trieNode));
    if (*triePointer == NULL)
        return ERROR;
    (*triePointer)->dataKind = POINTER;
    for (i = 0; i < 27; i++)
        (*triePointer)->data.next[i] = NULL;
    return OK;
}

// insert a new node into the trie tree, which is a data node
status trieDataAlloc(trieNode **trieData, const char *data)
{
    *trieData = (trieNode *)malloc(sizeof(trieNode));
    if (*trieData == NULL)
        return ERROR;
    (*trieData)->dataKind = DATA;
    (*trieData)->data.data = (char *)malloc((strlen(data) + 1) * sizeof(char));
    if ((*trieData)->data.data == NULL)
        return ERROR;
    strcpy((*trieData)->data.data, data);
    return OK;
}

// destroy a trie tree
status trieTreeDestroy(trieNode **ptrieTree)
{
    int i;
    if (ptrieTree == NULL)
        return ERROR;
    if (*ptrieTree == NULL)
        return OK;
    if ((*ptrieTree)->dataKind == DATA)
        free((*ptrieTree)->data.data);
    else if ((*ptrieTree)->dataKind == POINTER)
        for (i = 0; i < 27; i++)
            trieTreeDestroy(&(*ptrieTree)->data.next[i]);
    free(*ptrieTree);
    return OK;
}

// clear a trie tree
status trieTreeClear(trieNode *trieTree)
{
    int i;
    if (trieTree == NULL)
        return OK;
    if (trieTree->dataKind == DATA)
        free(trieTree->data.data);
    else if (trieTree->dataKind == POINTER)
        for (i = 0; i < 27; i++)
            trieTreeClear(trieTree->data.next[i]);
    free(trieTree);
    return OK;
}

// add a new word into the trie tree.
status trieTreeInsert(trieNode *trieTree, const char *word)
{
    int i, j;
    trieNode *triePointer;

    // if the trie tree is empty, create a new trie tree
    if (trieTree == NULL)
        return ERROR;
    // if the trie tree is not empty, find the position to insert the new word
    for (i = 0; i < strlen(word); i++)
    {
        // if the next node is NULL, create a new node
        if (trieTree->data.next[word[i] - 'a'] == NULL)
        {
            triePointerAlloc(&triePointer);
            trieTree->data.next[word[i] - 'a'] = triePointer;
        }
        // go to the next node
        trieTree = trieTree->data.next[word[i] - 'a'];
    }
    // when the word is finished, create a new data node at trieTree->data.next[26]
    trieDataAlloc(&triePointer, word);
    trieTree->data.next[26] = triePointer;

    return OK;
}

// delete a word from the trie tree
status trieTreeDelete(trieNode *trieTree, const char *word)
{
    // use a stack to store the path
    sqStack *stack;
    int i, j, pathValid;
    trieNode *triePointer;

    // initialize the stack
    stack = stackAlloc();
    initStack_Sq(stack);

    // if the trie tree is empty, return ERROR
    if (trieTree == NULL)
        return ERROR;
    // if the trie tree is not empty, find the position to delete the word
    for (i = 0; i < strlen(word); i++)
    {
        // if the next node is NULL, return ERROR
        if (trieTree->data.next[word[i] - 'a'] == NULL)
            return ERROR;
        // store the path into the stack
        push_Sq(stack, trieTree);
        // go to the next node
        trieTree = trieTree->data.next[word[i] - 'a'];
    }
    // when the word is finished, delete the data node at trieTree->data.next[26]
    trieTreeClear(trieTree->data.next[26]);
    trieTree->data.next[26] = NULL;

    // use the stack to delete the useless nodes. remember to destory the stack
    while (!stackEmpty_Sq(stack))
    {
        pop_Sq(stack, &triePointer);
        pathValid = false;
        for (i = 0; i < 27; i++)
            if (triePointer->data.next[i] != NULL)
                pathValid = true;
        if (pathValid == false)
        {
            trieTreeClear(triePointer);
            triePointer = NULL;
        }
        else
            break;
    }

    // destory the stack
    destroyStack_Sq(stack);

    return OK;
}

// search a word in the trie tree
status trieTreeSearch(trieNode *trieTree, const char *word)
{
    int i;
    // if the trie tree is empty, return false
    if (trieTree == NULL)
        return false;
    // if the trie tree is not empty, find the position to search the word
    for (i = 0; i < strlen(word); i++)
    {
        // if the next node is NULL, return false
        if (trieTree->data.next[word[i] - 'a'] == NULL)
            return false;
        // go to the next node
        trieTree = trieTree->data.next[word[i] - 'a'];
    }
    // when the word is finished, check whether the data node at trieTree->data.next[26] is NULL
    if (trieTree->data.next[26] == NULL)
        return false;
    return true;
}

int main()
{
    int op; // 1 for insert, 2 for delete, 3 for search
    char word[100]; // the word to be handled
    trieNode *trieTree;

    // initialize the trie tree
    triePointerAlloc(&trieTree);

    // input the words
    while (scanf("%d", &op) != EOF)
    {
        scanf("%s", word);
        if (op == 1) // insert
            trieTreeInsert(trieTree, word);
        else if (op == 2) // delete
            trieTreeDelete(trieTree, word);
        else if (op == 3) // search
        {
            if (trieTreeSearch(trieTree, word) == true)
                std::cout << "True" << std::endl;
            else
                std::cout << "False" << std::endl;
        }
    }

    // destory the trie tree
    trieTreeDestroy(&trieTree);

    return 0;
}