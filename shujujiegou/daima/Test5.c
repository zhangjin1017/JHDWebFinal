#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define MAX_VERTICES 100 //假设图有100个顶点
#define MAX_WEIGHT 32767 //加权图（网）不邻接时为10000，但输出为“∞”
typedef int boole;
typedef int ElemType;
boole visited[MAX_VERTICES]; //访问标志数组
//图结构
typedef struct
{
    char Vertices[MAX_VERTICES];                     //顶点信息的数组
    int AdjacencyMatrix[MAX_VERTICES][MAX_VERTICES]; //边信息的数组。
    int numV;                                        //当前的顶点数
    int numA;                                        //当前的边数
} AdMatrix;
//队列结构
typedef struct Qnode
{
    ElemType data;
    struct Qnode *next;
} Qnode, *Qptr; //定义节点
//队列
typedef struct LINKQUEUE
{
    Qptr front;
    Qptr rear;
} LinkQueue; //定义队首、队尾指针
//图的生成函数
void CreateGraph(AdMatrix *G)
{
    int n, e, vi, vj, w;
    printf("请输入图的顶点数和边数:");
    scanf("%d%d", &n, &e);
    getchar();
    G->numV = n;
    G->numA = e;
    // AdjacencyMatrix初始化
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //无权图的初始化
            G->AdjacencyMatrix[i][j] = 0;
        }
    }
    printf("请依次输入%d个顶点的信息:", n);
    // Vertices数组的创建
    for (int i = 0; i < G->numV; i++)
    {
        scanf("%c", &G->Vertices[i]);
    }
    getchar();
    printf("请依次输入%d条边的信息i(横坐标),j(纵坐标),w(权重):\n", e);
    // AdjacencyMatrix数组的建立
    for (int i = 0; i < G->numA; i++)
    {
        scanf("%d%d%d", &vi, &vj, &w);
        G->AdjacencyMatrix[vi - 1][vj - 1] = w;
        G->AdjacencyMatrix[vj - 1][vi - 1] = w; //无向图具有对称性，通过其实现；有向图不需要这条语句。
    }
}
//输出邻接矩阵的信息
void ShowGraph(AdMatrix *G)
{
    int i, j;
    // printf("-----输出顶点的信息-----");
    // for (i = 0; i < G->numV; i++)
    // {
    //     printf("%c ", G->Vertices[i]);
    // }
    printf("-----邻接矩阵-----\n");
    printf("  ");
    for (i = 0; i < G->numV; i++) //输出顶点信息
    {
        printf("%c ", G->Vertices[i]);
    }
    for (i = 0; i < G->numV; i++) //输出邻接矩阵
    {
        printf("\n%c ", G->Vertices[i]);
        for (j = 0; j < G->numV; j++) //
        {
            if (G->AdjacencyMatrix[i][j] == MAX_WEIGHT)
            {
                printf("%s ", "∞");
            }
            else
            {
                printf("%d ", G->AdjacencyMatrix[i][j]);
            }
        }
        // printf("\n");
    }
}
// 深度优先遍历
void DFS(AdMatrix *G, int i)
{
    int j;
    visited[i] = 1; //访问过的结点标记为1
    printf("%c ", G->Vertices[i]);
    for (j = 0; j < G->numV; j++) //对所有的邻接点进行深度优先遍历
    {
        if (G->AdjacencyMatrix[i][j] == 1 && !visited[j])
        {
            DFS(G, j);
        }
    }
}
//深度优先遍历
void DFStraverse(AdMatrix *G)
{
    for (int i = 0; i < G->numV; i++)
    {
        visited[i] = 0; //初始化标记数组为0
    }
    for (int i = 0; i < G->numV; i++)
    {
        if (!visited[i]) //没有访问过，进行深度优先遍历
        {
            DFS(G, i);
        }
    }
}
//广度优先遍历—用一个队列实现
void InitQueue(LinkQueue *q) //队列初始化
{
    //定义头结点，队首队尾都指向头结点
    Qptr firstnode = (Qptr)malloc(sizeof(Qnode));
    q->front = q->rear = firstnode;
    if (!q->front)
    {
        return;
    }
    q->front->next = NULL;
}
//入队列
void PushQueue(LinkQueue *q, ElemType e)
{
    //在队尾插入元素
    Qptr p = (Qptr)malloc(sizeof(Qnode));
    if (!p)
    {
        return;
    }
    p->data = e;       //元素值
    p->next = NULL;    //指向下一个元素
    q->rear->next = p; //队尾指针指向新元素
    q->rear = p;       //更新队尾指针
}
//出队列
void DetQueue(LinkQueue *q, ElemType *e)
{
    //出队列在队首进行
    if (q->front == q->rear)
    {
        printf("队列中无元素！\n");
        return;
    }
    Qptr p = q->front->next;  //获取队首元素
    e = &(p->data);           //获取队首元素的值
    q->front->next = p->next; //队首指针指向下一个元素
    if (q->rear == p)         //如果出队列的元素是队尾元素，更新队尾指针
    {
        q->rear = q->front; //队尾指针指向队首
    }
    free(p);
}
//检验是否为空
int QueueEmpty(LinkQueue *q)
{
    if (q->front == q->rear)
        return 0;
    else
        return 1;
}
//广度优先遍历
void BFSTraverse(AdMatrix *G)
{
    int k = 0;
    LinkQueue Q;
    InitQueue(&Q);
    for (int i = 0; i < G->numV; i++) //初始化标记数组
    {
        visited[i] = 0; //初始化标记数组
    }
    for (int i = 0; i < G->numV; i++)
    {
        if (!visited[i]) //没有访问过，进行广度优先遍历
        {
            visited[i] = 1;                //标记为已访问
            printf("%c ", G->Vertices[i]); //输出顶点信息
            PushQueue(&Q, i);              //入队列
        }
        while (QueueEmpty(&Q)) //队列不为空
        {
            DetQueue(&Q, &k); //出队列
            for (int j = 0; j < G->numV; j++)
            {
                if (G->AdjacencyMatrix[k][j] == 1 && !visited[j]) //对所有的邻接点进行广度优先遍历
                {
                    visited[j] = 1;                //标记为已访问
                    printf("%c ", G->Vertices[j]); //输出顶点信息
                    PushQueue(&Q, j);              //入队列
                }
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    AdMatrix G;
    CreateGraph(&G);
    ShowGraph(&G);
    printf("\n深度优先遍历:\n");
    DFStraverse(&G);
    printf("\n广度优先遍历：\n");
    BFSTraverse(&G);
    return 0;
}
