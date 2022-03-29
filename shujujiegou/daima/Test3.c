#include <malloc.h>
#include <stdio.h>
#define MaxSize 100 //树栈最大容量
//定义二叉树的二叉链表结点结构
typedef struct Node
{
    char data;
    struct Node *LChild;
    struct Node *RChild;
} BiTNode, *BiTree;
//利用“扩展先序遍历序列”创建二叉链表
void CreateBiTree(BiTree *bt)
{
    char ch;
    ch = getchar(); //输入数据
    if (ch == '#')  //如果出现输入的是'#',终止递归
        *bt = NULL;
    else
    {
        *bt = (BiTNode *)malloc(sizeof(BiTNode)); //申请一个结点空间
        (*bt)->data = ch;                         //对根结点进行赋值
        CreateBiTree(&((*bt)->LChild));           //递归创建左子树
        CreateBiTree(&((*bt)->RChild));           //递归创建右子树
    }
}
//先序遍历二叉树的递归算法
void PreOrder(BiTree root)
{
    if (root) //递归终止条件是T为NULL
    {
        printf("%c ", root->data); //输出结点
        PreOrder(root->LChild);    //先序递归左子树
        PreOrder(root->RChild);    //先序递归右子树
    }
}
int top = -1; //栈顶指针 每次遍历完成  正常该回到-1
//先序遍历二叉树的非递归算法
void PreOrder2(BiTree root)
{
    BiTNode *a[MaxSize]; //定义一个顺序栈
    BiTNode *p;          //临时指针
    a[++top] = root;     //根结点进栈
    while (top != -1)
    {
        p = a[top]; //取栈顶元素
        top--;
        while (p)
        {
            printf("%c ", p->data); //调用结点的操作函数
            if (p->RChild)          //如果该结点有右孩子，右孩子进栈
            {
                a[++top] = p->RChild;
            }
            p = p->LChild; //一直指向根结点最后一个左孩子
        }
    }
}

//中序遍历二叉树的递归算法
void InOrder(BiTree root)
{
    if (root) //递归终止条件是T为NULL
    {
        InOrder(root->LChild);     //中序递归左子树
        printf("%c ", root->data); //输出结点
        InOrder(root->RChild);     //中序递归右子树
    }
}
//中序遍历二叉树的非递归算法(调用栈操作)
void InOrder2(BiTree root)
{
    BiTNode *a[MaxSize]; //定义一个顺序栈
    BiTNode *p;          //临时指针
    p = root;
    while (p || top != -1) //当p为NULL或者栈为空时，表明树遍历完成
    {
        if (p) //如果p不为NULL，将其压栈并遍历其左子树
        {
            a[++top] = p;
            p = p->LChild;
        }
        else //如果p==NULL，表明左子树遍历完成，需要遍历上一层结点的右子树
        {
            p = a[top];
            top--;
            printf("%c ", p->data);
            p = p->RChild;
        }
    }
}
//后序遍历二叉树的递归算法
void PostOrder(BiTree root)
{
    if (root) //递归终止条件是T为NULL
    {
        PostOrder(root->LChild);   //后序递归左子树
        PostOrder(root->RChild);   //后序递归右子树
        printf("%c ", root->data); //输出结点
    }
}
//后序遍历记录结点栈
typedef struct SNode
{
    BiTree p; //结点
    int tag;  //标记
} SNode;
//后序遍历二叉树的非递归算法(调用栈操作)
void PostOrder2(BiTree root)
{
    SNode a[MaxSize]; //定义一个顺序栈
    BiTNode *p;       //临时指针
    int tag;          //标记
    SNode sdata;
    p = root;
    while (p || top != -1)
    {
        while (p)
        {
            sdata.p = p;      //为该结点入栈做准备
            sdata.tag = 0;    //由于遍历是左孩子，设置标志位为0
            a[++top] = sdata; //进栈
            p = p->LChild;    //以该结点为根结点，遍历左孩子
        }
        sdata = a[top]; //取栈顶元素
        top--;          //出栈
        p = sdata.p;
        tag = sdata.tag;
        if (tag == 0) //如果tag==0，说明该结点还没有遍历它的右孩子
        {
            sdata.p = p;
            sdata.tag = 1;    //更改该结点的标志位
            a[++top] = sdata; //进栈
            p = p->RChild;    //以该结点的右孩子为根结点，重复循环
        }
        else //如果取出来的栈顶元素的tag==1，说明此结点左右子树都遍历完了，可以调用操作函数了
        {
            printf("%c ", p->data);
            p = NULL;
        }
    }
}
int main(int argc, char const *argv[])
{
    BiTree bt;
    printf("请输入要添加的元素\n");
    CreateBiTree(&bt); // 创建二叉树
    printf("递归先序:  ");
    PreOrder(bt); //打印二叉树 递归先序遍历
    printf("  ");
    printf("递归中序:  ");
    InOrder(bt); //打印二叉树 递归中序遍历
    printf("  ");
    printf("递归后序:  ");
    PostOrder(bt); //打印二叉树 递归后序遍历
    printf("\n");
    printf("非递归先序:");
    PreOrder2(bt); //打印二叉树 非递归先序遍历
    printf("  ");
    printf("非递归中序:");
    InOrder2(bt); //打印二叉树 非递归中序遍历
    printf("  ");
    printf("非递归后序:");
    PostOrder2(bt); //打印二叉树 非递归后序遍历
    return 0;
}
