#include <iostream>
using namespace std;

template<class T>
class Queue{
 public:
  virtual bool IsEmpty()const = 0;
  virtual bool IsFull()const = 0;
  virtual bool Front(T& x)const =0;
  virtual bool EnQueue(T x)=0;
  virtual bool DeQueue()=0;
  virtual void Clear()=0;
};

template<class T>
class SeqQueue:public Queue<T>{
 public:
  SeqQueue(int mSize);
  ~SeqQueue(){delete []q;}
  bool IsEmpty()const{return front==rear;}
  bool IsFull()const{return (rear+1)%maxSize ==front;}
  bool Front(T& x)const;
  bool EnQueue(T x);
  bool DeQueue();
  void Clear(){front = rear = 0;}
 private:
  int front, rear;
  int maxSize;
  T* q;
};

template<class T>
SeqQueue<T>::SeqQueue(int mSize){
 maxSize = mSize;
 q = new T[maxSize];
 front = rear = 0;
}

template<class T>
bool SeqQueue<T>::Front(T& x)const{
 if(IsEmpty()){
  cout << "Empty" << endl;
  return false;
 }
 x = q[(front +1)%maxSize];
 return true;
}

template<class T>
bool SeqQueue<T>::EnQueue(T x){
 if(IsFull()){
  cout << "Full" << endl;
  return false;
 }
 q[rear=(rear+1)%maxSize]=x;
 return true;
}

template<class T>
bool SeqQueue<T>::DeQueue(){
 if(IsEmpty()){
  cout << "Underflow" << endl;
  return false;
 }
 front=(front +1)%maxSize;
 return true;
}

int main(void){
 SeqQueue<int> sq(20);
 int k;
 for(int i = 0; i < 5; i++)
  sq.EnQueue(i+1);
 for(int j = 0; j < 6; j++){
  if(sq.Front(k)){
   cout << k << " ";
   sq.DeQueue();
  }
 }
 cout << endl;
 return 0;
}
