#include "stdio.h"
#include "stdlib.h"

typedef struct node
{
    /* data */
    char Element;
    struct node *link;
} Node;

typedef struct stack
{
    /* data */
    Node *Top;
} Stack;

void CreateStack(Stack *s)
{
    s->Top = NULL;
}

int IsEmpty(Stack *s)
{
    return (s->Top == NULL);
}

void Push(Stack *s, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->Element = data;
    newNode->link = s->Top;
    s->Top = newNode;
}

char Pop(Stack *s)
{
    if (IsEmpty(s))
    {
        printf("UnderFlow!\n");
        return -1;
    }
    else
    {
        Node *temp = s->Top;
        char popElement = temp->Element;
        s->Top = temp->link;
        free(temp);

        return popElement;
    }
}

void StackTop(Stack *s, char *element)
{
    if (IsEmpty(s))
        printf("UnderFlow!\n");
    else
    {
        *element = s->Top->Element;
    }
}

void PrintStack(Stack s)
{
    if (IsEmpty(&s))
        printf("UnderFlow!\n");
    else
    {
        Node *current = s.Top;
        while (current != NULL)
        {
            printf("%c ", current->Element);
            current = current->link;
        }
        printf("\n");
    }
}

int main()
{
    Stack s;
    CreateStack(&s);
    Push(&s,'a');
    Push(&s,'d');
    PrintStack(s);
    Pop(&s);
    PrintStack(s);
    return 0;
}
