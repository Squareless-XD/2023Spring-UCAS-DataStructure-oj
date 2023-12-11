// 3-改进的迷宫寻路
// Description
// 给定一张地图及入口与出口，人只能走上下左右，但要达到出口时，必须先拿到钥匙，然而钥匙掉落在迷宫中，你需要从中捡取，求拿到钥匙并走出迷宫的最快路线。

// Input
// 输入分为两个部分。第一部分是两个整数X与Y，X<100，Y<100，表示迷宫的行与列，第二部分是迷宫地图，1表示迷宫的墙，0表示人可走，R表示入口，C表示出口，Y表示钥匙。

// Output
// 拿到钥匙并走出迷宫的最快路线(最左上角坐标为1，1)

// Sample Input 1 
// 5 7
// 1R10001
// 1010101
// 1000011
// 101100C
// 1Y00011
// Sample Output 1
// 1 2
// 2 2
// 3 2
// 4 2
// 5 2
// 5 3
// 5 4
// 5 5
// 4 5
// 4 6
// 4 7

#include <bits/stdc++.h>
// #include <vector>

#define STACK_INIT_SIZE 100 // 存储空间初始分配量 单位：stackElemType
#define STACK_INCREMENT 10  // 存储空间分配增量

#define OK 0
#define ERROR 1
#define INFEASIBLE -1
#define OVERFLOW_STACK -2

typedef struct
{
    int x;
    int y;
} point;

typedef point stackElemType;
typedef int status;

typedef struct
{
    stackElemType *base;
    stackElemType *top;
    int stacksize;
} sqStack;

sqStack *stackAlloc(void);
status initStack_Sq(sqStack *stack);
status destroyStack_Sq(sqStack *stack);
status clearStack_Sq(sqStack *stack);
status stackEmpty_Sq(sqStack *stack);
status stackLength_Sq(sqStack *stack);

// 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
status getTop_Sq(sqStack *stack, stackElemType *e);

status push_Sq(sqStack *stack, stackElemType e);
status pop_Sq(sqStack *stack, stackElemType *e);

// 从栈顶到栈底一次对战中每个元素调用函数visit()，一旦visit()失败，则操作失败
status stackTraverse(sqStack *stack, status (*visit)());

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

status clearStack_Sq(sqStack *stack)
{
    stack->top = stack->base;
    memset(stack, 0, sizeof(sqStack));
    return OK;
}

status stackEmpty_Sq(sqStack *stack)
{
    if (stack->top == stack->base)
        return true;
    return false;
}

int stackLength_Sq(sqStack *stack)
{
    return stack->top - stack->base;
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

status stackTraverse(sqStack *stack, status (*visit)(stackElemType *e))
{
    int i;
    if (stack->top == stack->base)
        return ERROR;
    for (i = stack->top - stack->base - 1; i >= 0; --i)
        visit(&stack->base[i]);
    return OK;
}

int main()
{
    std::vector<std::vector<char>> maze;
    int x, y;
    point entrance, key, exit;
    sqStack *stack;

    // initialize the stack
    stack = stackAlloc();
    initStack_Sq(stack);

    // input the size of the maze
    std::cin >> x >> y;

    // input the maze, together find the entrance, key and exit
    for (int i = 0; i < x; ++i)
    {
        std::vector<char> temp;
        for (int j = 0; j < y; ++j)
        {
            char c;
            std::cin >> c;
            temp.push_back(c);
            if (c == 'R')
            {
                entrance.x = i;
                entrance.y = j;
            }
            else if (c == 'Y')
            {
                key.x = i;
                key.y = j;
            }
            else if (c == 'C')
            {
                exit.x = i;
                exit.y = j;
            }
        }
        maze.push_back(temp);
    }

    // push the entrance into the stack
    push_Sq(stack, entrance);

    // find the key
    while (1)
    {
        point temp;
        getTop_Sq(stack, &temp);
        if (temp.x == key.x && temp.y == key.y)
            break;
        if (maze[temp.x][temp.y + 1] == '0' || maze[temp.x][temp.y + 1] == 'Y')
        {
            temp.y += 1;
            push_Sq(stack, temp);
            continue;
        }
        if (maze[temp.x + 1][temp.y] == '0' || maze[temp.x + 1][temp.y] == 'Y')
        {
            temp.x += 1;
            push_Sq(stack, temp);
            continue;
        }
        if (maze[temp.x][temp.y - 1] == '0' || maze[temp.x][temp.y - 1] == 'Y')
        {
            temp.y -= 1;
            push_Sq(stack, temp);
            continue;
        }
        if (maze[temp.x - 1][temp.y] == '0' || maze[temp.x - 1][temp.y] == 'Y')
        {
            temp.x -= 1;
            push_Sq(stack, temp);
            continue;
        }
        pop_Sq(stack, &temp);
    }
    



}