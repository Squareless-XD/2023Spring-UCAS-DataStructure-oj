// 10.30-快排非递归
// Description
// 按照下述原则编写快排的非递归算法：
// （1）一趟排序之后，先对长度较短的子序列进行排序，且将另一子序列的上、下界入栈保存
// （2）若待排序记录数<=3，则不再进行分割，而是直接进行比较排序

// Input
// 输入待排序列

// Output
// 输出排序完成后的序列

// Sample Input 1
// 18 39 21 23 9 1
// Sample Output 1
// 1 9 18 21 23 39

#include <bits/stdc++.h>
#define MAXLEN 1000
#define ADD 50

// swap two integers
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// partition a piece of array into two part, and return the index of the pivot
int partition(int arr[], int low, int high)
{
    int x = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortIter(int arr[], int low, int high)
{
    // Create an auxiliary stack
    int stack[high - low + 1];
    // initialize top of stack
    int top = -1;
    // partIndex is partitioning index, arr[p] is now at right place
    int partIndex;

    // push initial values of low and high to stack
    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0)
    {
        // pop high and low
        high = stack[top--];
        low = stack[top--];

        // set pivot element at its correct position in sorted array
        partIndex = partition(arr, low, high);
         
        // If there are elements on left side of pivot, then push left side to stack
        if (partIndex - 1 > low)
        {
            stack[++top] = low;
            stack[++top] = partIndex - 1;
        }

        // If there are elements on right side of pivot, then push right side to stack
        if (partIndex + 1 < high)
        {
            stack[++top] = partIndex + 1;
            stack[++top] = high;
        }
    }
}

// A utility function to print contents of arr
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n - 1; ++i)
        std::cout << arr[i] << " ";
    std::cout << arr[i];
}

int main()
{
    int *arr = new int [MAXLEN];
    int n, i = 0;
    char c;
    while ((c = getchar()) != '\n' && c != EOF && ungetc(c, stdin) && std::cin >> n)
    {
        arr[i++] = n;
        if (i == MAXLEN)
        {
            int *newbuf = new int [sizeof(arr) / sizeof(int) + ADD];
            memcpy(newbuf, arr, sizeof(arr));
            delete arr;
            arr = newbuf;
        }
    }
    quickSortIter(arr, 0, i - 1);
    printArr(arr, i);

    return 0;
}
