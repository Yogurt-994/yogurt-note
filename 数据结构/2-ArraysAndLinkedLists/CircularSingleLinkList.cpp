#include "stdio.h"
#include "stdlib.h"

typedef struct node
{
    int Element;
    struct node *Link;
} Node;

int InputElement()
{
    int element;
    scanf("%d", &element);
    return element;
}

Node *CreateLinkList()
{
    Node *head = (Node *)malloc(sizeof(Node));
    head->Link = head;
    return head;
}

void InsertNode(Node *head)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->Element = InputElement();

    newNode->Link = head->Link;
    head->Link = newNode;
}

void PrintList(Node *first)
{
    Node *p;
    p = first->Link;
    for (; p != first; p = p->Link)
    {
        printf("%d ", p->Element);
    }
}

void FreeList(Node *first)
{
    Node *p = first->Link;
    while (p != first)
    {
        Node *temp = p;
        p = p->Link;
        free(temp);
    }
    free(first);
}

int main()
{
    Node *list = CreateLinkList();
    int numNodes;
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    for (int i = 0; i < numNodes; i++)
    {
        printf("Enter element %d: ", i + 1);
        InsertNode(list);
    }

    printf("List elements: ");
    PrintList(list);

    FreeList(list);

    return 0;
}