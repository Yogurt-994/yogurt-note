#include <iostream>
using namespace std;

template<class T>
void Swap(T& a, T& b){
 T temp = a;
 a = b;
 b = temp;
}

template<class T>
void BubbleSort(T A[], int n){
 int i, j, last;
 i = n-1;
 while(i >0){
  last =0;
  for(int j =0; j<i; j++)
   if(A[j+1] < A[j]){
    Swap(A[j], A[j+1]);
    last =j;
   }
   i =last;
  cout << "╣з" << n-i-1 << "лк\t";
  for(int k = 0; k < n; k++)
   cout <<  A[k] << "\t";
  cout << endl;
 }
}

int main(void){
 int ia[] = {48, 36, 68, 72, 12, 48, 02};
 int n = sizeof ia /sizeof ia[0];
 BubbleSort(ia, n);
 
 return 0;
}
