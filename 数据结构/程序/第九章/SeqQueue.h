#include <iostream>
using namespace std;

class SeqQueue
{
public:
    SeqQueue(int mSize)
    {
        maxSize = mSize;
        q = new T[maxSize];
        front = rear = 0;
    }
    ~SeqQueue() { delete[] q; }
    bool IsEmpty() const { return front == rear; }
    bool IsFull() const { return (rear + 1) % maxSize == front; }
    bool Front(T &x) const
    {
        if (IsEmpty())
        {
            cout << "Empty" << endl;
            return false;
        }
        x = q[(front + 1) % maxSize];
        return true;
    }
    bool EnQueue(T x)
    {
        if (IsFull())
        {
            cout << "Full" << endl;
            return false;
        }
        q[(rear + 1) % maxSize] = x;
        return true;
    }
    bool DeQueue()
    {
        if (IsEmpty())
        {
            cout << "Underflow" << endl;
            return false;
        }
        front = (front + 1) % maxSize;
        return true;
    }
    void Clear(front = rear = 0;);

private:
    int front, rear;
    int maxSize;
    T *q;
};