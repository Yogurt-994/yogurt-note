#include "stdio.h"
#include "stdlib.h"

#define MaxSize 50

// 当前顺序栈是栈底Top为-1
typedef struct stack
{
    /* data */
    int Top, MaxStack;
    int Elements[MaxSize];
} Stack;

void CreateStack(Stack *s, int maxsize)
{
    s->Top = -1;
    s->MaxStack = maxsize;
}

int IsEmpty(Stack s)
{
    return s.Top < 0;
}

int IsFull(Stack s)
{
    return s.Top >= s.MaxStack - 1;
}

void Push(Stack *s, int x)
{
    if (IsFull(*s))
        printf("OverFlow!");
    else
        s->Elements[++s->Top] = x;
}

void Pop(Stack *s)
{
    if (IsEmpty(*s))
        printf("UnderFlow!");
    else
        s->Top--;
}

void StackTop(Stack *s, int *x)
{
    if (IsEmpty(*s))
        printf("UnderFlow!");
    else
        *x = s->Elements[s->Top];
}

int InputElement()
{
    static int a;
    scanf("%d", &a);
    return a;
}

void PrintStack(Stack s)
{
    if (IsEmpty(s))
        printf("UnderFlow!");
    else
    {
        for (int i = 0; i <= s.Top; i++)
        {
            printf("%d ", s.Elements[i]);
        }
        printf("\n");
    }
}

int main()
{
    Stack s;
    int inputElement;
    CreateStack(&s, 10);
    Push(&s, 10);
    Push(&s, 15);
    PrintStack(s);
    inputElement = InputElement();
    Push(&s, inputElement);
    PrintStack(s);
    Pop(&s);
    Pop(&s);
    if (IsEmpty(s))
        printf("Stack is empty!\n");
    else
        printf("Not empty.\n");
    PrintStack(s);
    return 0;
}