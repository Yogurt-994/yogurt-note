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

// SeqList.h
// #include "linearList.h"
template <class T>
class SeqList : public LinearList<T>
{
public:
    SeqList(int mSize);
    ~SeqList() { delete[] elements; }
    bool IsEmpty() const;
    int Length() const;
    bool Find(int i, T &x) const;
    int Search(T x) const;
    bool Insert(int i, T x);
    bool Delete(int i);
    bool Update(int i, T x);
    void Output(ostream &out) const;

private:
    int maxLength;
    T *elements;
};

template <class T>
SeqList<T>::SeqList(int mSize)
{
    maxLength = mSize;
    elements = new T[maxLength];
    n = 0;
}

template <class T>
bool SeqList<T>::IsEmpty() const { return n == 0; }

template <class T>
int SeqList<T>::Length() const { return n; }

template <class T>
bool SeqList<T>::Find(int i, T &x) const
{
    if (i < 0 || i > n - 1)
    {
        cout << "Out of Bounds" << endl;
        return false;
    }
    x = elements[i];
    return true;
}

template <class T>
int SeqList<T>::Search(T x) const
{
    for (int j = 0; j < n; j++)
        if (elements[j] == x)
            return j;
    return -1;
}

template <class T>
bool SeqList<T>::Insert(int i, T x)
{
    if (i < -1 || i > n - 1)
    {
        cout << "Out of Bounds" << endl;
        return false;
    }
    if (n == maxLength)
    {
        cout << "OverFlow" << endl;
        return false;
    }
    for (int j = n - 1; j > i; j--)
        elements[j + 1] = elements[j];
    elements[i + 1] = x;
    n++; // 长度加1
    return true;
}

template <class T>
bool SeqList<T>::Delete(int i)
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
    for (int j = i + 1; j < n; j++)
        elements[j - 1] = elements[j];
    n--; // 长度减1;
    return true;
}

template <class T>
bool SeqList<T>::Update(int i, T x)
{
    if (i < 0 || i > n - 1)
    {
        cout << "Out of Bounds" << endl;
        return false;
    }
    elements[i] = x;
    return true;
}

template <class T>
void SeqList<T>::Output(ostream &out) const
{
    for (int i = 0; i < n; i++)
        out << elements[i] << ' ';
    out << endl;
}

// SeqListU.h
// #include "SeqList.h"
template <class T>
void Union(SeqList<T> &LA, SeqList<T> &LB)
{
    T x;
    for (int i = 0; i < LB.Length(); i++)
    {
        LB.Find(i, x);
        if (LA.Search(x) == -1)
            LA.Insert(LA.Length() - 1, x);
    }
}

// #include "SeqListU.h"
const int SIZE = 20;

int main(void)
{
    SeqList<int> LA(SIZE);
    SeqList<int> LB(SIZE);
    for (int i = 0; i < 5; i++)
        LA.Insert(i - 1, i);
    for (int i = 5; i < 10; i++)
        LB.Insert(i - 6, i);
    LB.Insert(-1, 0);
    LB.Insert(3, 2);
    LB.Insert(LB.Length() - 1, 4);
    Union(LA, LB);
    LA.Output(cout);
    return 0;
}
