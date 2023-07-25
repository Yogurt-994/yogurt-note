#include "stdio.h"
#include "stdlib.h"

#define MaxSize 101

typedef struct list
{
    /* data */
    int Size;    // 当前顺序表的大小
    int MaxList; // 顺序表的最大空间
    int Element[MaxSize];
} List;

void CreateList(List *lst, int maxsize)
{
    lst->Size = 0;
    lst->MaxList = maxsize;
}

bool IsEmpty(List lst)
{
    return lst.Size == 0;
}

bool IsFull(List lst)
{
    return lst.Size == lst.MaxList;
}

void Clear(List *lst)
{
    lst->Size = 0;
}

bool Insert(List *lst, int pos, int data)
{
    int i;
    if (IsFull(*lst))
    {
        printf("OverFlow!\n");
        return false;
    }
    if (pos < 0 || pos > lst->Size)
    {
        printf("Out of bounds!\n");
        return false;
    }
    for (i = lst->Size - 1; i >= pos; i--)
    {
        lst->Element[i + 1] = lst->Element[i];
    }
    lst->Element[pos] = data;
    lst->Size++;
    return true;
}

bool Remove(List *lst, int pos, int *data)
{
    int i;
    if (IsEmpty(*lst))
    {
        printf("OverFlow!\n");
        return false;
    }
    if (pos < 0 || pos >= lst->Size)
    {
        printf("Out of bounds!\n");
        return false;
    }
    *data = lst->Element[pos];
    for (i = pos + 1; i < lst->Size; i++)
    {
        lst->Element[i - 1] = lst->Element[i];
    }
    lst->Size--;
    return true;
}

bool Retrieve(List lst, int pos, int *data)
{
    if (pos < 0 || pos >= lst.Size)
    {
        printf("Out of bounds!\n");
        return false;
    }
    *data = lst.Element[pos];
    return true;
}

bool Replace(List *lst, int pos, int data)
{
    if (pos < 0 || pos >= lst->Size)
    {
        printf("OUt of bounds!\n");
        return false;
    }
    lst->Element[pos] = data;
    return true;
}

// 顺序表是有序的
int Search_Insert(List *lst, int data)
{
    int i, j;
    for (i = 0; i < lst->Size && lst->Element[i] < data; i++)
        ;
    if (i < lst->Size && lst->Element[i] == data) // 已经找到该值
        return i;
    if (i == lst->MaxList)
        return -1; // 表示已经越界
    for (j = lst->Size - 1; j >= i; j--)
    {
        lst->Element[j + 1] = lst->Element[j];
    }
    lst->Element[i] = data;
    return i;
}

void Search_Delete(List *lst, int start, int end)
{
    int s_i = 0, e_i = 0;
    int s, e;
    for (; s_i < lst->Size && lst->Element[s_i] < start; s_i++)
        ;
    for (e_i = s_i; e_i < lst->Size && lst->Element[e_i] <= end; e_i++)
        ;
    for (s = s_i, e = e_i; e < lst->Size; e++)
    {
        lst->Element[s++] = lst->Element[e];
    }
    lst->Size -= e - s;
}

int main()
{
    List lst;
    CreateList(&lst, 10);

    Insert(&lst, 0, 1);
    Insert(&lst, 1, 3);
    Insert(&lst, 2, 5);
    Insert(&lst, 3, 7);
    Insert(&lst, 4, 9);
    Insert(&lst, 5, 11);

    for (int i = 0; i < lst.Size; i++)
    {
        printf("%d ", lst.Element[i]);
    }

    int pos = Search_Insert(&lst, 5);
    printf("\n%d\n", pos);

    Search_Delete(&lst, 3, 7);
    for (int i = 0; i < lst.Size; i++)
    {
        printf("%d ", lst.Element[i]);
    }

    return 0;
}