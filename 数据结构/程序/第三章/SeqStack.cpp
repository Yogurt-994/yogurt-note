#include <iostream>
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

int main(void){
 SeqStack<int> s(20);
 int k;
 for(int i = 0; i < 5; i++)
  s.Push(i+1);
 for(int j = 0; j < 6; j++){
  if(s.Top(k)){
   cout << k << " ";
   s.Pop();
  }
 }
 cout << endl;
 return 0;
}
