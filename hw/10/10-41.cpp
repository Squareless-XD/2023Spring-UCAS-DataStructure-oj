// 10.41 关键字范围有限时的排序
// Description
// 假设有 1000 个关键字为小于 10000 的整数的记录序列,请设计一种排序方法,要求以尽可能少的比较次数和移动次数实现排序,并按你的设计编出算法。

// Input
// 输入一个无序序列，包含一千个不大于 10000 的数，以空格隔开

// Output
// 输出排序后的序列，以空格隔开

// hint: 最后一个数字之后不要输出空格

#include <bits/stdc++.h>

int main()
{
    std::vector<int> v;
    int n;
    char c;
    while ((c = getchar()) != '\n' && ungetc(c, stdin) && std::cin >> n)
        v.push_back(n);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size() - 1; ++i)
        std::cout << v[i] << ' ';
    std::cout << v[v.size() - 1];
    return 0;
}