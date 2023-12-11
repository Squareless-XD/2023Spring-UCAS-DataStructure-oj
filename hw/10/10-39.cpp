// 10.39 有序序列归并
// Description
// 已知两个有序序列 (a_1, a_2, ... , a_m) 和 (a_{m+1}, a_{m+2}, ... , a_n)，并且其中一个序列的记录个数少于s, s=\ceil{\sqrt{n}}。试写一个算法，用 O(n) 时间和 O(1) 附加空间完成这两个有序序列的合并。
// 提示：有大样例，请严格按照时间复杂度来。

// Input
// 输入为两行，每行为一个有序序列，序列内的数字用空格隔开。

// Output
// 排序后的序列，序列内的数字用空格隔开

// Sample Input 1
// 1 3 5
// 2 4
// Sample Output 1
// 1 2 3 4 5

#include <bits/stdc++.h>

// Driver Code
int main()
{
    std::vector<int> v1, v2, vout;
    int i;

    // Input data
    int n;
    char c;
    while ((c = getchar()) != '\n' && c != EOF && ungetc(c, stdin) && std::cin >> n)
        v1.push_back(n);
    while ((c = getchar()) != '\n' && c != EOF && ungetc(c, stdin) && std::cin >> n)
        v2.push_back(n);
    
    // Merge
    int len1 = v1.size(), len2 = v2.size();
    int i1 = 0, i2 = 0;
    while (i1 < len1 || i2 < len2)
    {
        if (i1 == len1)
            vout.push_back(v2[i2++]);
        else if (i2 == len2)
            vout.push_back(v1[i1++]);
        else if (v1[i1] < v2[i2])
            vout.push_back(v1[i1++]);
        else
            vout.push_back(v2[i2++]);
    }

    // Output
    int lenout = vout.size();
    for (i = 0; i < lenout - 1; ++i)
        std::cout << vout[i] << ' ';
    std::cout << vout[i];

    return 0;
}