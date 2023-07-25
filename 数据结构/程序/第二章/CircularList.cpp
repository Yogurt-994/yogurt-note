#include <iostream>
using namespace std;

template <class T>
class CircularList;
template <class T>
class Node
{
private:
	T data;
	Node<T> *link;
	friend class CircularList<T>;
};

template <class T>
class CircularList
{
private:
	Node<T> *first;
	int length;

public:
	CircularList()
	{
		first = 0;
		length = 0;
	}
	~CircularList()
	{ // 要思考它，将其转变为单链表的格式
		Node<T> *p = first->link;
		first->link = 0;
		first = p;
		while (first)
		{
			p = first->link;
			delete first;
			first = p;
		}
	}
	bool isEmpty() const
	{
		return length == 0;
	}
	int Length() const
	{
		return length;
	}
	bool find(int k, T &x) const
	{
		if (k < 1 || k > length)
		{
			cout << "Out of bounds" << endl;
			return false;
		}
		Node<T> *p = first;
		for (int i = 1; i < k; i++)
			p = p->link;
		x = p->data;
		return true;
	}
	int search(const T &x) const
	{
		int i = 1;
		Node<T> *p = first;
		for (i = 1; p && p->data != x; i++)
			p = p->link;
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
		Node<T> *p = first;
		for (int i = 1; i < k; i++)
			p = p->link;
		Node<T> *q = new Node<T>;
		q->data = x;
		if (k)
		{
			q->link = p->link;
			p->link = q;
		}
		else
		{ // 注意现在已经成为环状了
			q->link = q;
			first = q;
		}
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
		Node<T> *p = first, *q = first;
		for (int i = 1; i < k - 1; i++)
			q = q->link;
		if (k == 1)
		{
			while (p->link != first)
				p = p->link;
			p->link = first->link;
			delete first;
			first = p->link;
		}
		else
		{
			p = q->link;
			q->link = p->link;
			delete p;
		}
		length--;
		return true;
	}
	bool update(int k, const T &x)
	{
		if (k < 1 || k > length)
		{
			cout << "Out of bounds" << endl;
			return false;
		}
		Node<T> *p = first;
		for (int i = 1; i < k; i++)
			p = p->link;
		p->data = x;
		return true;
	}
	void output(ostream &out) const
	{
		Node<T> *p = first;
		out << p->data << " ";
		p = first->link;
		while (p != first)
		{
			out << p->data << " ";
			p = p->link;
		}
		out << endl;
	}
};

int main(void)
{
	CircularList<int> s;
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