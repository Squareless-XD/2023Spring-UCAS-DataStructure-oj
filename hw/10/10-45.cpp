// 10.45-基数排序
// Description
// 试编写算法，借助"计数"实现基数排序。

// Input
// 输入待排序序列

// Output
// 输出排序完成后的序列

// Sample Input 1 
// 120 319 231 232 442 483
// Sample Output 1
// 120 231 232 319 442 483

#include <bits/stdc++.h>
#define MAXLEN 1000
#define ADD 50

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
    int n, i = 0, length;
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

    // Counting sort. get the count of smaller elements in the array
    length = i;
    int *count = new int [length];
    memset(count, 0, sizeof(int) * length);
    for (i = 0; i < length; ++i)
        for (int j = 0; j < length; ++j)
            if (arr[j] < arr[i])
                ++count[i];

    // Radix sort using counting sort
    int *temp = new int [length];
    for (i = 0; i < length; ++i)
        temp[count[i]] = arr[i];

    // Output
    printArr(temp, i);

    return 0;
}
