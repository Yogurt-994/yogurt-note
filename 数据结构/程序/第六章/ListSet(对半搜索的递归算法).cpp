#include <iostream>
#include <cassert>
using namespace std;

enum ResultCode{Underflow, Overflow, Success, 
		Duplicate, NotPresent};
const int MaxNum = 9999;
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
  int BSearch(T& x, int low, int high)const;
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
 int i=BSearch(x, 0, n-1);
 if(i ==-1)return NotPresent;
 x =l[i];
 return Success;
}

template<class T>
int ListSet<T>::BSearch(T& x, int low, int high)const{
 if(low <= high){
  int m=(low+high)/2;
  if(x <l[m]) return BSearch(x, low, m-1);
  if(x >l[m]) return BSearch(x, m+1, high);
  return m;
 }
 return -1;
}

int main(void){
 ListSet<int> ls(20);
 cout << "初始序列\n";
 int x = 21; ls.Insert(x); x = 30; ls.Insert(x);
 x = 36; ls.Insert(x); x = 41; ls.Insert(x);
 x = 52; ls.Insert(x); x = 54; ls.Insert(x);
 x = 66; ls.Insert(x); x = 72; ls.Insert(x);
 x = 83; ls.Insert(x); x = 97; ls.Insert(x);
 ls.Print();
 cout << endl;
 x = 66;
 if(ls.Search(x)==Success) cout << "Found " << x << endl;
  else cout << "Not Found " << x << endl;
 return 0;
}

