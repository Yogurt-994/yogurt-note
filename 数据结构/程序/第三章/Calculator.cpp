#include <iostream>
#include <cmath>
using namespace std;

template<class T>
class Stack{
 public:
  virtual bool IsEmpty()const=0;
  virtual bool IsFull()const=0;
  virtual bool Top(T& x)const=0;
  virtual bool Push(T x)=0;
  virtual bool Pop()=0;
  virtual void Clear()=0;
};

template<class T>
class SeqStack:public Stack<T>{
 public:
  SeqStack(int mSize);
  ~SeqStack(){delete []s;}
  bool IsEmpty()const{return top==-1;}
  bool IsFull()const{return top==maxTop;}
  bool Top(T& x)const;
  bool Push(T x);
  bool Pop();
  void Clear(){top=-1;}
 private:
  int top;
  int maxTop;
  T* s;
};

template<class T>
SeqStack<T>::SeqStack(int mSize){
 maxTop = mSize -1;
 s = new T[mSize];
 top=-1;
}

template<class T>
bool SeqStack<T>::Top(T& x)const{
 if(IsEmpty()){
  cout << "Empty" << endl; return false;
 }
 x = s[top];
 return true;
}

template<class T>
bool SeqStack<T>::Push(T x){
 if(IsFull()){
  cout << "Overflow" << endl;
  return false;
 }
 s[++top]=x;
 return true;
}

template<class T>
bool SeqStack<T>::Pop(){
 if(IsEmpty()){
  cout << "Underflow" << endl;
 }
 top--;
 return true;
}

//===============================================
class Calculator{
 public:
  Calculator(int maxSize):s(maxSize){}
  void Run();
  void Clear(){s.Clear();}
 private:
  SeqStack<double> s;
  void PushOperand(double);
  bool GetOperands(double&, double&);
  void DoOperator(char);
};

void Calculator::PushOperand(double op){
 s.Push(op);
}

bool Calculator::GetOperands(double& op1, double& op2){
 if(!s.Top(op1)){
  cerr << "Missing operand!" << endl; return false;
 }
 s.Pop();
 if(!s.Top(op2)){
  cerr << "Missing operand!" << endl; return false;
 }
 s.Pop();
 return true;
}

void Calculator::DoOperator(char oper){
 double oper1, oper2;
 bool result =GetOperands(oper1, oper2);
 if(result)
  switch(oper){
   case '+': s.Push(oper2 +oper1); break;
   case '-': s.Push(oper2 -oper1); break;
   case '*': s.Push(oper2 *oper1); break;
   case '/': if(fabs(oper1) < 1e-6){
    cerr << "Divide by 0!" << endl;
    Clear();
   }
   else s.Push(oper2 /oper1); break;
   case '^': s.Push(pow(oper2, oper1)); break;
  }
  else Clear();
}

void Calculator::Run(){
 char c;
 double newop;
 while(cin >> c, c !='#'){
  switch(c){
   case '+':
   case '-':
   case '*':
   case '/':
   case '^': DoOperator(c); break;
   default: cin.putback(c);
   	    cin >> newop;
   	    PushOperand(newop);
   	    break;
  }
 }
 if(s.Top(newop)) cout << newop << endl;
}

const int SIZE =20;
int main(void){
 Calculator Cal(SIZE);
 Cal.Run();
 return 0;
}
