#include "stdio.h"
#include "stdlib.h"

#define MaxSize 50

typedef struct queue
{
    /* data */
    int Front, Rear, MaxQueue;
    int Element[MaxSize];
} Queue;

void CreateQueue(Queue *q, int maxsize)
{
    q->Front = q->Rear = 0;
    q->MaxQueue = maxsize;
}

int IsEmpty(Queue q)
{
    return q.Front == q.Rear;
}

int IsFull(Queue q)
{
    return (q.Rear + 1) % q.MaxQueue == q.Front;
}

void Append(Queue *q, int element)
{
    if (IsFull(*q))
        printf("OverFlow!\n");
    else
        q->Element[q->Rear = (q->Rear + 1) % q->MaxQueue] = element;
}

void Serve(Queue *q)
{
    if (IsEmpty(*q))
        printf("UnderFlow!\n");
    else
        q->Front = (q->Front + 1) % q->MaxQueue;
}

void QueueFront(Queue q, int *x)
{
    if (IsEmpty(q))
        printf("UnderFlow!\n");
    else
        *x = q.Element[(q.Front + 1) % q.MaxQueue];
}

int InputElement()
{
    static int a;
    printf("Input a Element:");
    scanf("%d", &a);
    return a;
}

void PrintQueue(Queue q)
{
    if (IsEmpty(q))
        printf("underFlow!\n");
    else
    {
        int front = q.Front;
        while ((front++) % q.MaxQueue != q.Rear % q.MaxQueue)
        {
            printf("%d ", q.Element[front]);
        }
        printf("\n");
    }
}

int main()
{
    Queue q;
    int inputElement;
    CreateQueue(&q, 10);
    Append(&q, 1);
    Append(&q, 2);
    Append(&q, 3);
    Append(&q, 4);
    Append(&q, 5);
    PrintQueue(q);
    inputElement = InputElement();
    Append(&q, inputElement);
    PrintQueue(q);
    Serve(&q);
    Serve(&q);
    Serve(&q);
    Serve(&q);
    Serve(&q);
    PrintQueue(q);
    return 0;
}