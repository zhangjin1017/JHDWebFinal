#include <stdio.h>
#include <string.h>

#define N 30
#define M 50
struct name ///名字结构体
{
    char s[30];
    int v; /// ascll码值之和
} NAME[N];
struct hashs ///哈希表结构体
{
    char name[30]; ///名字
    int key;       ///关键字
    int sum;       ///哈希表中含有的元素个数
} HASH[M];
void init() ///初始化
{
    int i, j, sum;
    for (i = 0; i < N; i++)
    {
        NAME[i].v = 0;
    }
    strcpy(NAME[0].s, "jiangziya");       //姜子牙
    strcpy(NAME[1].s, "simayi");          //司马懿
    strcpy(NAME[2].s, "sunwukong");       //孙悟空
    strcpy(NAME[3].s, "zhangfei");        //张飞
    strcpy(NAME[4].s, "guanyu");          //关羽
    strcpy(NAME[5].s, "zhaoyun");         //赵云
    strcpy(NAME[6].s, "diaochan");        //貂蝉
    strcpy(NAME[7].s, "liubei");          //刘备
    strcpy(NAME[8].s, "sunce");           //孙策
    strcpy(NAME[9].s, "sunshangxiang");   //孙尚香
    strcpy(NAME[10].s, "bailishouyue");   //百里守约
    strcpy(NAME[11].s, "libai");          //李白
    strcpy(NAME[12].s, "wangzhaojun");    //王昭君
    strcpy(NAME[13].s, "yunzhongjun");    //云中君
    strcpy(NAME[14].s, "zhongkui");       //钟馗
    strcpy(NAME[15].s, "liushan");        //刘禅
    strcpy(NAME[16].s, "zhouyu");         //周瑜
    strcpy(NAME[17].s, "hanxin");         //韩信
    strcpy(NAME[18].s, "caocao");         //曹操
    strcpy(NAME[19].s, "zhenji");         //甄姬
    strcpy(NAME[20].s, "shangguanwaner"); //上官婉儿
    strcpy(NAME[21].s, "huamulan");       //花木兰
    strcpy(NAME[22].s, "yuji");           //虞姬
    strcpy(NAME[23].s, "xiangyu");        //项羽
    strcpy(NAME[24].s, "zhugeliang");     //诸葛亮
    strcpy(NAME[25].s, "gongsunli");      //公孙离
    strcpy(NAME[26].s, "direnjie");       //狄仁杰
    strcpy(NAME[27].s, "liyuanfang");     //李元芳
    strcpy(NAME[28].s, "chengyaojin");    //程咬金
    strcpy(NAME[29].s, "huangzhong");     //黄忠
    for (i = 0; i < N; i++)
    {
        sum = 0;
        for (j = 0; j < strlen(NAME[i].s); j++)
        {
            sum = sum + (NAME[i].s[j] - 'a');
        }
        NAME[i].v = sum; ///名字字母ascll码之和
    }
}
void creathash() ///构造哈希表
{
    int i;
    int n, m, counts;
    for (i = 0; i < M; i++)
    {
        strcpy(HASH[i].name, "0");
        HASH[i].key = 0;
        HASH[i].sum = 0;
    }
    for (i = 0; i < N; i++)
    {
        counts = 1;
        n = (NAME[i].v) % 47;
        m = n;
        if (HASH[n].sum == 0) ///不冲突
        {
            strcpy(HASH[n].name, NAME[i].s);
            HASH[n].key = NAME[i].v;
            HASH[n].sum = 1;
        }
        else ///如果发生了冲突
        {
            while (1)
            {
                m = (m + (NAME[i].v % 10) + 1) % 47;
                counts++;
                if (HASH[m].key == 0)
                {
                    break;
                }
            }
            strcpy(HASH[m].name, NAME[i].s);
            HASH[m].key = NAME[i].v;
            HASH[m].sum = counts;
        }
    }
    return;
}

void searchhash()
{
    char name[30];
    int i, sum, n, m, counts;
    sum = 0;
    n = 0;
    counts = 1;
    printf("请输入要查找人的姓名拼音：\n");
    scanf("%s", name);
    for (i = 0; i < strlen(name); i++)
    {
        sum += (name[i] - 'a');
    }
    n = sum % 47;
    m = n;
    if (strcmp(HASH[n].name, name) == 0)
    {
        printf("姓名:%s 关键字:%d 查找长度:1\n", HASH[n].name, sum);
    }
    else if (HASH[n].sum == 0)
    {
        printf("没有找到这条记录！！！\n");
    }
    else
    {
        while (1)
        {
            m = (m + (sum % 10) + 1) % 47; ///哈希函数
            counts++;
            if (strcmp(HASH[m].name, name) == 0)
            {
                printf("姓名:%s 关键字:%d 查找长度:%d\n", HASH[m].name, sum, counts);
                break;
            }
            if (HASH[m].key == 0)
            {
                printf("没有找到这条记录！！！\n");
                break;
            }
        }
    }
}
void displayhash() ///演示哈希表
{
    int i, sum;
    float ave;
    ave = 0.0;
    sum = 0;
    printf("\n地址\t关键字\t\t搜索长度\t姓名\n");
    for (i = 0; i < M; i++)
    {
        printf("%d", i);
        printf("\t%d", HASH[i].key);
        printf("\t\t%d", HASH[i].sum);
        printf("\t%12s", HASH[i].name);
        printf("\n");
    }
    for (i = 0; i < M; i++)
    {
        sum += HASH[i].sum;
    }
    ave = ((sum)*1.0) / N;
    printf("\n");
    printf("平均查找长度ASL(%d)=%.3lf\n", N, ave);
    return;
}
void display()
{
    int i;
    printf("\n\t关键字\t\t姓名\n");
    for (i = 0; i < 30; i++)
    {
        printf("\t%3d", NAME[i].v);
        printf("\t%15s", NAME[i].s);
        printf("\n");
    }
    return;
}
//顺序查找
void search()
{

    char name[30];
    printf("请输入要查找人的姓名拼音：\n");
    scanf("%s", name);
    int times = 0;
    int i;

    for (i = 0; i < N; i++)
    {
        if (strcmp(NAME[i].s, name) == 0)
        {
            times++;
            printf("查找次数为：%d\n", times);
            return;
        }
        else
        {
            times++;
        }
    }
}
//把NAME按照s排序
void sort()
{
    int i, j;
    char temp[30];
    for (i = 0; i < N - 1; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            if (strcmp(NAME[i].s, NAME[j].s) > 0)
            {
                strcpy(temp, NAME[i].s);
                strcpy(NAME[i].s, NAME[j].s);
                strcpy(NAME[j].s, temp);
            }
        }
    }
}
//二分查找
void binary_search()
{
    sort();
    int low, high, mid;
    low = 0;
    high = N - 1;
    int times = 0;
    char name[30];
    printf("请输入要查找人的姓名拼音：\n");
    scanf("%s", name);
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (strcmp(NAME[mid].s, name) == 0)
        {
            times++;
            printf("查找次数为：%d\n", times);
            return;
        }
        else if (strcmp(NAME[mid].s, name) > 0)
        {
            high = mid - 1;
            times++;
        }
        else
        {
            low = mid + 1;
            times++;
        }
    }
}

int menu()
{
    printf("\n\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━┳  汉字姓名拼音哈希表展示查找系统 ┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

    printf("\n\n");
    printf("\t\t\t ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("\t\t\t ┃                                 ┃\n");
    printf("\t\t\t ┃       请选择您要操作的项目      ┃\n");
    printf("\t\t\t ┃                                 ┃\n");
    printf("\t\t\t ┃       1 展示姓名拼音和关键字    ┃\n");
    printf("\t\t\t ┃                                 ┃\n");
    printf("\t\t\t ┃       2 展示哈希表              ┃\n");
    printf("\t\t\t ┃                                 ┃\n");
    printf("\t\t\t ┃       3 查找关键字              ┃\n");
    printf("\t\t\t ┃                                 ┃\n");
    printf("\t\t\t ┃       4 顺序查找                ┃\n");
    printf("\t\t\t ┃                                 ┃\n");
    printf("\t\t\t ┃       5 二分查找                ┃\n");
    printf("\t\t\t ┃                                 ┃\n");
    printf("\t\t\t ┃       6 退出                    ┃\n");
    printf("\t\t\t ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    return 0;
}
int main()
{
    int n;
    int flag;
    flag = 1;
    while (1)
    {
        menu();
        printf("请输入要执行的操作数(1-6)：\n");
        if (flag == 1)
        {
            init();
            creathash();
            flag = 0;
        }
        scanf("%d", &n);
        getchar();
        if (n < 1 || n > 6)
        {
            printf("输入有误，请重新输入！！！\n");
            continue;
        }
        else
        {
            if (n == 1)
            {
                printf("展示所准备的姓名拼音及其所组成的关键字：\n");
                display();
            }
            else if (n == 2)
            {
                displayhash();
            }
            else if (n == 3)
            {
                searchhash();
            }
            else if (n == 4)
            {
                search();
            }
            else if (n == 5)
            {
                binary_search();
            }
            else if (n == 6)
            {
                return 0;
            }
        }
    }
    return 0;
}