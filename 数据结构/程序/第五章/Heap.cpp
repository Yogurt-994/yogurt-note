#include <iostream>
using namespace std;

template<class T>
void AdjustDown(T heap[], int r, int j){
 int child = 2* r +1;
 T temp = heap[r];
 while(child <= j){
  if((child<j)&&(heap[child]>heap[child+1]))
   child++;
  if(temp<=heap[child]) break;
  heap[(child-1)/2]=heap[child];
  child=2*child +1;
 }
 heap[(child-1)/2]=temp;
 cout << "µÚ" << (-r +4) << "±é\t";
 for(int i =0; i <= j; i++)
  cout << heap[i] << "\t";
 cout << endl;
}

template<class T>
void CreateHeap(T heap[], int n){
 for(int i=(n-2)/2;i>-1;i--)
  AdjustDown(heap, i, n-1);
}

int main(void){
 int heap[] = {61,28,81,43,36,47,83,5};
 cout << "³õÊ¼ÐòÁÐ";
 for(int i =0; i < 8; i++)
  cout << heap[i] << "\t";
 cout << endl;
 CreateHeap(heap,8);
 return 0;
}
