#include <iostream>
using namespace std;

enum ResultCode{Underflow, Overflow, Success, Duplicate, NotPresent};
const int NeverUsed = -100;

template<class T>
class DynamicSet{
 public:
  virtual ResultCode Search(T& x) =0;
  virtual ResultCode Insert(T& x)=0;
  virtual ResultCode Remove(T& x)=0;
};

template<class T>
class HashTable:public DynamicSet<T>{
 public:
  HashTable(int divisor = 11);
  ~HashTable(){delete []ht; delete []empty;}
  ResultCode Search(T& x);
  ResultCode Insert(T& x);
  ResultCode Remove(T& x);
  void Output();
 private:
  ResultCode Find(T& x, int& pos);
  T h(T x);
  int M;
  T* ht;
  bool* empty;
};

template<class T>
void  HashTable<T>::Output(){
 for(int j = 0; j < M; j++)
  cout << j << "   ";
 cout << endl;
 for(int i =0; i < M; i++){
  if(ht[i]== NeverUsed)
   cout << "NU" << "  ";
  else cout << ht[i] << "  ";
 }
 cout << endl;
 for(int k = 0; k < M; k++){
  if(empty[k] == true)
   cout << "T " << "  ";
  else cout << "F " << "  ";
 }
  cout << endl << endl;
}

template<class T>
T HashTable<T>::h(T x){
 return x % 11;
}

template<class T>
HashTable<T>::HashTable(int divisor){
 M =divisor;
 ht =new T[M];
 empty =new bool[M];
 for(int i=0; i<M; i++)empty[i]=true;
 for(int i=0; i<M; i++)ht[i] =NeverUsed;
}

template<class T>
ResultCode HashTable<T>::Find(T& x, int& pos){
 pos =h(x);
 int i =pos, j =-1;
 do{
  if(ht[pos] ==NeverUsed && j==-1)j =pos;
  if(empty[pos])break;
  if(ht[pos] ==x){
   x =ht[pos]; return Success;
  }
  pos =(pos +1)%M;
 }while(pos !=i);
 if(j ==-1) return Overflow;
 pos =j; return NotPresent;
}

template<class T>
ResultCode HashTable<T>::Search(T& x){
 int pos;
 if(Find(x, pos)== Success) return Success;
 return NotPresent;
}

template<class T>
ResultCode HashTable<T>::Insert(T& x){
 int pos;
 ResultCode result = Find(x, pos);
 if(result == NotPresent){
  ht[pos]=x; empty[pos]=false;
  return Success;
 }
 if(result ==Success)return Duplicate;
 return Overflow;
}

template<class T>
ResultCode HashTable<T>::Remove(T& x){
 int pos;
 if(Find(x, pos)==Success){
  ht[pos] =NeverUsed;
  return Success;
 }
 return NotPresent;
}

int main(void){
 HashTable<int> ht;
 int x = 80; ht.Insert(x); ht.Output();
 x = 80; ht.Insert(x); ht.Output();
 x = 40; ht.Insert(x); ht.Output();
 x = 65; ht.Insert(x); ht.Output();
 x = 58; ht.Insert(x); ht.Output();
 x = 24; ht.Insert(x); ht.Output();
 x = 35; ht.Insert(x); ht.Output();
 x = 58; ht.Remove(x); ht.Output();
 return 0;
}
