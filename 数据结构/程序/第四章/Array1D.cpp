#include <cassert>
#include <iostream>
using namespace std;

template <class T>
class Array1D
{
public:
    Array1D(int sz = 0);
    ~Array1D() { delete[] elements; }
    T &operator[](int i) const;
    Array1D<T> &operator=(const Array1D<T> &r);
    friend istream &operator>>(istream &in,
                               Array1D<T> &r)
    {
        cout << "Input array" << endl;
        for (int i = 0; i < r.size; i++)
            in >> r.elements[i];
        return in;
    }
    friend ostream &operator<<(ostream &out,
                               const Array1D<T> &r)
    {
        cout << "Array =";
        for (int i = 0; i < r.size; i++)
            out << r.elements[i] << "  ";
        out << endl;
        return out;
    }

private:
    int size;
    T *elements;
};

template <class T>
Array1D<T>::Array1D(int sz)
{
    assert(sz >= 0);
    size = sz;
    elements = new T[sz];
}

template <class T>
T &Array1D<T>::operator[](int i) const
{
    assert(i >= 0 && i < size);
    return elements[i];
}

template <class T>
Array1D<T> &Array1D<T>::operator=(
    const Array1D<T> &r)
{
    if (this != &r)
    {
        size = r.size;
        delete[] elements;
        elements = new T[size];
        for (int i = 0; i < size; i++)
            elements[i] = r.elements[i];
    }
    return *this;
}

int main(void)
{
    Array1D<int> a(5), b(8);
    Array1D<int> c;
    cin >> a;
    cout << "a " << a << endl;
    cin >> b;
    cout << "b " << b << endl;
    cout << "c " << c << endl;
    cout << "a[0]= " << a[0] << "; b[5]= " << b[5] << endl;
    c = b;
    cout << "c = b, c " << c << endl;
    b = a;
    cout << "b = a, b " << b << endl;
    return 0;
}
