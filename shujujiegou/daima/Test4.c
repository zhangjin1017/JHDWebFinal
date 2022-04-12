#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxBit 100              //二进制位数
#define MaxValue 1000           //最大权值
#define MaxSize 50              //最大结点数
#define MaxNode MaxSize * 2 - 1 //生成的哈夫曼树的结点数
//编码结构体
typedef struct
{
    int bit[MaxBit]; //二进制编码
    int start;
} HCodeType;
//结点结构体
typedef struct
{
    int weight; //权值
    int parent; //双亲结点
    int lchild; //左子结点
    int rchild; //右子结点
    char value; //字符
} HNodeType;

/* 构造一颗哈夫曼树 */
void HuffmanTree(HNodeType HuffNode[MaxNode], int n, int count2[n][2])
{
    /* i、j： 循环变量，m1、m2：构造哈夫曼树不同过程中两个最小权值结点的权值，
        x1、x2：构造哈夫曼树不同过程中两个最小权值结点在数组中的序号。*/
    int i, j, m1, m2, x1, x2;
    /* 初始化存放哈夫曼树数组 HuffNode[] 中的结点 */
    for (i = 0; i < 2 * n - 1; i++)
    {
        HuffNode[i].weight = 0;  //权值
        HuffNode[i].parent = -1; //双亲结点
        HuffNode[i].lchild = -1; //左子结点
        HuffNode[i].rchild = -1; //右子结点
        HuffNode[i].value = i;   //实际值，大写字母
    }
    //初始化weight和value
    for (i = 0; i < n; i++)
    {
        HuffNode[i].weight = count2[i][1];      //权值赋值
        HuffNode[i].value = (char)count2[i][0]; //字符赋值
    }
    //循环构造Huffman树
    for (i = 0; i < n - 1; i++)
    {
        m1 = m2 = MaxValue; // m1、m2中存放两个无父结点且结点权值最小的两个结点
        x1 = x2 = 0;
        //找出所有结点中权值最小、无父结点的两个结点，并合并之为一颗二叉树
        for (j = 0; j < n + i; j++)
        {
            if (HuffNode[j].weight < m1 && HuffNode[j].parent == -1) //找出权值最小的结点
            {
                m2 = m1;
                x2 = x1;
                m1 = HuffNode[j].weight;
                x1 = j;
            }
            else if (HuffNode[j].weight < m2 && HuffNode[j].parent == -1) //找出权值第二小的结点
            {
                m2 = HuffNode[j].weight;
                x2 = j;
            }
        }
        //设置找到的两个子结点 x1、x2 的父结点信息
        HuffNode[x1].parent = n + i;                                        //设置x1的父结点
        HuffNode[x2].parent = n + i;                                        //设置x2的父结点
        HuffNode[n + i].weight = HuffNode[x1].weight + HuffNode[x2].weight; //设置父结点权值
        HuffNode[n + i].lchild = x1;                                        //设置父结点的左子结点
        HuffNode[n + i].rchild = x2;                                        //设置父结点的右子结点

        // printf("x1.weight and x2.weight in round %d: %d, %d\n", i + 1, HuffNode[x1].weight, HuffNode[x2].weight); /* 用于测试 */
        // printf("\n");
    }
    //测试
    // printf("索引     大写字母(ASCII)     权重         双亲结点      左子结点     右子结点\n");
    // for (i = 0; i < n + 2; i++)
    // {
    //     printf("index:%-5d value:%-10d weight:%-5d parents:%-5d lchild:%-5d rchild:%-5d\n", i, HuffNode[i].value, HuffNode[i].weight, HuffNode[i].parent, HuffNode[i].lchild, HuffNode[i].rchild);
    // }
    //写入文件
    FILE *fp;
    fp = fopen("C:\\Users\\12169\\Desktop\\Test1.txt", "w");
    fprintf(fp, "索引     大写字母(ASCII)     权重         双亲结点      左子结点     右子结点\n");
    for (i = 0; i < n + 2; i++)
    {
        fprintf(fp, "index:%-5d value:%-10d weight:%-5d parents:%-5d lchild:%-5d rchild:%-5d\n", i, HuffNode[i].value, HuffNode[i].weight, HuffNode[i].parent, HuffNode[i].lchild, HuffNode[i].rchild);
    }
    fclose(fp);
    printf("建立的哈夫曼树已经写入桌面文件Test1.txt\n");
}

//解码
void decodeing(char str[], HNodeType Buf[], int Num)
{
    int i, tmp = 0;
    int m = 2 * Num - 1;
    char *nump;
    char num[100];
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == '0')
            num[i] = 0;
        else
            num[i] = 1;
    }
    i = 0;
    nump = &num[0];

    while (nump < (&num[strlen(str)]))
    {
        tmp = m - 1;
        while ((Buf[tmp].lchild != -1) && (Buf[tmp].rchild != -1))
        {

            if (*nump == 0)
            {
                tmp = Buf[tmp].lchild;
            }
            else
                tmp = Buf[tmp].rchild;
            nump++;
        }

        printf("%c", Buf[tmp].value);
    }
}

int main(void)
{

    HNodeType HuffNode[MaxNode];     /* 定义一个结点结构体数组 */
    HCodeType HuffCode[MaxSize], cd; /* 定义一个编码结构体数组， 同时定义一个临时变量来存放求解编码时的信息 */
    int i, j, c, p, n = 0;
    char str[MaxSize];

    printf("请输入要编码的字符串:\n");
    scanf("%s", str);

    int count[26] = {0}; //存放26个大写字母出现的次数

    //统计次数
    for (i = 0; str[i] != '\0'; i++)
    {
        count[str[i] - 65]++;
    }
    printf("每个字母出现次数(次数越多权重越大):\n");
    //打印
    for (i = 0; i < 26; i++)
    {
        if (count[i] != 0)
        {
            printf("%c:%d\n", i + 65, count[i]);
            n++;
        }
    }
    int count2[n][2];
    int m = 0;
    //记录字母和权重
    for (i = 0; i < 26; i++)
    {
        if (count[i] != 0)
        {
            count2[m][0] = i + 65;
            count2[m++][1] = count[i];
        }
    }
    HuffmanTree(HuffNode, n, count2);

    for (i = 0; i < n; i++)
    {
        cd.start = n - 1;
        c = i;
        p = HuffNode[c].parent;
        while (p != -1) /* 父结点存在 */
        {
            if (HuffNode[p].lchild == c)
                cd.bit[cd.start] = 0;
            else
                cd.bit[cd.start] = 1;
            cd.start--; /* 求编码的低一位 */
            c = p;
            p = HuffNode[c].parent; /* 设置下一循环条件 */
        }                           /* end while */

        /* 保存求出的每个叶结点的哈夫曼编码和编码的起始位 */
        for (j = cd.start + 1; j < n; j++)
        {
            HuffCode[i].bit[j] = cd.bit[j];
        }
        HuffCode[i].start = cd.start;
    } /* end for */
    //存入文件
    FILE *fp;
    fp = fopen("C:\\Users\\12169\\Desktop\\Test2.txt", "w");
    for (i = 0; i < n; i++)
    {
        fprintf(fp, "%c 的哈夫曼编码: ", HuffNode[i].value);
        for (j = HuffCode[i].start + 1; j < n; j++)
        {
            fprintf(fp, "%d", HuffCode[i].bit[j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    printf("所有字母的编码结果已写入桌面文件Test2.txt\n");
    /* 输出已保存好的所有存在编码的哈夫曼编码 */
    // for (i = 0; i < n; i++)
    // {
    //     printf("%c 的哈夫曼编码: ", HuffNode[i].value);
    //     for (j = HuffCode[i].start + 1; j < n; j++)
    //     {
    //         printf("%d", HuffCode[i].bit[j]);
    //     }
    //     // printf(" start:%d", HuffCode[i].start);
    //     printf("\n");
    // }

    printf("请输入二进制数,解码:\n");
    char str2[100];
    scanf("%s", str2);
    decodeing(str2, HuffNode, n);
    getchar();
    return 0;
}