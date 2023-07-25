// Polynominal.cpp
#include <iostream.h>

class Polynominal; // 前向声明
class Term
{
private:
    int coef;
    int exp;
    Term *link;
    friend class Polynominal;

public:
    Term(int c, int e) : coef(c), exp(e) { link = 0; }
    Term(int c, int e, Term *nxt) : coef(c), exp(e) { link = nxt; }
    Term *insertAfter(int c, int e)
    {
        link = new Term(c, e, link);
        return link;
    }
    friend ostream &operator<<(ostream &out, const Term &val)
    {
        if (val.coef == 0)
            return out;
        out << val.coef;
        switch (val.exp)
        {
        case 0:
            break;
        case 1:
            out << "X";
            break;
        default:
            out << "X^" << val.exp;
            break;
        }
        return out;
    }
}; // class Term

class Polynominal
{
private:
    Term *theList;

public:
    Polynominal()
    {
        theList = new Term(0, -1);
        theList->link = theList;
    }
    ~Polynominal()
    {
        Term *p = theList;
        while (p->link != theList)
            p = p->link;
        p->link = 0;
        while (theList)
        {
            p = theList->link;
            delete theList;
            theList = p;
        }
    }
    void addTerms(istream &in)
    {
        Term *q = theList;
        int c, e;
        for (;;)
        {
            cout << "Input a term(coef, exp): ";
            in >> c >> e;
            if (e < 0)
                break;
            q = q->insertAfter(c, e);
        }
    }
    void output(ostream &out) const
    {
        int first = 1;
        Term *p = theList->link;
        cout << "The Polynominal is: ";
        for (; p != theList; p = p->link)
        {
            if (!first && (p->coef > 0))
                out << "+";
            first = 0;
            out << *p;
        }
        out << endl;
    }
    void polyAdd(Polynominal &r)
    {
        Term *q, *q1 = theList, *q2, *p;
        p = r.theList;
        q = q1->link;
        p = p->link;
        while (p->exp >= 0)
        {
            while (p->exp < q->exp)
            {
                q1 = q;
                q = q->link;
            }
            if (p->exp == q->exp)
            {
                q->coef = q->coef + p->coef;
                if (q->coef == 0)
                {
                    q2 = q;
                    q1->link = q->link;
                    q = q->link;
                    delete (q2);
                    p = p->link;
                }
                else
                {
                    q1 = q;
                    q = q->link;
                    p = p->link;
                }
            }
            else
            {
                q1 = q1->insertAfter(p->coef, p->exp);
                p = p->link;
            } // else
        }     // while
    }         // PolyAdd
    friend ostream &operator<<(ostream &out, const Polynominal &x)
    {
        x.output(out);
        return out;
    }
    friend istream &operator>>(istream &in, Polynominal &x)
    {
        x.addTerms(in);
        return in;
    }
    friend Polynominal &operator+(Polynominal &a, Polynominal &b)
    {
        a.polyAdd(b);
        return a;
    }
};

void main(void)
{
    Polynominal p, q;
    cin >> p;
    cout << p;
    cin >> q;
    cout << q;
    q = q + p;
    cout << q;
}
