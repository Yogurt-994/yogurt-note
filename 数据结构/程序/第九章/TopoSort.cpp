#include <iostream>
using namespace std;

enum ResultCode
{
    Underflow,
    Overflow,
    Success,
    Duplicate,
    NotPresent,
    Failure,
    HasCycle
};

template <class T>
struct ENode
{
    ENode() { nextArc = NULL; }
    ENode(int vertex, T weight, ENode *next)
    {
        adjVex = vertex;
        w = weight;
        nextArc = next;
    }
    int adjVex;
    T w;
    ENode *nextArc;
};

template <class T>
class Graph
{
public:
    virtual ~Graph() {}
    virtual ResultCode Insert(int u, int v, T &w) = 0;
    virtual ResultCode Remove(int u, int v) = 0;
    virtual bool Exist(int u, int v) const = 0;

protected:
};

template <class T>
struct LGraph : public Graph<T>
{
public:
    LGraph(int mSize);
    ~LGraph();
    ResultCode Insert(int u, int v, T &w);
    ResultCode Remove(int u, int v);
    bool Exist(int u, int v) const;
    int Vertices() const { return n; }
    void Output();

protected:
    ENode<T> **a;
    int n, e;
};

template <class T>
void LGraph<T>::Output()
{
    ENode<T> *q;
    for (int i = 0; i < n; i++)
    {
        q = a[i];
        // a[i]本身已经是第一个结点的地址，故而不能写成q=a[i]->adjVex!!
        while (q)
        {
            cout << "(" << i << "  "
                 << q->adjVex << "  " << q->w << ")  ";
            q = q->nextArc;
        }
        cout << endl;
    }
    cout << endl
         << endl;
}

template <class T>
LGraph<T>::LGraph(int mSize)
{
    n = mSize;
    e = 0;
    a = new ENode<T> *[n];
    for (int i = 0; i < n; i++)
        a[i] = NULL;
}

template <class T>
LGraph<T>::~LGraph()
{
    ENode<T> *p, *q;
    for (int i = 0; i < n; i++)
    {
        p = a[i];
        q = p;
        while (p)
        {
            p = p->nextArc;
            delete q;
            q = p;
        }
    }
    delete[] a;
}

template <class T>
bool LGraph<T>::Exist(int u, int v) const
{
    if (u < 0 || v < 0 || u > n - 1 || v > n - 1 || u == v)
        return false;
    ENode<T> *p = a[u];
    while (p && p->adjVex != v)
        p = p->nextArc;
    if (!p)
        return false;
    else
        return true;
}

template <class T>
ResultCode LGraph<T>::Insert(int u, int v, T &w)
{
    if (u < 0 || v < 0 || u > n - 1 || v > n - 1 || u == v)
        return Failure;
    if (Exist(u, v))
        return Duplicate;
    ENode<T> *p = new ENode<T>(v, w, a[u]);
    a[u] = p;
    e++;
    return Success;
}

template <class T>
ResultCode LGraph<T>::Remove(int u, int v)
{
    if (u < 0 || v < 0 || u > n - 1 || v > n - 1 || u == v)
        return Failure;
    ENode<T> *p = a[u], *q = NULL;
    while (p && p->adjVex != v)
    {
        q = p;
        p = p->nextArc;
    }
    if (!p)
        return NotPresent;
    if (q)
        q->nextArc = p->nextArc;
    else
        a[u] = p->nextArc;
    delete p;
    e--;
    return Success;
}

//===============================================

template <class T>
class ExtLGraph : public LGraph<T>
{
public:
    ExtLGraph(int mSize) : LGraph<T>(mSize) {}
    void TopoSort(int *order);

private:
    void CallInDegree(int *InDegree);
};

template <class T>
void ExtLGraph<T>::TopoSort(int *order)
{
    int *InDegree = new int[LGraph<T>::n];
    int i, j, k, top = -1;
    ENode<T> *p;
    CallInDegree(InDegree);
    for (i = 0; i < LGraph<T>::n; i++)
        if (!InDegree[i])
        {
            InDegree[i] = top;
            top = i;
        }
    for (int i = 0; i < LGraph<T>::n; i++)
    {
        if (top == -1)
            throw HasCycle;
        else
        {
            j = top;
            top = InDegree[top];
            order[i] = j;
            cout << j << "  ";
            for (p = LGraph<T>::a[j]; p; p = p->nextArc)
            {
                k = p->adjVex;
                InDegree[k]--;
                if (!InDegree[k])
                {
                    InDegree[k] = top;
                    top = k;
                }
            }
        }
    }
}

template <class T>
void ExtLGraph<T>::CallInDegree(int *InDegree)
{
    for (int i = 0; i < LGraph<T>::n; i++)
        InDegree[i] = 0;
    for (int i = 0; i < LGraph<T>::n; i++)
        for (ENode<T> *p = LGraph<T>::a[i]; p; p = p->nextArc)
            InDegree[p->adjVex]++;
}

//==================================================

int main(void)
{
    const int size = 9;
    ExtLGraph<int> lg(size);
    cout << endl
         << endl
         << "逐步建构图9-11的TopoSort(P190)" << endl
         << endl;
    int w = 10;
    lg.Insert(0, 2, w);
    lg.Insert(0, 7, w);
    lg.Insert(1, 2, w);
    lg.Insert(1, 3, w);
    lg.Insert(1, 4, w);
    lg.Insert(2, 3, w);
    lg.Insert(3, 5, w);
    lg.Insert(3, 6, w);
    lg.Insert(4, 5, w);
    lg.Insert(7, 8, w);
    lg.Insert(8, 6, w);

    int *order = new int[size];
    lg.TopoSort(order);
    delete[] order;
    return 0;
}
