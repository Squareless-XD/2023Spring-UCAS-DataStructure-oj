// 10.38-2-路归并排序
// Description
// 2-路归并排序的另一策略是，先对待排序序列扫描一遍，找出并划分为若干个最大有序子列，将这些子列作为初始归并段。试写一个算法在链表结构上实现这一策略。

// Input
// 输入分为两行：
// 第一行代表输入的数据元素的个数
// 第二行是输入的所有数据元素，元素之间用空格隔开

// Output
// 输出经过2-路归并排序后的数据元素序列，元素之间用空格隔开（数据元素按从小到大排序）

// Sample Input 1       Sample Output 1
// 5                    1 2 3 4 5
// 2 5 3 1 4

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
        printf("Function malloc() error.\n");
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
        printf("This list is empty.\n");
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
        printf("This list is empty.\n");
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
    printf("The node to be deleted wasn't found in the list.\n");
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
        printf("This list is empty.\n");
        return -1; // if the list is empty, return 1
    }
    if (index < 0)
    {
        printf("Index is not valid.\n");
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
        printf("Length of the list fewer than index.\n");
        return -1;
    }
    return node->data;
}

// use function "compare()" to give the first element in list with the same data, returning the index and address
int list_locate_elem(listnode *header, listnode **pobject, ElemType data, int *compare(ElemType a, ElemType b))
{
    int count = 0;
    listnode *node;     // begin the search of "node_del" from "header"
    if (header == NULL) // when the list is empty, node won't ever be detected
    {
        printf("This list is empty.\n");
        return -1;
    }
    node = header;
    while (node != NULL && compare(node->data, data) != 0) // if "prev" hasn't reached the end, or compare() gives a "unequal", then go on
    {
        ++count;
        node = node->next;
    }
    if (node != NULL) // if compare() gives a "equal", find its address
    {
        *pobject = node;
        return count;
    }
    printf("The node to be deleted wasn't found in the list.\n");
    return -1;
}

// return the node before in the list
int list_prev_node(listnode *header, listnode *node, listnode **pprev)
{
    listnode *prev;
    if (header == NULL) // when the list is empty, node won't ever be detected
    {
        printf("This list is empty.\n");
        return -1;
    }
    if (header == node)
    {
        *pprev = NULL;
        printf("The first ndoe is that node. No previous one before it.\n");
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
    printf("No valid node found.\n");
    return -1;
}

// add a new node to the list after certain node
int list_insert_after(listnode *node, ElemType data)
{
    listnode *new_node;
    if (create_list_node(&new_node, data) == -1)
    {
        printf("Insert failed: cannot create new node\n");
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
        printf("Insert failed: cannot found previous one\n");
        return -1;
    }
    if (prev_judge == -2)
    {
        if (create_list_node(&new_node, data) == -1)
        {
            printf("Insert failed: cannot create new node\n");
            return -1;
        }
        new_node->next = node; // link 2 nodes together
        *pheader = new_node;   // change the header
    }
    else if (prev_judge == 0)
        list_insert_after(prev, data);
    return 0;
}

void MergeSort(listnode **headRef);
listnode *SortedMerge(listnode *a, listnode *b);
void FrontBackSplit(listnode *source, listnode **frontRef, listnode **backRef);



void MergeSort(listnode **headRef)
{
    listnode *head = *headRef;
    listnode *a;
    listnode *b;

    // If length is 0 or 1, then list is sorted
    if (head == NULL || head->next == NULL)
        return;

    // Split head into 'a' and 'b' sublists
    FrontBackSplit(head, &a, &b);

    // Recursively sort the sublists
    MergeSort(&a);
    MergeSort(&b);

    // Merge the two sorted lists together
    *headRef = SortedMerge(a, b);
}

// Split the nodes of the given list into front and back halves,
void FrontBackSplit(listnode *source, listnode **frontRef, listnode **backRef)
{
    listnode *fast;
    listnode *slow;
    slow = source;
    fast = source->next;

    // Advance 'fast' two nodes, and advance 'slow' one node
    // so that 'slow' points to the middle node
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' is before the midpoint in the list, so split it in two
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

// merge two sorted lists recursively
listnode *SortedMerge(listnode *a, listnode *b)
{
    listnode *result = NULL;

    // if either list is empty, return the other
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    // Pick either a or b, and recur
    if (a->data <= b->data)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return result;
}

int main()
{
    int n, data;
    listnode *header = NULL, *node = NULL, *prev = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &data);
        if (create_list_node(&node, data) == -1)
        {
            printf("Create list node failed.\n");
            return -1;
        }
        if (header == NULL)
            header = node;
        else
            prev->next = node;
        prev = node;
    }

    // merge sort
    MergeSort(&header);

    // print the list
    node = header;
    while (node->next != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("%d\n", node->data);
    destroy_list(header);
    return 0;
}