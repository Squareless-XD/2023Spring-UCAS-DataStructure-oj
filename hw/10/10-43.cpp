// 10.43-计数排序
// Description
// 已知记录序列a[1..n]中的关键字各不相同，可按如下所述实现计数排序：另设数组c[1..n]，对每个记录a[i]，统计序列中关键字比它小的记录个数存于c[i]，则c[i]=0的记录必为关键字最小的记录，然后依c[i]值的大小对a中的记录进行重新排列，试编写算法实现上述排序方法。

// Input
// 输入记录序列a

// Output
// 输出c中每个元素

// Sample Input 1 
// 4 3 10 2 1
// Sample Output 1
// 3 2 4 1 0

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

    printArr(count, i);

    return 0;
}
