#include <stdio.h>

#define MaxSize 10 //货架最大容量
//定义商品信息栈
typedef struct Data
{
    int year;  //年
    int month; //月
    int day;   //日
} shop;
//定义顺序栈data
typedef struct
{
    shop data[MaxSize];
    int top;
} SeqStack;
//初始化顺序栈
void InitStack(SeqStack *S)
{
    S->top = -1;
}
//判断栈空
int IsEmpty(SeqStack *S)
{
    return (S->top == -1 ? 1 : 0);
}
//判断栈满
int IsFull(SeqStack *S)
{
    return (S->top == MaxSize - 1 ? 1 : 0);
}
//进栈
int Push(SeqStack *S, shop d)
{

    if (IsFull(S) == 1) //栈满
    {
        return 0;
    }
    S->top++;            //栈顶指针上移
    S->data[S->top] = d; //商品d放入top所指空间
    return 1;
}
//出栈
int Pop(SeqStack *S, shop *d)
{
    if (IsEmpty(S) == 1) //栈空
    {
        return 0;
    }
    *d = S->data[S->top];
    S->top--; //栈顶指针下移
    return 1;
}
//取栈顶元素
int GetTop(SeqStack *S, shop *d)
{

    if (IsEmpty(S) == 1) //栈空
    {
        return 0;
    }
    *d = S->data[S->top];
    return 1;
}
//遍历输出货架
void showAll(SeqStack *S1)
{
    int i = S1->top;
    printf("------当前货架-------\n");
    for (; i > -1; i--)
    {
        printf("商品%d:生产日期：%d-%d-%d\n", i, S1->data[i].year, S1->data[i].month, S1->data[i].day);
    }
    printf("--------------------\n");
}
//上货
void addShop(SeqStack *S1, SeqStack *S2)
{
    int flag = 1;
    int year, month, day;
    shop newd, oldd;
    // int result;
    while (flag)
    {
        printf("开始上货\n");
        printf("请输入该商品生产年份: (输入‘0’停止上货)\n");
        scanf("%d", &year);
        if (year != 0)
        {
            printf("请输入商品月份:\n");
            scanf("%d", &month);
            printf("请输入商品日期:\n");
            scanf("%d", &day);
            newd.year = year;
            newd.month = month;
            newd.day = day;

            if (GetTop(S1, &oldd) == 0) //栈空
            {
                Push(S1, newd); //直接进栈
                showAll(S1);
            }
            else //栈不空
            {
                if (IsFull(S1) == 0) //栈没满
                {
                    //取栈顶元素比较生产日期
                    int result = IsEmpty(S1); //栈是否空
                    while (result != 1)
                    {
                        int bijiao = 0; // 1则新货日期大，0则日期小
                        // printf("货架顶部-- %d-%d-%d\n", S1->data[S1->top].year, S1->data[S1->top].month, S1->data[S1->top].day);
                        // printf("新货------ %d-%d-%d\n", newd.year, newd.month, newd.day);
                        if (oldd.year < newd.year) //年份大
                        {
                            bijiao = 1;
                        }
                        else if (oldd.year == newd.year && oldd.month < newd.month) //年份相同 月份大
                        {
                            bijiao = 1;
                        }
                        else if (oldd.year == newd.year && oldd.month == newd.month && oldd.day < newd.day) //年份、月份相同 日期大
                        {
                            bijiao = 1;
                        }
                        // printf("比较结果--- %d\n", bijiao);

                        if (bijiao == 1) //需要倒货
                        {
                            Pop(S1, &oldd);    //抛出S1顶部的货
                            Push(S2, oldd);    //放入S2
                            GetTop(S1, &oldd); // 取S1顶部的货 记录到oldd
                        }
                        else
                        {
                            break; //跳出本次循环
                        }
                        result = IsEmpty(S1); //栈是否空
                    }
                    //全都倒货了 或者货架为空 先把新的加进去  再把S2中的全放回S1（如果S2中有）
                    Push(S1, newd); //直接进栈
                    while (IsEmpty(S2) != 1)
                    {
                        Pop(S2, &oldd); //取S2顶部的货
                        Push(S1, oldd); //放入S1
                    }
                    // result = 1; //结束上货
                    printf("上货成功\n");
                    showAll(S1);
                }
                else //栈满
                {
                    printf("货架满了,停止上货\n");
                    flag = 0;
                    showAll(S1);
                }
            }
        }
        else
        {
            printf("停止上货\n");
            flag = 0;
            showAll(S1);
        }
    }
}
int main(int argc, char const *argv[])
{
    SeqStack S1, S2;
    InitStack(&S1); //初始化S1栈
    InitStack(&S2); //初始化S2栈
    addShop(&S1, &S2);

    return 0;
}
