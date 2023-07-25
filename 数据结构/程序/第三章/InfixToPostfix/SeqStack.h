#ifndef SEQSTACK_H
#define SEQSTACK_H
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

template<typename T>
class Stack{
 public:
  Stack(){};
  virtual void push(const T& x) = 0;
  virtual void pop() = 0;
  virtual T Top()const = 0;
  virtual bool isEmpty()const = 0;
  virtual bool isFull()const = 0;
};

template<typename T>
class SeqStack: public Stack<T>{
 public:
  SeqStack(int maxSize = 50);
  ~SeqStack();
  void push(const T& x);
  void pop();
  T Top()const;
  //由于下面三个函数内容较短，故将其直接写在类中，
  //编译器在这里将其当作inline（内联）函数处理
  bool isEmpty()const{return(top == -1);}
  bool isFull()const{return (top == maxTop);}
  void setNull(){top = -1;}
 private:
  T* s;
  int maxTop;
  int top;
};

template<typename T>
SeqStack<T>::SeqStack(int maxSize){
	//声明中定义了默认值，此处实现时不必再写
 maxTop = maxSize -1;
 s = new T[maxSize];
 top = -1;
}

template<typename T>
SeqStack<T>::~SeqStack(){
 delete []s;
}

template<typename T>
void SeqStack<T>::push(const T& x){
 assert(!isFull());
 s[++top] = x;
}

template<typename T>
void SeqStack<T>::pop(){
 assert(!isEmpty());
 top--;
}

template<typename T>
T SeqStack<T>::Top()const{
 assert(!isEmpty());
 return s[top];
}

#endif
