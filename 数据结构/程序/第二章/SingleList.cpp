// LinearList.h
#include <iostream>
using namespace std;

template <class T>
class LinearList
{
public:
    virtual bool IsEmpty() const = 0;
    virtual int Length() const = 0;
    virtual bool Find(int i, T &x) const = 0;
    virtual int Search(T x) const = 0;
    virtual bool Insert(int i, T x) = 0;
    virtual bool Delete(int i) = 0;
    virtual bool Update(int i, T x) = 0;
    virtual void Output(ostream &out) const = 0;

protected:
    int n; // 线性表的长度
};

// include "LinearList.h"
template <class T>
class SingleList;
template <class T>
class Node
{
private:
    T element;
    Node<T> *link;
    friend class SingleList<T>;
};

template <class T>
class SingleList : public LinearList<T>
{
public:
    SingleList()
    {
        first = NULL;
        n = 0;
    }
    ~SingleList();
    bool IsEmpty() const;
    int Length() const;
    bool Find(int i, T &x) const;
    int Search(T x) const;
    bool Insert(int i, T x);
    bool Delete(int i);
    bool Update(int i, T x);
    void Clear();
    void Output(ostream &out) const;

private:
    Node<T> *first;
};

template <class T>
SingleList<T>::~SingleList()
{
    Node<T> *p;
    while (first)
    {
        p = first->link;
        delete first;
        first = p;
    }
}

template <class T>
int SingleList<T>::Length() const { return n; }

template <class T>
bool SingleList<T>::IsEmpty() const { return n == 0; }

template <class T>
bool SingleList<T>::Find(int i, T &x) const
{
    if (i < 0 || i > n - 1)
    {
        cout << "Out Of Bounds" << endl;
        return false;
    }
    Node<T> *p = first;
    for (int j = 0; j < i; j++)
        p = p->link;
    x = p->element;
    return true;
}

template <class T>
int SingleList<T>::Search(T x) const
{
    Node<T> *p = first;
    int j;
    for (j = 0; p && p->element != x; j++)
        p = p->link;
    if (p)
        return j;
    return -1;
}

template <class T>
bool SingleList<T>::Insert(int i, T x)
{
    if (i < -1 || i > n - 1)
    {
        cout << "Out of Bounds" << endl;
        return false;
    }
    Node<T> *q = new Node<T>;
    q->element = x;
    Node<T> *p = first;
    for (int j = 0; j < i; j++)
        p = p->link;
    if (i > -1)
    {
        q->link = p->link;
        p->link = q;
    }
    else
    {
        q->link = first;
        first = q;
    }
    n++;
    return true;
}

template <class T>
bool SingleList<T>::Delete(int i)
{
    if (!n)
    {
        cout << "UnderFlow" << endl;
        return false;
    }
    if (i < 0 || i > n - 1)
    {
        cout << "Out Of Bounds" << endl;
        return false;
    }
    Node<T> *p = first, *q = first;
    for (int j = 0; j < i - 1; j++)
        q = q->link;
    if (i == 0)
        first = first->link;
    else
    {
        p = q->link;
        q->link = p->link;
    }
    delete p;
    n--;
    return true;
}

template <class T>
bool SingleList<T>::Update(int i, T x)
{
    if (i < 0 || i > n - 1)
    {
        cout << "Out Of Bounds" << endl;
        return false;
    }
    Node<T> *p = first;
    for (int j = 0; j < i; j++)
        p = p->link;
    p->element = x;
    return true;
}

template <class T>
void SingleList<T>::Output(ostream &out) const
{
    Node<T> *p = first;
    while (p)
    {
        out << p->element << " ";
        p = p->link;
    }
    out << endl;
}

//==============================

template <class T>
void Union(SingleList<T> &LA, SingleList<T> &LB)
{
    T x;
    for (int i = 0; i < LB.Length(); i++)
    {
        LB.Find(i, x);
        if (LA.Search(x) == -1)
            LA.Insert(LA.Length() - 1, x);
    }
}

template <class T>
void Intersection(SingleList<T> &LA, SingleList<T> &LB)
{
    T x;
    int i = 0;
    while (i < LA.Length())
    {
        LA.Find(i, x);
        if (LB.Search(x) == -1)
            LA.Delete(i);
        else
            i++;
    }
}

const int SIZE = 20;

int main(void)
{
    SingleList<int> LA;
    SingleList<int> LB;
    for (int i = 0; i < 5; i++)
        LA.Insert(i - 1, i);
    LA.Output(cout);
    for (int i = 5; i < 10; i++)
        LB.Insert(i - 6, i);
    LB.Insert(-1, 0);
    LB.Insert(3, 2);
    LB.Insert(LB.Length() - 1, 4);
    LB.Output(cout);
    cout << endl;
    Intersection(LA, LB);
    LA.Output(cout);
    return 0;
}
