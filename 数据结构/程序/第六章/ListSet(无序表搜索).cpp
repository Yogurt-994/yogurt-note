#include <iostream>
#include <cassert>
using namespace std;

enum ResultCode{Underflow, Overflow, Success, 
		Duplicate, NotPresent};
template<class T>
class DynamicSet{
 public:
  virtual ResultCode Search(T& x)const=0;
  virtual ResultCode Insert(T& x)=0;
  virtual ResultCode Remove(T& x)=0;
  virtual bool IsEmpty()const=0;
  virtual bool IsFull()const=0;
};

template<class T>
class ListSet:public DynamicSet<T>{
 public:
  ListSet(int mSize);
  ~ListSet(){delete []l;}
  bool IsEmpty()const{return n==0;}
  bool IsFull()const{return n==maxSize;}
  ResultCode Search(T& x)const;
  ResultCode Insert(T& x);
  ResultCode Remove(T& x);
  void Print();
 private:
  T* l;
  int maxSize;
  int n;
};

template<class T>
void ListSet<T>::Print(){
 for(int i=0; i<n; i++)
  cout << l[i] << "\t";
  cout << endl;
}

template<class T>
ListSet<T>::ListSet(int mSize){
 maxSize = mSize;
 l = new T[maxSize];
 n = 0;
}

template<class T>
ResultCode ListSet<T>::Insert(T& x){
 assert(!IsFull());
 l[n++] = x;
 return Success;
}

template<class T>
ResultCode ListSet<T>::Remove(T& x){
  //空的，等待以后完成
}

template<class T>
ResultCode ListSet<T>::Search(T& x)const{
 for(int i =0; i <n; i++){
  if(l[i] == x){
   x =l[i];
   return Success;
  }
 }
 return NotPresent;
}

int main(void){
 ListSet<int> ls(20);
 cout << "初始序列\t";
 int x = 34; ls.Insert(x); x = 88; ls.Insert(x);
 x = 77; ls.Insert(x); x = 55; ls.Insert(x);
 x = 44; ls.Insert(x); x = 100; ls.Insert(x);
 ls.Print();
 cout << endl;
 x = 88;
 if(ls.Search(x)==Success) cout << "Found " << x << endl;
 return 0;
}

