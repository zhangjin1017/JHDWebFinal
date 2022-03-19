#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
typedef struct Node
{
    char city[10]; //城市名
    int x;         // x轴位置
    int y;         // y轴位置
    struct Node *next;
} Node, *LinkList;

//初始化单链表
void InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
}
//用尾插法建立单链表
void CreateFormTail(LinkList L)
{
    Node *r, *s;
    int flag = 1;
    r = L;
    char city[10];
    int x;
    int y;
    char *jieshu = "结束";
    while (flag)
    {
        printf("请输入城市名: (如果输入'结束',则结束)\n");
        scanf("%s", city);

        if (strcmp(city, jieshu) != 0) //如果输入'结束'，则结束
        {
            printf("请输入x坐标:\n");
            scanf("%d", &x);
            printf("请输入y坐标:\n");
            scanf("%d", &y);
            s = (Node *)malloc(sizeof(Node));
            strcpy(s->city, city);
            s->x = x;
            s->y = y;
            r->next = s;
            r = s;
        }
        else
        {
            flag = 0;
            r->next = NULL;
        }
    }
}
//根据城市名获取坐标
void getXYByCity(LinkList L, char *city)
{
    Node *p;
    p = L->next;
    // printf("开始");
    // printf("%s\n", p);
    // printf("%s\n", p->city);
    // printf("%d\n", p->x);
    // printf("%d\n", p->y);
    while (p != NULL)
    { //使用strcmp()方法寻找城市
        // printf("开始判断：%s,%s\n", p->city, city);
        if (strcmp(p->city, city) == 0)
        {
            printf("坐标为(%d,%d)\n", p->x, p->y);
            break; //找到一个就跳出循环
        }
        p = p->next; //下一结点
    }
    if (p == NULL)
    {
        printf("没有查找到对应城市\n");
    }
}
//查找所有符合要求的城市
void getAllCities(LinkList L, int x, int y, int D)
{
    Node *p;
    p = L->next;
    int px, py;  // p结点上的x,y坐标
    int dx, dy;  //坐标P和p结点的坐标差
    int num = 0; //记录符合条件的城市数量
    while (p != NULL)
    {
        px = p->x;
        py = p->y;
        dx = abs(px - x); //距离为整数，所以取绝对值
        dy = abs(py - y);
        if (dx * dx + dy * dy <= D * D) //判断是否在D距离范围内
        {
            printf("%s  ", p->city);
            num++; //找到符合条件的，数量+1
        }
        p = p->next; //下一结点
    }
    if (num == 0) //找到0个城市
    {
        printf("没有查找到符合的城市\n");
    }
}
int main(int argc, char const *argv[])
{
    LinkList L;
    InitList(&L);
    CreateFormTail(L);
    //第一问
    printf("请输入要查找的城市名:");
    char city[10];
    scanf("%s", city);
    char *searchCity = city;
    getXYByCity(L, searchCity); //查找坐标
    printf("---------------------------------------\n");
    //第二问
    int x, y, D;
    printf("请输入坐标P(空格隔开):");
    scanf("%d %d", &x, &y);
    // printf("x:%d,y:%d", x, y);
    printf("请输入距离D:");
    scanf("%d", &D);
    getAllCities(L, x, y, D); //查找符合条件的城市
    return 0;
}
