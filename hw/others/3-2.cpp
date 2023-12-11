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

#include <string.h>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

#define MAX_INT_32bit 0x7fffffff

typedef struct
{
    int x;
    int y;
} point;

typedef struct
{
    point prev;
    point next;
} pathPair;

// 顶点
class Node
{
public:
    Node(char data = 0)
    {
        m_cData = data;
        m_bVisited = false;
    }
    Node(const Node &node)
    {
        if (this == &node)
            return;
        *this = node;
    }

    Node &operator=(const Node &node)
    {
        if (this == &node)
            return *this;
        this->m_cData = node.m_cData;
        this->m_bVisited = node.m_bVisited;
        return *this;
    }

public:
    char m_cData;    // 数据
    bool m_bVisited; // 是否访问
};

// 边
class Edge
{
public:
    Edge(int nodeIndexA = 0, int nodeIndexB = 0, int weightValue = 0) : m_iNodeIndexA(nodeIndexA),
                                                                        m_iNodeIndexB(nodeIndexB),
                                                                        m_iWeightValue(weightValue),
                                                                        m_bSelected(false) {}
    Edge(const Edge &edge)
    {
        if (this == &edge)
            return;
        *this = edge;
    }

    Edge &operator=(const Edge &edge)
    {
        if (this == &edge)
            return *this;
        this->m_iNodeIndexA = edge.m_iNodeIndexA;
        this->m_iNodeIndexB = edge.m_iNodeIndexB;
        this->m_iWeightValue = edge.m_iWeightValue;
        this->m_bSelected = edge.m_bSelected;
        return *this;
    }

public:
    int m_iNodeIndexA;  // 头顶点
    int m_iNodeIndexB;  // 尾顶点
    int m_iWeightValue; // 权重
    bool m_bSelected;   // 是否被选中
};

// 图
class CMap
{

private:
    int m_iCapacity;    // 顶点总数
    int m_iNodeCount;   // 当前顶点数量
    Node *m_pNodeArray; // 顶点集合
    int *m_pMatrix;     // 邻接距阵
    Edge *m_pEdgeArray; // 最小生成树边集合
public:
    CMap(int iCapacity)
    {
        m_iCapacity = iCapacity;
        m_iNodeCount = 0;
        m_pNodeArray = new Node[m_iCapacity];
        m_pMatrix = new int[m_iCapacity * m_iCapacity];
        memset(m_pMatrix, 0, m_iCapacity * m_iCapacity * sizeof(int));
        m_pEdgeArray = new Edge[m_iCapacity - 1];
    }
    ~CMap(void)
    {
        delete[] m_pNodeArray;
        delete[] m_pMatrix;
        delete[] m_pEdgeArray;
    }

private:
    // 广度遍历具体实现
    void breadthFirstTraverseImpl(vector<int> preVec)
    {
        int val = 0;
        vector<int> curVec;
        for (int i = 0; i < (int)preVec.size(); i++)
        {
            for (int j = 0; j < m_iCapacity; j++)
            {
                getValueFromMatrix(preVec[i], j, val);
                if (/*1 == val*/ 0 != val)
                {
                    if (m_pNodeArray[j].m_bVisited)
                        continue;
                    cout << m_pNodeArray[j].m_cData << " ";
                    m_pNodeArray[j].m_bVisited = true;
                    curVec.push_back(j);
                }
                else
                    continue;
            }
        }

        if (curVec.empty())
            return;
        else
            breadthFirstTraverseImpl(curVec);
    }

    // 取最小边
    int getMinEdge(const vector<Edge> &edgeVec)
    {
        int min = 0, minEdge = 0;

        for (int i = 0; i < (int)edgeVec.size(); i++)
        {
            if (edgeVec[i].m_bSelected)
                continue;
            min = edgeVec[i].m_iWeightValue;
            minEdge = i;
        }

        for (int i = 0; i < (int)edgeVec.size(); i++)
        {
            if (edgeVec[i].m_bSelected)
                continue;
            if (min > edgeVec[i].m_iWeightValue)
            {
                min = edgeVec[i].m_iWeightValue;
                minEdge = i;
            }
        }

        if (0 == min)
            return -1;

        return minEdge;
    }

    bool isInSet(const vector<int> &nodeSet, int target)
    {
        for (int i = 0; i < (int)nodeSet.size(); i++)
        {
            if (nodeSet[i] == target)
                return true;
        }

        return false;
    }

    void mergeNodeSet(vector<int> &nodeSetA, const vector<int> &nodeSetB)
    {
        for (size_t i = 0; i < (int)nodeSetB.size(); i++)
        {
            nodeSetA.push_back(nodeSetB[i]);
        }
    }

public:
    // 添加顶点
    void addNode(Node *node)
    {
        assert(node);
        m_pNodeArray[m_iNodeCount].m_cData = node->m_cData;
        m_iNodeCount++;
    }
    // 将顶点访问设置默认
    void resetNode()
    {
        for (int i = 0; i < m_iNodeCount; i++)
            m_pNodeArray[i].m_bVisited = false;
    }
    // 设置权重-有向图
    bool setValueToMatrixForDirectedGraph(int row, int col, int val = 1)
    {
        if (row < 0 || row >= m_iCapacity)
            return false;
        if (col < 0 || col >= m_iCapacity)
            return false;
        m_pMatrix[row * m_iCapacity + col] = val;
        return true;
    }

    // 设置权重-无向图
    bool setValueToMatrixForUndirectedGraph(int row, int col, int val = 1)
    {
        if (row < 0 || row >= m_iCapacity)
            return false;
        if (col < 0 || col >= m_iCapacity)
            return false;
        m_pMatrix[row * m_iCapacity + col] = val;
        m_pMatrix[col * m_iCapacity + row] = val;
        return true;
    }
    // 获取权重
    bool getValueFromMatrix(int row, int col, int &val)
    {
        if (row < 0 || row >= m_iCapacity)
            return false;
        if (col < 0 || col >= m_iCapacity)
            return false;
        val = m_pMatrix[row * m_iCapacity + col];
        return true;
    }
    // 打印矩阵
    void printMatrix()
    {
        for (int i = 0; i < m_iCapacity; i++)
        {
            for (int j = 0; j < m_iCapacity; j++)
                cout << m_pMatrix[i * m_iCapacity + j] << " ";
            cout << endl;
        }
    }

    // 深度遍历
    void depthFirstTraverse(int index)
    {
        int val = 0;
        cout << m_pNodeArray[index].m_cData << " ";
        m_pNodeArray[index].m_bVisited = true;

        for (int i = 0; i < m_iCapacity; i++)
        {
            getValueFromMatrix(index, i, val);
            if (/*1 == val*/ 0 != val)
            {
                if (m_pNodeArray[i].m_bVisited)
                    continue;
                depthFirstTraverse(i);
            }
            else
                continue;
        }
    }

    // 广度遍历
    void breadthFirstTraverse(int index)
    {
        cout << m_pNodeArray[index].m_cData << " ";
        m_pNodeArray[index].m_bVisited = true;

        vector<int> curVec;
        curVec.push_back(index);

        breadthFirstTraverseImpl(curVec);
    }

    // 求最小生成树-普里斯算法
    void primTree(int index)
    {
        int val = 0;
        int iEdgeCount = 0;
        vector<Edge> edgeVec; // 待选边集合

        // 从传入点开始找
        vector<int> nodeIndexVec;
        nodeIndexVec.push_back(index);

        // 结束条件：边数=顶点数-1
        while (iEdgeCount < m_iCapacity - 1)
        {
            // 查找传入点的符合要求（权重不为0且目的点没有被访问）边
            int row = nodeIndexVec.back();
            cout << m_pNodeArray[row].m_cData << endl;
            m_pNodeArray[row].m_bVisited = true;

            for (int i = 0; i < m_iCapacity; i++)
            {
                getValueFromMatrix(row, i, val);
                if (0 == val)
                    continue;
                if (m_pNodeArray[i].m_bVisited)
                    continue;
                Edge edge(row, i, val);
                edgeVec.push_back(edge);
            }

            // 取出最小边
            int retIndex = getMinEdge(edgeVec);
            if (-1 != retIndex)
            {
                // 存储选中边
                edgeVec[retIndex].m_bSelected = true;
                m_pEdgeArray[iEdgeCount] = edgeVec[retIndex];
                cout << m_pNodeArray[m_pEdgeArray[iEdgeCount].m_iNodeIndexA].m_cData << " - ";
                cout << m_pNodeArray[m_pEdgeArray[iEdgeCount].m_iNodeIndexB].m_cData << " (";
                cout << m_pEdgeArray[iEdgeCount].m_iWeightValue << ") " << endl;
                iEdgeCount++;

                int iNodeIndex = edgeVec[retIndex].m_iNodeIndexB;
                // 设置点被访问
                m_pNodeArray[iNodeIndex].m_bVisited = true;
                // 存入目的点递归查找
                nodeIndexVec.push_back(iNodeIndex);
            }
        }
    }

    // 最小生成树-克鲁斯卡尔算法
    void kruskalTree()
    {
        int val = 0;
        int edgeCount = 0;

        // 定义存放节点集合数组
        vector<vector<int>> nodeSets;

        // 第一步、取出所有边
        vector<Edge> edgeVec;
        for (int i = 0; i < m_iCapacity; i++)
        {
            for (int j = i + 1; j < m_iCapacity; j++)
            {
                getValueFromMatrix(i, j, val);
                if (0 == val)
                    continue;
                if (m_pNodeArray[i].m_bVisited)
                    continue;
                Edge edge(i, j, val);
                edgeVec.push_back(edge);
            }
        }

        // 第二步、从所有边中取出组成最小生成树的边
        // 1、算法结束条件：边数=顶点数-1
        while (edgeCount < m_iCapacity - 1)
        {
            // 2、从边集合中找出最小边
            int retIndex = getMinEdge(edgeVec);
            if (-1 != retIndex)
            {
                edgeVec[retIndex].m_bSelected = true;

                // 3、找出最小边连接点
                int nodeAIndex = edgeVec[retIndex].m_iNodeIndexA;
                int nodeBIndex = edgeVec[retIndex].m_iNodeIndexB;

                // 4、找出点所在集合
                bool nodeAInSet = false;
                bool nodeBInSet = false;
                int nodeAInSetLabel = -1;
                int nodeBInSetLabel = -1;

                for (int i = 0; i < (int)nodeSets.size(); i++)
                {
                    nodeAInSet = isInSet(nodeSets[i], nodeAIndex);
                    if (nodeAInSet)
                        nodeAInSetLabel = i;
                }

                for (int i = 0; i < (int)nodeSets.size(); i++)
                {
                    nodeBInSet = isInSet(nodeSets[i], nodeBIndex);
                    if (nodeBInSet)
                        nodeBInSetLabel = i;
                }

                // 5、根据点集合的不同做不同处理
                if (nodeAInSetLabel == -1 && nodeBInSetLabel == -1)
                {
                    vector<int> vec;
                    vec.push_back(nodeAIndex);
                    vec.push_back(nodeBIndex);
                    nodeSets.push_back(vec);
                }
                else if (nodeAInSetLabel == -1 && nodeBInSetLabel != -1)
                {
                    nodeSets[nodeBInSetLabel].push_back(nodeAIndex);
                }
                else if (nodeAInSetLabel != -1 && nodeBInSetLabel == -1)
                {
                    nodeSets[nodeAInSetLabel].push_back(nodeBIndex);
                }
                else if (-1 != nodeAInSetLabel && -1 != nodeBInSetLabel && nodeAInSetLabel != nodeBInSetLabel)
                {
                    // mergeNodeSet(nodeSets[nodeAInSetLabel], nodeSets[nodeBInSetLabel]);
                    nodeSets[nodeAInSetLabel].insert(nodeSets[nodeAInSetLabel].end(),
                                                     nodeSets[nodeBInSetLabel].begin(),
                                                     nodeSets[nodeBInSetLabel].end());
                    for (int k = nodeBInSetLabel; k < (int)nodeSets.size() - 1; k++)
                    {
                        nodeSets[k] = nodeSets[k + 1];
                    }
                }
                else if (nodeAInSetLabel != -1 && nodeBInSetLabel != -1 && nodeAInSetLabel == nodeBInSetLabel)
                {
                    continue;
                }

                m_pEdgeArray[edgeCount] = edgeVec[retIndex];
                edgeCount++;

                cout << m_pNodeArray[edgeVec[retIndex].m_iNodeIndexA].m_cData << " - ";
                cout << m_pNodeArray[edgeVec[retIndex].m_iNodeIndexB].m_cData << " (";
                cout << edgeVec[retIndex].m_iWeightValue << ") " << endl;
            }
        }
    }

    // 最短路径-迪杰斯特拉算法
    // sourceVex:源点 pairInShortPath:算法中间结果, 可能在最短路径中的两个相邻的点
    void Dijkstra(std::vector<pathPair> &pairInShortPath, const int sourceVex, const int width)
    {
        std::vector<pathPair> pairStore;
        std::vector<int> vexVisited;
        std::vector<int> vexPathLen;
        pathPair tempPair;
        int temp, minLen, minLenVex, i, j, k;

        vexVisited = std::vector<int>(m_iCapacity, false);
        // initialize vertex distance
        vexPathLen = std::vector<int>(m_iCapacity, MAX_INT_32bit);
        vexPathLen[sourceVex] = 0;

        // // check every edge of the source vertex, and add them to pairStore
        // for (i = 0; i < m_iCapacity; ++i)
        // {
        //     if (getValueFromMatrix(sourceVex, i, temp) == true && temp > 0)
        //     {
        //         tempPair.prev.x = sourceVex / width;
        //         tempPair.prev.y = sourceVex % width;
        //         tempPair.next.x = i / width;
        //         tempPair.next.y = i % width;
        //         pairStore.push_back(tempPair);
        //     }
        // }

        tempPair.prev.x = sourceVex / width;
        tempPair.prev.y = sourceVex % width;
        tempPair.next.x = sourceVex / width;
        tempPair.next.y = sourceVex % width;
        // Dijkstra algorithm
        for (i = 0; i < m_iCapacity; ++i) // while S != V
        {
            // find a minimum L(u)
            minLen = MAX_INT_32bit;
            for (j = 0; j < m_iCapacity; ++j)
            {
                if (vexVisited[j] == true)
                    continue;
                if (minLen > vexPathLen[j])
                {
                    minLen = vexPathLen[j];
                    minLenVex = j;
                    // find if j is in pairStore
                    for (k = 0; k < pairStore.size(); ++k)
                    {
                        if (pairStore[k].next.x == j / width && pairStore[k].next.y == j % width)
                        {
                            tempPair = pairStore[k];
                            break;
                        }
                    }
                }
            }
            if (minLen == MAX_INT_32bit)
                break;

            // add the tempPair into pairInShortPath
            pairInShortPath.push_back(tempPair);

            // erase the tempPair from pairStore
            for (k = 0; k < pairStore.size(); ++k)
            {
                if (pairStore[k].next.x == tempPair.next.x && pairStore[k].next.y == tempPair.next.y)
                {
                    pairStore.erase(pairStore.begin() + k);
                    break;
                }
            }

            // add {u} into S
            vexVisited[minLenVex] = true;

            // refresh all v \notin S for there L(v)
            for (j = 0; j < m_iCapacity; ++j)
            {
                if (vexVisited[j] == true)
                    continue;
                if (getValueFromMatrix(minLenVex, j, temp) == true && temp > 0 && minLen + temp < vexPathLen[j])
                {
                    vexPathLen[j] = minLen + temp;

                    // judge if j is in pairStore. if it is, then refresh the pairStore. if not, then add it into pairStore
                    for (k = 0; k < pairStore.size(); ++k)
                    {
                        if (pairStore[k].next.x == j / width && pairStore[k].next.y == j % width)
                        {
                            pairStore[k].prev.x = minLenVex / width;
                            pairStore[k].prev.y = minLenVex % width;
                            break;
                        }
                    }
                    if (k == pairStore.size())
                    {
                        tempPair.prev.x = minLenVex / width;
                        tempPair.prev.y = minLenVex % width;
                        tempPair.next.x = j / width;
                        tempPair.next.y = j % width;
                        pairStore.push_back(tempPair);
                    }
                }
            }
        }

        // // print out the results
        // for (i 0 1; i < m_iNodeCount; ++i)
        // {
        //     if (i == sourceVex)
        //         continue;
        //     printf("%d", vexPathLen[i]);
        //     if (i != m_iNodeCount)
        //         putchar(',');
        // }
        // putchar('\n');
    }
};

#define STACK_INIT_SIZE 100 // 存储空间初始分配量 单位：stackElemType
#define STACK_INCREMENT 10  // 存储空间分配增量

#define OK 0
#define ERROR 1
#define INFEASIBLE -1
#define OVERFLOW_STACK -2

typedef pathPair stackElemType;
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

// use a vector pairInShortPath to find the shortest path from the source vertex to the destination vertex
// the pairInShortPath is the result of Dijkstra algorithm
// use a stack to store the path
// since one vertex will only appear once in pathPair.y, a whild-loop is all we need
status DFSinPairs(std::vector<pathPair> &pairInShortPath, sqStack *pathStack, int srcVex, int dstVex, const int width)
{
    int i, dstTemp;
    stackElemType tempElem;
    tempElem.prev.x = dstVex / width;
    tempElem.prev.y = dstVex % width;

    while (dstTemp != srcVex)
    {
        for (i = 0; i < pairInShortPath.size(); ++i)
        {
            if (pairInShortPath[i].next.x == tempElem.prev.x && pairInShortPath[i].next.y == tempElem.prev.y)
            {
                tempElem = pairInShortPath[i];
                break;
            }
        }
        if (i == pairInShortPath.size())
            return ERROR;
        dstTemp = tempElem.prev.x * width + tempElem.prev.y;
        push_Sq(pathStack, tempElem);
    }
    return OK;
}

int inBounds(int i, int j, int x, int y)
{
    if (i >= 0 && i < x && j >= 0 && j < y)
        return true;
    return false;
}

int isValid(char c)
{
    if (c == '0' || c == 'R' || c == 'Y' || c == 'C')
        return true;
    return false;
}


int main()
{
    std::vector<std::vector<char>> maze;
    int x, y;
    point entrance, key, exit;
    // sqStack *stack;

    // // initialize the stack
    // stack = stackAlloc();
    // initStack_Sq(stack);

    // input the size of the maze
    std::cin >> x >> y; // x is the number of rows, y is the number of columns

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

    // use a graph to store the maze.
    // the graph is an undirected graph. only the '0', 'R', 'Y' adn 'C' can be connected.
    // 'C' is temporarily connected, and will be disconnected later.
    // if two points are adjacent in the matrix, then they are connected in the graph.
    // if two points are connected, the weight is 1.
    CMap graph(x * y); // the number of points is x * y
    char c;
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            if (isValid(maze[i][j]))
            {
                graph.addNode(new Node(maze[i][j]));
                if (inBounds(i, j + 1, x, y) && isValid(maze[i][j + 1]))
                    graph.setValueToMatrixForUndirectedGraph(i * y + j, i * y + (j + 1), 1);
                if (inBounds(i, j - 1, x, y) && isValid(maze[i][j - 1]))
                    graph.setValueToMatrixForUndirectedGraph(i * y + j, i * y + (j - 1), 1);
                if (inBounds(i + 1, j, x, y) && isValid(maze[i + 1][j]))
                    graph.setValueToMatrixForUndirectedGraph(i * y + j, (i + 1) * y + j, 1);
                if (inBounds(i - 1, j, x, y) && isValid(maze[i - 1][j]))
                    graph.setValueToMatrixForUndirectedGraph(i * y + j, (i - 1) * y + j, 1);
            }
        }
    }

/*
3 3
0Y0
R10
0C0
*/
    // after adding all the edges, we can use the breadth first search to find the shortest path from the entrance to the key.

    // find the shortest distance in the graph between two points, using dijkstra algorithm
    // it will create several pairs of vertexes, noted with the distance between them
    // these pairs are all consisted of two adjacent vertexes
    // the distance between two vertexes is the weight of the edge between them
    // use DFS on them to get the shortest path

    // initialize the distance array
    std::vector<int> distance;

    // initialize the previous vertex array
    std::vector<int> previous;

    // graph.printMatrix();


    /*
    class CMap
    {

    private:
        int m_iCapacity; //顶点总数
        int m_iNodeCount; //当前顶点数量
        Node *m_pNodeArray; //顶点集合
        int *m_pMatrix; //邻接距阵
        Edge *m_pEdgeArray; //最小生成树边集合
    */
    // void Dijkstra(aLGraph *graph, vexType sourceVex)

    int srcVex = entrance.x * y + entrance.y; // the source vertex
    int keyVex = key.x * y + key.y;           // the key vertex
    int exitVex = exit.x * y + exit.y;        // the exit vertex
    std::vector<pathPair> pairInShortPath;
    sqStack *pathStack;
    stackElemType tempElem;

    // initialize the stack
    pathStack = stackAlloc();
    initStack_Sq(pathStack);

    // find the shortest path from the key to the exit
    graph.Dijkstra(pairInShortPath, keyVex, y);
    DFSinPairs(pairInShortPath, pathStack, keyVex, exitVex, y);

    // clear the vector. don't clear the stack
    pairInShortPath.clear();

    // // connect the exit with adjacent points
    // if (inBounds(exit.x, exit.y + 1, x, y) && isValid(maze[exit.x][exit.y + 1]))
    // {
    //     graph.setValueToMatrixForUndirectedGraph(exit.x * y + exit.y, exit.x * y + (exit.y + 1), 0);
    //     graph.setValueToMatrixForUndirectedGraph(exit.x * y + (exit.y + 1), exit.x * y + exit.y, 0);
    // }
    // if (inBounds(exit.x, exit.y - 1, x, y) && isValid(maze[exit.x][exit.y - 1]))
    // {
    //     graph.setValueToMatrixForUndirectedGraph(exit.x * y + exit.y, exit.x * y + (exit.y - 1), 0);
    //     graph.setValueToMatrixForUndirectedGraph(exit.x * y + (exit.y - 1), exit.x * y + exit.y, 0);
    // }
    // if (inBounds(exit.x + 1, exit.y, x, y) && isValid(maze[exit.x + 1][exit.y]))
    // {
    //     graph.setValueToMatrixForUndirectedGraph(exit.x * y + exit.y, (exit.x + 1) * y + exit.y, 0);
    //     graph.setValueToMatrixForUndirectedGraph((exit.x + 1) * y + exit.y, exit.x * y + exit.y, 0);
    // }
    // if (inBounds(exit.x - 1, exit.y, x, y) && isValid(maze[exit.x - 1][exit.y]))
    // {
    //     graph.setValueToMatrixForUndirectedGraph(exit.x * y + exit.y, (exit.x - 1) * y + exit.y, 0);
    //     graph.setValueToMatrixForUndirectedGraph((exit.x - 1) * y + exit.y, exit.x * y + exit.y, 0);
    // }


    // find the shortest path from the entrance to the key
    graph.Dijkstra(pairInShortPath, srcVex, y);
    DFSinPairs(pairInShortPath, pathStack, srcVex, keyVex, y);

    std::cout << entrance.x + 1 << " " << entrance.y + 1 << std::endl;
    // print out the path from the entrance to the exit
    while (!stackEmpty_Sq(pathStack))
    {
        pop_Sq(pathStack, &tempElem);
        std::cout << tempElem.next.x + 1 << " " << tempElem.next.y + 1 << std::endl;
    }


    // destroy the stack
    destroyStack_Sq(pathStack);

    return 0;
}

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



/*

4 7
1R10001
101010Y
1000011
101100C

*/