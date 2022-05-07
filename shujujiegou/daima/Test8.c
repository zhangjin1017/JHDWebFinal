#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 30
//直接插入排序
void insertSort(int *array)
{
    int i, j, tmp;
    for (i = 1; i < MAX_SIZE; i++)
    {
        tmp = array[i];
        for (j = i - 1; j >= 0 && array[j] > tmp; j--)
        {
            array[j + 1] = array[j];
        }
        array[j + 1] = tmp;
    }
    printf("直接插入：");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
//简单选择排序
void selectSort(int *array)
{
    int i, j, min, tmp;
    for (i = 0; i < MAX_SIZE - 1; i++)
    {
        min = i;
        for (j = i + 1; j < MAX_SIZE; j++)
        {
            if (array[j] < array[min])
            {
                min = j;
            }
        }
        tmp = array[i];
        array[i] = array[min];
        array[min] = tmp;
    }
    printf("简单选择：");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
//冒泡排序
void bubbleSort(int *array)
{
    int i, j, tmp;
    for (i = 0; i < MAX_SIZE - 1; i++)
    {
        for (j = 0; j < MAX_SIZE - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
    printf("冒泡排序：");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
//快速排序
void quickSort(int *array)
{
    int i, j, tmp, key;
    i = 0;
    j = MAX_SIZE - 1;
    key = array[0];
    while (i < j)
    {
        while (array[j] >= key && i < j)
        {
            j--;
        }
        tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
        while (array[i] <= key && i < j)
        {
            i++;
        }
        tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
    }
    printf("快速排序：");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//随机生成30个整数
int main()
{
    int i;
    int array[MAX_SIZE];
    for (i = 0; i < MAX_SIZE; i++)
    {
        array[i] = rand() % 100 + 1; //随机生成1到100之间的整数
    }
    printf("原始数组:");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    //直接插入排序
    insertSort(array);
    //简单选择排序
    selectSort(array);
    //冒泡排序
    bubbleSort(array);
    //快速排序
    quickSort(array);

    return 0;
}
