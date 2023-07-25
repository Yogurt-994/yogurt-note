#include "stdio.h"
#include "stdlib.h"

#define IS_FULL(ptr) (!(ptr))

typedef struct node
{
    /* data */
    int Element;
    struct node *Link;
} Node;

Node *NewNode()
{
    Node *p = (Node *)malloc(sizeof(Node));
    if (IS_FULL(p))
    {
        fprintf(stderr, "The memory is full");
        exit(1);
    }
    p->Link = NULL;
    return p;
}

Node *Copy(Node *first)
{
    // 指向节点的指针变量 r
    Node *r, *new = NULL, *p = first;
    for (; p; p = p->Link) // 该循环会遍历原始链表
    {
        if (!new)
        {
            new = NewNode(); // 链表的头节点 q,在此后没有变动过，用于返回
            new->Element = p->Element;
            r = new;
        }
        else
        {
            r->Link = NewNode();
            r = r->Link;
            r->Element = p->Element;
        }
    }
    return new;
}

void Connect(Node *first, Node *second)
{
    Node *p = first;
    while (p->Link)
    {
        p = p->Link;
    }
    p->Link = second;
}

void Reverse(Node **head)
{
    Node *current = *head, *nextNode;
    *head = NULL;
    while (current) // 条件是 current 不为空。这意味着只要还有剩余的节点需要处理，就继续循环。
    {
        nextNode = current->Link;
        current->Link = *head;
        *head = current;
        current = nextNode;
    }
}

int main()
{
    // 创建原始链表
    Node *first = NewNode();
    first->Element = 1;

    Node *second = NewNode();
    second->Element = 2;
    first->Link = second;

    Node *third = NewNode();
    third->Element = 3;
    second->Link = third;

    // 复制链表
    Node *copyList = Copy(first);

    // 打印原始链表
    printf("Original list: ");
    for (Node *p = first; p != NULL; p = p->Link)
        printf("%d ", p->Element);

    // 打印复制后的链表
    printf("\nCopied list: ");
    for (Node *p = copyList; p != NULL; p = p->Link)
        printf("%d ", p->Element);

    // 反转链表
    Reverse(&first);

    printf("\nReverse list: ");
    for (Node *p = first; p != NULL; p = p->Link)
        printf("%d ", p->Element);

    Connect(first, copyList);
    printf("\nConnect list: ");
    for (Node *p = first; p != NULL; p = p->Link)
        printf("%d ", p->Element);

    return 0;
}
