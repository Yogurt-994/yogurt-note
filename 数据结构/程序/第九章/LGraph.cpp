#include <iostream>
using namespace std;

enum ResultCode
{
  Underflow,
  Overflow,
  Success,
  Duplicate,
  NotPresent,
  Failure
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
class LGraph : public Graph<T>
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
      cout << "(" << i << "  " << q->adjVex << "  " << q->w << ")  ";
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

int main(void)
{
  LGraph<int> lg(4);
  cout << "逐步建构图9-8(f)的邻接表(P178)" << endl;
  int w = 4;
  lg.Insert(1, 0, w);
  lg.Output();
  w = 5;
  lg.Insert(1, 2, w);
  lg.Output();
  w = 3;
  lg.Insert(2, 3, w);
  lg.Output();
  w = 1;
  lg.Insert(3, 0, w);
  lg.Output();
  w = 1;
  lg.Insert(3, 1, w);
  lg.Output();
  return 0;
}
