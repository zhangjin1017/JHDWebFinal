#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 30
//构建一个学生姓名结构体
struct student
{
    char name[20];
} stu;
//顺序查找
int search(struct student stu[], int *times1, char *name)
{

    int i;
    for (i = 0; i < MAX_SIZE; i++)
    {
        if (strcmp(stu[i].name, name) == 0)
        {
            (*times1)++;
            return i;
        }
        else
        {
            (*times1)++;
        }
    }
    return -1;
}
//二分查找
int binary_search(struct student stu[], int *times2, char *name)
{
    int low, high, mid;
    low = 0;
    high = MAX_SIZE - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (strcmp(stu[mid].name, name) == 0)
        {
            (*times2)++;
            return mid;
        }
        else if (strcmp(stu[mid].name, name) > 0)
        {
            high = mid - 1;
            (*times2)++;
        }
        else
        {
            low = mid + 1;
            (*times2)++;
        }
    }
    return -1;
}
int main(int argc, char const *argv[])
{
    int i;
    int times1 = 0;
    int times2 = 0;
    struct student stu[MAX_SIZE]; //新建一个学生数组
    char name[20];
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("请输入第%d个学生姓名:", i + 1);
        scanf("%s", stu[i].name);
    }
    printf("请输入要查找的学生姓名:");
    scanf("%s", name);
    search(stu, &times1, name);
    printf("顺序查找的次数:%d\n", times1);
    binary_search(stu, &times2, name);
    printf("二分查找的次数:%d\n", times2);

    return 0;
}
