#include <iostream>
using namespace std;

template <class T>
class HeaderList;
template <class T>
class Node
{
private:
	T data;
	Node<T> *link;
	friend class HeaderList<T>;
};

template <class T>
class HeaderList
{
private:
	Node<T> *first;
	int length;

public:
	HeaderList()
	{
		first = new Node<T>;
		first->data = 0;
		first->link = 0;
		length = 0;
	}
	~HeaderList()
	{
		Node<T> *p;
		while (first)
		{
			p = first->link;
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
			cout << "Out of bounds" << endl;
			return false;
		}
		Node<T> *p = first->link;
		for (i = 1; i < k; i++)
			p = p->link;
		x = p->data;
		return true;
	}
	int search(const T &x) const
	{
		Node<T> *p = first->link;
		for (int i = 1; p && p->data != x; i++)
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
		for (int i = 1; i <= k; i++)
			p = p->link;
		Node<T> *q = new Node<T>;
		q->data = x;
		q->link = p->link;
		p->link = q;
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
			cout << "Out of bounds" << endl;
			return false;
		}
		Node<T> *p = first, *q;
		for (int i = 1; i < k; i++)
			p = p->link;
		q = p->link;
		p->link = q->link;
		delete q;
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
		for (int i = 0; i < k; i++)
			p = p->link;
		p->data = x;
		return true;
	}
	void output(ostream &out) const
	{
		Node<T> *p = first->link;
		while (p)
		{
			out << p->data << "  ";
			p = p->link;
		}
		out << endl;
	}
};

void main(void)
{
	HeaderList<int> s;
	cout << "After insertion:" << endl;
	for (int i = 0; i < 5; i++)
		s.insert(i, i + 2);
	s.output(cout);
	cout << "After deletion: " << endl;
	s.Delete(2);
	s.output(cout);
	cout << "s.search(5) = " << s.search(5) << endl;
}