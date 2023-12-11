// 10.32-荷兰旗问题
// Description
// 荷兰国旗问题：设有一个仅由红、白、蓝三种颜色的条块组成的条块序列。请编写一个时间复杂度为O(n)的算法，使得这些条块按红、白、蓝的顺序排好，即排成荷兰旗图案。

// Input
// 输入条块序列，其中1表示红，2表示白，3表示蓝

// Output
// 输出排序好的序列

// Sample Input 1 
// 2 3 3 3 1 1 1
// Sample Output 1
// 1 1 1 2 3 3 3

#include <bits/stdc++.h>

int main()
{
    int red, white, blue, input, firstOne = true;
    char c;
    red = white = blue = 0;

    while ((c = getchar()) != EOF && c != '\n')
    {
        ungetc(c, stdin);
        scanf("%d%c", &input, &c);
        if (input == 1)
            ++red;
        else if (input == 2)
            ++white;
        else if (input == 3)
            ++blue;
        if (c == '\n' || c == EOF)
            break;
    }

    
    for (int i = 0; i < red; ++i)
    {
        if (firstOne)
        {
            printf("1");
            firstOne = false;
        }
        else
            printf(" 1");
    }
    for (int i = 0; i < white; ++i)
    {
        if (firstOne)
        {
            printf("2");
            firstOne = false;
        }
        else
            printf(" 2");
    }
    for (int i = 0; i < blue; ++i)
    {
        if (firstOne)
        {
            printf("3");
            firstOne = false;
        }
        else
            printf(" 3");
    }
    

    return 0;
}