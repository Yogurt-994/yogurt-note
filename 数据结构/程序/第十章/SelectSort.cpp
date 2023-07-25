#include <iostream>
using namespace std;

template<class T>
void Swap(T& a, T& b){
 T temp = a;
 a = b;
 b = temp;
}

template<class T>
void SelectSort(T A[], int n){
 int small;
 for(int i =0; i <n-1; i++){
  small = i;
  for(int j = i+1; j< n; j++)
   if(A[j] < A[small]) small = j;
  Swap(A[i], A[small]);
  cout << "╣з" << i+1 << "лк\t";
  for(int k = 0; k < n; k++)
   cout <<  A[k] << "\t";
  cout << endl;
 }
}

int main(void){
 int ia[] = {48, 36, 68, 72, 12, 48, 02};
 int n = sizeof ia /sizeof ia[0];
 SelectSort(ia, n);
 
 return 0;
}
