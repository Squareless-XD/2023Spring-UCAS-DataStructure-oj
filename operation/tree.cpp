#include <bits/stdc++.h>

#define treeElemType int

#define true 1
#define false 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW_QUEUE -2

typedef int status;

typedef struct tNode
{
    treeElemType data;
    struct tNode *nextSibling;
    struct tNode *firstChild;
}treeNode;

typedef struct
{
    treeNode *root;
}treeData;

typedef int queueElemType;
typedef int status;

typedef struct qNode
{
    queueElemType data;
    struct qNode *next;
} queueNode;

typedef struct
{
    queueNode *front;
    queueNode *rear;
} linkedQueue;

linkedQueue *queueAlloc(void);
status initQueue(linkedQueue *queue);
status destoryQueue(linkedQueue *queue);
status clearQueue(linkedQueue *queue);
status queueEmpty(linkedQueue *queue);
int queueLength(linkedQueue *queue);
status getFront(linkedQueue *queue, queueElemType *elem);
status enqueue(linkedQueue *queue, queueElemType elem);
status dequeue(linkedQueue *queue, queueElemType *elem);
status queueTraverse(linkedQueue *queue, status (*visit)(queueNode *node));

// get a pointer to a linked queue
linkedQueue *queueAlloc(void)
{
    linkedQueue *queue;
    queue = (linkedQueue *)malloc(sizeof(linkedQueue));
    if (!queue)
        return NULL;
    return queue;
}

// initialize a new linked queue
status initQueue(linkedQueue *queue)
{
    queue->front = queue->rear = (queueNode *)malloc(sizeof(queueNode));
    if (!queue)
        return ERROR;
    queue->front->next = NULL;
    return OK;
}

// destory a queue
status destoryQueue(linkedQueue *queue)
{
    while (queue->front)
    {
        queue->rear = queue->front->next;
        free(queue->front);
        queue->front = queue->rear;
    }
    return OK;
}

// clear a queue
status clearQueue(linkedQueue *queue)
{
    queueNode *p, *temp;
    p = queue->front->next;
    queue->rear = queue->front;
    while (p)
    {
        temp = p->next;
        free(p);
        p = temp;
    }
    return OK;
}

// check whether a queue is empty. if so, return true
status queueEmpty(linkedQueue *queue)
{
    if (queue->front == queue->rear)
        return true;
    return false;
}

// get the length of the queue
int queueLength(linkedQueue *queue)
{
    int length = 0;
    queueNode *p;

    if (queue->front == queue->rear)
        return 0;
    p = queue->front->next;
    while (p)
    {
        ++length;
        p = p->next;
    }
    return length;
}

// get the front element from the queue without letting it out
status getFront(linkedQueue *queue, queueElemType *elem)
{
    if (queue->front == queue->rear)
        return ERROR;
    *elem = queue->front->data;
    return OK;
}

// put a new element into the queue
status enqueue(linkedQueue *queue, queueElemType elem)
{
    queueNode *newNode;
    newNode = (queueNode *)malloc(sizeof(queueNode));
    if (!newNode)
        return ERROR;
    newNode->data = elem;
    newNode->next = NULL;
    queue->rear->next = newNode;
    queue->rear = newNode;
    return OK;
}

// take out the oldest element from the queue
status dequeue(linkedQueue *queue, queueElemType *elem)
{
    queueNode *frontTemp;
    if (queue->front == queue->rear)
        return ERROR;
    frontTemp = queue->front->next; // since this node contains the first element that is ever stored
    *elem = frontTemp->data;
    queue->front->next = frontTemp->next;
    if (queue->rear == frontTemp)
        queue->rear = queue->front;
    free(frontTemp);
    return OK;
}

status queueTraverse(linkedQueue *queue, status (*visit)(queueNode *node))
{
    queueNode *p;
    if (queue->front == queue->rear)
        return ERROR;
    p = queue->front->next;
    while (p)
    {
        visit(p);
        p = p->next;
    }
    return OK;
}


treeData *treeAlloc(void)
{
    treeData *tree;
    tree = (treeData *)malloc(sizeof(treeData));
    if (!tree)
        return NULL;
    return tree;
}

// initialize a new linked queue
status initTree(treeData *tree)
{
    tree->root = (treeNode *)malloc(sizeof(treeNode));
    if (!tree->root)
        return ERROR;
    tree->root->nextSibling = NULL;
    tree->root->firstChild = NULL;
    return OK;
}

// destory a queue
status destoryTree(treeData *tree)
{
    clearTree(tree->root);
    free(tree);
    return OK;
}

status clearTree(treeNode *root)
{
    treeNode *p, *temp;
    p = root;
    while (p)
    {
        temp = p->nextSibling;
        clearTree(p->firstChild);
        free(p);
        p = temp;
    }
    return OK;
}

// check whether a tree is empty. if so, return OK

status treeEmpty(treeData *tree)
{
    if (tree->root == NULL)
        return true;
    return false;
}

// get the depth of the tree
int treeDepth(treeNode *root)
{
    int depth;
    treeNode *p = root->firstChild;
    if (!p)
        return 0;
    while (p)
    {
        depth = std::max(0, treeDepth(p) + 1);
        p = p->nextSibling;
    }
    return depth;
}

// get the root
treeNode *getRoot(treeData *tree)
{
    return tree->root;
}

// // put a new element into the queue
// status enqueue(linkedQueue *queue, queueElemType elem)
// {
//     queueNode *newNode;
//     newNode = (queueNode *)malloc(sizeof(queueNode));
//     if (!newNode)
//         return ERROR;
//     newNode->data = elem;
//     newNode->next = NULL;
//     queue->rear->next = newNode;
//     queue->rear = newNode;
//     return OK;
// }

// // take out the oldest element from the queue
// status dequeue(linkedQueue *queue, queueElemType *elem)
// {
//     queueNode *frontTemp;
//     if (queue->front == queue->rear)
//         return ERROR;
//     frontTemp = queue->front->next; // since this node contains the first element that is ever stored
//     *elem = frontTemp->data;
//     queue->front->next = frontTemp->next;
//     if (queue->rear == frontTemp)
//         queue->rear = queue->front;
//     free(frontTemp);
//     return OK;
// }

// status queueTraverse(linkedQueue *queue, status (*visit)(queueNode *node))
// {
//     queueNode *p;
//     if (queue->front == queue->rear)
//         return ERROR;
//     p = queue->front->next;
//     while (p)
//     {
//         visit(p);
//         p = p->next;
//     }
//     return OK;
// }

