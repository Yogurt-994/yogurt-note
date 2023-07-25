#include <iostream>
#include <cassert>
using namespace std;

template<class T>
class PrioQueue{
 public:
  PrioQueue(int mSize = 20);
  ~PrioQueue(){delete []q;}
  bool IsEmpty()const{return n==0;}
  bool IsFull()const{return n==maxSize;}
  void Append(const T& x);
  void Serve(T& x);
 private:
  void AdjustDown(int r, int j);
  void AdjustUp(int j);
  void Print();
  T* q;
  int n, maxSize;
};

template<class T>
void PrioQueue<T>::Print(){
 for(int i = 0; i < n; i++)
  cout << q[i] << "\t";
 cout << endl;
}

template<class T>
PrioQueue<T>::PrioQueue(int mSize){
 maxSize = mSize;
 n =0;
 q =new T[maxSize];
}

template<class T>
void PrioQueue<T>::AdjustUp(int j){
 int i =j;
 T temp = q[i];
 while(i > 0 && temp<q[(i-1)/2]){
  q[i] = q[(i-1)/2];
  i = (i-1)/2;
 }
 q[i]=temp;
 Print();
}

template<class T>
void PrioQueue<T>::Append(const T& x){
 assert(!IsFull());
 q[n++] =x;
 AdjustUp(n-1);
}

template<class T>
void PrioQueue<T>::Serve(T& x){
 assert(!IsEmpty());
 x =q[0]; q[0]=q[--n];
 AdjustDown(0, n-1);
}

template<class T>
void PrioQueue<T>::AdjustDown(int r, int j){
 int child = 2* r +1;
 T temp = q[r];
 while(child <= j){
  if((child<j)&&(q[child]>q[child+1]))
   child++;
  if(temp<=q[child]) break;
  q[(child-1)/2]=q[child];
  child=2*child +1;
 }
 q[(child-1)/2]=temp;
 Print();
}

int main(void){
 PrioQueue<int> pq;
 pq.Append(71); pq.Append(74); pq.Append(2);
 pq.Append(54); pq.Append(93); pq.Append(52);
 pq.Append(28);
 int i;
 cout << endl;
 pq.Serve(i); pq.Serve(i);
 return 0;
}
