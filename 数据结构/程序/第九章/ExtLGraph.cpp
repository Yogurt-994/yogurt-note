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

//====================SeqQueue======================
template <class T>
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
  void Clear() { front = rear = 0; }

private:
  int front, rear;
  int maxSize;
  T *q;
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
  void DFS();
  void BFS();

private:
  void DFS(int v, bool *visited);
  void BFS(int v, bool *visited);
};

template <class T>
void ExtLGraph<T>::DFS()
{
  bool *visited = new bool[LGraph<T>::n];
  for (int i = 0; i < LGraph<T>::n; i++)
    visited[i] = false;
  for (int i = 0; i < LGraph<T>::n; i++)
    if (!visited[i])
      DFS(i, visited);
  delete[] visited;
}

template <class T>
void ExtLGraph<T>::DFS(int v, bool *visited)
{
  visited[v] = true;
  cout << "  " << v;
  for (ENode<T> *w = LGraph<T>::a[v]; w; w = w->nextArc)
    if (!visited[w->adjVex])
      DFS(w->adjVex, visited);
}

template <class T>
void ExtLGraph<T>::BFS()
{
  bool *visited = new bool[LGraph<T>::n];
  for (int i = 0; i < LGraph<T>::n; i++)
    visited[i] = false;
  for (int i = 0; i < LGraph<T>::n; i++)
    if (!visited[i])
      BFS(i, visited);
  delete[] visited;
}

template <class T>
void ExtLGraph<T>::BFS(int v, bool *visited)
{
  SeqQueue<int> q(20);
  visited[v] = true;
  cout << "  " << v;
  q.EnQueue(v);
  while (!q.IsEmpty())
  {
    q.Front(v);
    q.DeQueue();
    for (ENode<T> *w = LGraph<T>::a[v]; w; w = w->nextArc)
      if (!visited[w->adjVex])
      {
        visited[w->adjVex] = true;
        cout << "  " << w->adjVex;
        q.EnQueue(w->adjVex);
      }
  }
}

//==================================================

int main(void)
{
  ExtLGraph<int> lg(7);
  cout << endl
       << endl
       << "逐步建构图9-9的DFS序列(P187)" << endl
       << endl;
  int w = 10;
  lg.Insert(0, 1, w);
  lg.Insert(1, 2, w);
  lg.Insert(1, 3, w);
  lg.Insert(2, 0, w);
  lg.Insert(3, 2, w);
  lg.Insert(3, 0, w);
  lg.Insert(4, 1, w);
  lg.Insert(5, 3, w);
  lg.Insert(5, 4, w);
  lg.Insert(6, 5, w);
  lg.Insert(6, 4, w);
  cout << endl
       << "DFS=(";
  lg.DFS();
  cout << ")" << endl;
  cout << endl
       << "BFS=(";
  lg.BFS();
  cout << ")" << endl;
  return 0;
}
