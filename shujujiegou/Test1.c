#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
typedef struct Node
{
    char city[10]; //������
    int x;         // x��λ��
    int y;         // y��λ��
    struct Node *next;
} Node, *LinkList;

//��ʼ��������
void InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
}
//��β�巨����������
void CreateFormTail(LinkList L)
{
    Node *r, *s;
    int flag = 1;
    r = L;
    char city[10];
    int x;
    int y;
    char *jieshu = "����";
    while (flag)
    {
        printf("�����������: (�������'����',�����)\n");
        scanf("%s", city);

        if (strcmp(city, jieshu) != 0) //�������'����'�������
        {
            printf("������x����:\n");
            scanf("%d", &x);
            printf("������y����:\n");
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
//���ݳ�������ȡ����
void getXYByCity(LinkList L, char *city)
{
    Node *p;
    p = L->next;
    // printf("��ʼ");
    // printf("%s\n", p);
    // printf("%s\n", p->city);
    // printf("%d\n", p->x);
    // printf("%d\n", p->y);
    while (p != NULL)
    { //ʹ��strcmp()����Ѱ�ҳ���
        // printf("��ʼ�жϣ�%s,%s\n", p->city, city);
        if (strcmp(p->city, city) == 0)
        {
            printf("����Ϊ(%d,%d)\n", p->x, p->y);
            break; //�ҵ�һ��������ѭ��
        }
        p = p->next; //��һ���
    }
    if (p == NULL)
    {
        printf("û�в��ҵ���Ӧ����\n");
    }
}
//�������з���Ҫ��ĳ���
void getAllCities(LinkList L, int x, int y, int D)
{
    Node *p;
    p = L->next;
    int px, py;  // p����ϵ�x,y����
    int dx, dy;  //����P��p���������
    int num = 0; //��¼���������ĳ�������
    while (p != NULL)
    {
        px = p->x;
        py = p->y;
        dx = abs(px - x); //����Ϊ����������ȡ����ֵ
        dy = abs(py - y);
        if (dx * dx + dy * dy <= D * D) //�ж��Ƿ���D���뷶Χ��
        {
            printf("%s  ", p->city);
            num++; //�ҵ����������ģ�����+1
        }
        p = p->next; //��һ���
    }
    if (num == 0) //�ҵ�0������
    {
        printf("û�в��ҵ����ϵĳ���\n");
    }
}
int main(int argc, char const *argv[])
{
    LinkList L;
    InitList(&L);
    CreateFormTail(L);
    //��һ��
    printf("������Ҫ���ҵĳ�����:");
    char city[10];
    scanf("%s", city);
    char *searchCity = city;
    getXYByCity(L, searchCity); //��������
    printf("---------------------------------------\n");
    //�ڶ���
    int x, y, D;
    printf("����������P(�ո����):");
    scanf("%d %d", &x, &y);
    // printf("x:%d,y:%d", x, y);
    printf("���������D:");
    scanf("%d", &D);
    getAllCities(L, x, y, D); //���ҷ��������ĳ���
    return 0;
}
