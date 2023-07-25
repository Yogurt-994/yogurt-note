#include "stdio.h"

#define MaxSize 50

typedef struct dstack
{
    /* data */
    int Top1, Top2, MaxStack;
    int Element[MaxSize];
} DStack;

void CreateStack(DStack *s, int maxsize)
{
    s->Top1 = -1;
    s->Top2 = maxsize;
    s->MaxStack = maxsize;
}

bool IsEmpty(DStack s, int i)
{
    if (i)
        return s.Top2 == s.MaxStack;
    return s.Top1 == -1;
}

bool IsFull(DStack s)
{
    return s.Top1 + 1 == s.Top2;
}

void Push(DStack *s, int i, int data)
{
    if (IsFull(*s))
        printf("OverFlow!\n");
    else
    {
        if (i)
            s->Element[--s->Top2] = data;
        else
            s->Element[++s->Top1] = data;
    }
}

void Pop(DStack *s, int i)
{
    if (IsEmpty(*s, i))
        printf("%d UnderFlow!", i);
    else
    {
        if (i)
            s->Top2++;
        else
            s->Top1--;
    }
}

int StackTop(DStack s, int i)
{
    if (IsEmpty(s, i)){
        printf("%d UnderFlow!", i);
        return -1;
    }
    else
    {
        if (i)
            return s.Element[s.Top2];
        else
            return s.Element[s.Top1];
    }
}

int main()
{
    DStack stack;
    int maxsize = MaxSize;

    CreateStack(&stack, maxsize);

    // Push elements to the first stack
    Push(&stack, 0, 11);
    Push(&stack, 0, 21);
    Push(&stack, 0, 31);

    // Push elements to the second stack
    Push(&stack, 1, 41);
    Push(&stack, 1, 51);
    Push(&stack, 1, 61);

    // Pop an element from the first stack
    Pop(&stack, 0);

    // Pop an element from the second stack
    Pop(&stack, 1);

    // Get the top element of the first stack
    int top1 = StackTop(stack, 0);
    printf("Top element of the first stack: %d\n", top1);

    // Get the top element of the second stack
    int top2 = StackTop(stack, 1);
    printf("Top element of the second stack: %d\n", top2);

    return 0;
}
