#include "stdio.h"
#include "stdlib.h"

typedef struct node
{
    /* data */
    int Element;
    struct node *Link;
} Node;

typedef struct list
{
    Node *first;
    int Size;
} List;

void CreateList(List *lst)
{
    lst->first = (Node *)malloc(sizeof(Node));
    lst->first->Link = NULL;
}

void Insert(List *lst, int pos, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->Element = data;
    newNode->Link = NULL;

    Node *p = lst->first;
    int i = 0;
    while (p && i < pos)
    {
        p = p->Link;
        i++;
    }
    if (!p || i > pos)
    {
        printf("Invalid position.\n");
        free(newNode);
        return;
    }
    newNode->Link = p->Link;
    p->Link = newNode;
}

void Remove(List *lst, int pos)
{
    Node *p = lst->first;
    int i = 0;
    while (p->Link && i < pos)
    {
        p = p->Link;
        i++;
    }
    while (!p->Link || i > pos)
    {
        printf("Invalid position.\n");
        return;
    }
    Node *temp = p->Link;
    p->Link = p->Link->Link;
    free(temp);
}

// 打印链表中的元素
void printList(List *lst)
{
    Node *p = lst->first->Link;
    while (p)
    {
        printf("%d ", p->Element);
        p = p->Link;
    }
    printf("\n");
}

int main()
{
    List lst;
    CreateList(&lst);

    Insert(&lst, 0, 10);
    Insert(&lst, 1, 20);
    Insert(&lst, 2, 30);

    printf("Initial list: ");
    printList(&lst);

    Remove(&lst, 1);

    printf("After remove operation: ");
    printList(&lst);

    return 0;
}