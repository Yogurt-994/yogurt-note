#include <iostream>
#include <cstring>
using namespace std;

class String
{
public:
    String(const char *p);
    ~String()
    {
        delete[] str;
        delete[] f;
    }
    void Fail();
    void RevisedFail();

private:
    void print();
    int n;
    char *str;
    int *f;
};

String::String(const char *p)
{
    n = strlen(p);
    str = new char[n + 1];
    strcpy(str, p);
    f = new int[n + 1];
    for (int i = 0; i <= n; i++)
        f[i] = 0;
}

void String::print()
{
    for (int i = 0; i < n; i++)
        cout << f[i] << "  ";
}

void String::Fail()
{
    int j = 0, k = -1;
    f[0] = -1;
    while (j < n)
        if ((k == -1) || (str[j] == str[k]))
        {
            j++;
            k++;
            f[j] = k;
        }
        else
            k = f[k];
    print();
}

void String::RevisedFail()
{
    int j = 0, k = -1;
    f[0] = -1;
    while (j < n)
    {
        if ((k == -1) || (str[j] == str[k]))
        {
            j++;
            k++;
            if (str[j] == str[k])
                f[j] = f[k];
            else
                f[j] = k;
        }
        else
            k = f[k];
    }
    print();
}

int main(void)
{
    String s("abab");
    s.Fail();
    cout << endl;
    s.RevisedFail();
    return 0;
}
