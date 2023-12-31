// 9.29-有序表查找
// Description
// 已知一非空有序表，表中记录按关键字递增排列，以不带头结点的单循环链表作存储结构，外设两个指针h和t，其中h始终指向关键字最小的节点，t则在表中浮动，其初始位置和h相同，在每次查找之后指向刚查到的节点。查找算法的策略是：首先将给定值K和t->key进行比较，若相等，则查找成功；否则因K小于或大于t->key而从h所指节点或t所指节点的后继节点进行查找，按上述过程编写查找算法。

// Input
// 第一行输入顺序表中的元素，以空格分隔
// 第二行输入需要查找的元素，以空格分隔

// Output
// 对每个需要查找的元素输出是否查找到，能查找到输出1，否则输出0

// Sample Input 1       Sample Output 1
// 2 4 32 64 100        0 1 0
// 1 2 3

#include <bits/stdc++.h>

#define ElemType int

// claim a variable called "struct LNode"
struct LNode
{
    ElemType data;
    struct LNode *next;
};

// make it easier to write, use the name "listnode"
typedef struct LNode listnode;

// function declaration
int create_list_node(listnode **pheader, ElemType data);
int list_malloc(listnode **pnode);
int free_list_node(listnode *node);
int destroy_list(listnode *header);
int delete_list_node(listnode *node_del, listnode *header);
int whether_list_empty(listnode *header);
int list_length(listnode *header);
int list_index(listnode *header, int index);
int list_locate_elem(listnode *header, listnode **pobject, ElemType data, int *compare(ElemType a, ElemType b));
int list_prev_node(listnode *header, listnode *node, listnode **pprev);
int list_insert_after(listnode *node, ElemType data);
int list_insert_before(listnode **pheader, listnode *node, ElemType data);

// create a new List node using the data called "data"
int create_list_node(listnode **pheader, ElemType data)
{
    if (list_malloc(pheader) == -1) // assign the memory needed for the node, and judge whether something wrong happened.
        return -1;
    // memset(*pheader, 0, sizeof(listnode)); // clear the of memory
    (*pheader)->data = data;
    (*pheader)->next = NULL;

    return 0;
}

// allocate a new space to a list node
int list_malloc(listnode **pnode)
{
    listnode *node = NULL;
    node = (listnode *)malloc(sizeof(listnode)); // call the "malloc()" function
    if (node == NULL)                            // if "malloc()" fails, then give the warning and return 1
    {
        // printf("Function malloc() error.\n");
        *pnode = NULL;
        return -1;
    }
    *pnode = node;
    return 0; // if nothing happened, return 0
}

// free a list node
int free_list_node(listnode *node)
{
    free(node);
    return 0;
}

// destroy a whloe list
int destroy_list(listnode *header)
{
    listnode *node = header, *prev;
    if (header == NULL)
    {
        // printf("This list is empty.\n");
        return -1;
    }
    while (node != NULL)
    {
        prev = node;
        node = node->next;
        free_list_node(prev);
    }
    return 0;
}

// delete a list node
int delete_list_node(listnode *node_del, listnode *header)
{
    listnode *prev;
    if (header == NULL) // when the list is empty, node won't ever be detected
    {
        // printf("This list is empty.\n");
        return -1;
    }
    prev = header;                                 // begin the search of "node_del" from "header"
    while (prev != NULL && prev->next != node_del) // if "prev" hasn't reached the end, or the next node is not "node_del", then go on
        prev = prev->next;
    if (prev != NULL) // if the next node is "node_del", delete it
    {
        prev->next = node_del->next;
        free(node_del);
        return 0;
    }
    // printf("The node to be deleted wasn't found in the list.\n");
    return -1;
}

// check if a list is empty or not
int whether_list_empty(listnode *header)
{
    if (header == NULL)
        return 1; // if the list is empty, return 1
    return 0;     // if not, return 0
}

// return the number of elements in a list
int list_length(listnode *header)
{
    listnode *node = header;
    int length = 0;
    while (node != NULL) // if the node hasn't reached the end, count the length
    {
        node = node->next;
        ++length;
    }
    return length;
}

// return the index-th element in a list of length bigger than index
int list_index(listnode *header, int index)
{
    listnode *node;
    // --index; // if you want to let the header be the 1st element, this line is required
    if (header == NULL)
    {
        // printf("This list is empty.\n");
        return -1; // if the list is empty, return 1
    }
    if (index < 0)
    {
        // printf("Index is not valid.\n");
        return -2; // if the list is empty, return 1
    }
    node = header;
    while (index && node->next != NULL) // if the node hasn't reached the end and hasn't reach the index
    {
        node = node->next;
        --index;
    }
    if (!index) // hasn't reached the index
    {
        // printf("Length of the list fewer than index.\n");
        return -1;
    }
    return node->data;
}

// use function "compare()" to give the first element in list with the same data, returning the index and address
int list_locate_elem(listnode *header, listnode **pobject, ElemType data, int (*compare)(ElemType a, ElemType b))
{
    int count = 0;
    listnode *node;     // begin the search of "node_del" from "header"
    if (header == NULL) // when the list is empty, node won't ever be detected
    {
        // printf("This list is empty.\n");
        return -1;
    }
    node = header;
    while (node != NULL && compare(node->data, data) == false) // if "prev" hasn't reached the end, or compare() gives a "unequal", then go on
    {
        ++count;
        node = node->next;
    }
    if (node != NULL) // if compare() gives a "equal", find its address
    {
        *pobject = node;
        return count;
    }
    // printf("The node to be deleted wasn't found in the list.\n");
    return -1;
}

// return the node before in the list
int list_prev_node(listnode *header, listnode *node, listnode **pprev)
{
    listnode *prev;
    if (header == NULL) // when the list is empty, node won't ever be detected
    {
        // printf("This list is empty.\n");
        return -1;
    }
    if (header == node)
    {
        *pprev = NULL;
        // printf("The first ndoe is that node. No previous one before it.\n");
        return -2;
    }
    prev = header;
    while (prev->next != NULL && prev->next != node) // if "prev" hasn't reached the end, and its "next" is not our target, then go on
    {
        prev = prev->next;
    }
    if (prev->next != NULL) // if hasn't reached the end
    {
        *pprev = prev;
        return 0;
    }
    // printf("No valid node found.\n");
    return -1;
}

// add a new node to the list after certain node
int list_insert_after(listnode *node, ElemType data)
{
    listnode *new_node;
    if (create_list_node(&new_node, data) == -1)
    {
        // printf("Insert failed: cannot create new node\n");
        return -1;
    }
    new_node->next = node->next;
    node->next = new_node;
    return 0;
}

// add a new node to the list before certain node
int list_insert_before(listnode **pheader, listnode *node, ElemType data)
{
    int prev_judge;
    listnode *prev, *new_node;
    if ((prev_judge = list_prev_node(*pheader, node, &prev)) == -1)
    {
        // printf("Insert failed: cannot found previous one\n");
        return -1;
    }
    if (prev_judge == -2)
    {
        if (create_list_node(&new_node, data) == -1)
        {
            // printf("Insert failed: cannot create new node\n");
            return -1;
        }
        new_node->next = node; // link 2 nodes together
        *pheader = new_node;   // change the header
    }
    else if (prev_judge == 0)
        list_insert_after(prev, data);
    return 0;
}

// compare two integers
int compareInt(ElemType a, ElemType b)
{
    if (a == b)
        return true;
    return false;
}

int main()
{
    listnode *header = NULL, *node, *prev;
    int data, index, prev_judge, first_judge;
    char op, c;
    int (*compare)(ElemType a, ElemType b) = &compareInt;

    // create the list
    while (scanf("%d%c", &data, &c))
    {
        if (create_list_node(&node, data) == -1)
        {
            // printf("Create list failed.\n");
            return -1;
        }
        if (header == NULL)
            header = node;
        else
        {
            prev = header;
            while (prev->next != NULL)
                prev = prev->next;
            prev->next = node;
        }
        if (c == EOF || c == '\n')
            break;
    }

    // input the data to be searched
    first_judge = false;
    while (scanf("%d%c", &data, &c))
    {
        // search the data
        if (list_locate_elem(header, &node, data, compare) != -1)
        {
            if (first_judge == false)
            {
                printf("1");
                first_judge = true;
            }
            else
                printf(" 1");
        }
        else
        {
            if (first_judge == false)
            {
                printf("0");
                first_judge = true;
            }
            else
                printf(" 0");
        }
        if (c == EOF || c == '\n')
            break;
    }

    putchar('\n');
    // destroy the list
    destroy_list(header);

    return 0;
}