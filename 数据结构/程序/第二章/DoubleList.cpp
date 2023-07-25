#include <iostream>
using namespace std;

template <class T>
class DoubleList;
template <class T>
class DNode
{
private:
	T data;
	DNode<T> *llink, *rlink;
	friend class DoubleList<T>;
};

template <class T>
class DoubleList
{
private:
	DNode<T> *first;
	int length;

public:
	DoubleList()
	{
		first = new DNode<T>;
		first->llink = first;
		first->rlink = first;
		length = 0;
	}
	~DoubleList()
	{
		first->llink->rlink = 0;
		DNode<T> *p;
		while (first)
		{
			p = first->rlink;
			delete first;
			first = p;
		}
	}
	bool isEmpty() const { return length == 0; }
	int Length() const { return length; }
	bool find(int k, T &x) const
	{
		if (k < 1 || k > length)
		{
			cout << "Out of Bounds" << endl;
			return false;
		}
		DNode<T> *p = first->rlink;
		for (int i = 1; i < k; i++)
			p = p->rlink;
		x = p->data;
		return true;
	}
	int search(const T &x) const
	{
		int i;
		DNode<T> *p = first->rlink;
		for (i = 1; p && p->data != x; i++)
			p = p->rlink;
		if (p)
			return i;
		return 0;
	}
	bool insert(int k, const T &x)
	{
		if (k < 0 || k > length)
		{
			cout << "Out of Bounds" << endl;
			return false;
		}
		DNode<T> *p = first->rlink; // 这里必须进行修改
		for (int i = 1; i <= k; i++)
			p = p->rlink;
		DNode<T> *q = new DNode<T>;
		q->data = x;
		q->llink = p->llink;
		q->rlink = p;
		p->llink->rlink = q;
		p->llink = q;
		length++;
		return true;
	}
	bool Delete(int k)
	{
		if (!length)
		{
			cout << "Underflow" << endl;
			return false;
		}
		if (k < 1 || k > length)
		{
			cout << "Out of Bounds" << endl;
			return false;
		}
		DNode<T> *p = first;
		for (int i = 1; i <= k; i++)
			p = p->rlink;
		p->llink->rlink = p->rlink;
		p->rlink->llink = p->llink;
		delete p;
		length--;
		return true;
	}
	void output(ostream &out) const
	{
		DNode<T> *p = first->rlink;
		while (p != first)
		{
			out << p->data << " ";
			p = p->rlink;
		}
		out << endl;
	}
};

int main(void)
{
	DoubleList<int> s;
	cout << "After insertion:" << endl;
	for (int i = 0; i < 5; i++)
		s.insert(i, i + 2);
	s.output(cout);
	cout << "After deletion: " << endl;
	s.Delete(2);
	s.output(cout);
	cout << "s.search(5) = " << s.search(5) << endl;
	return 0;
}