#include <iostream>
using namespace std;

const int INFINITY = 999;
 
template<class T>
void Swap(T& a, T& b){
 T temp = a;
 a = b;
 b = temp;
}

template<class T>
void QuickSort(T A[], int n){
  QSort(A, 0, n-1);
}

template<class T>
void QSort(T A[], int left, int right){
 int i, j;
 static int count = 1;
 if(left < right){
  i = left; j =right +1;
  do{
   do i++; while(A[i] < A[left]);
   do j--; while(A[j] > A[left]);
   if(i <j) Swap(A[i],A[j]);
  }while(i < j);
  Swap(A[left], A[j]);
  cout << "╣з" << count++ << "лк\t";
  for(int k = 0; k < 8; k++){
   if(A[k] == INFINITY)
    cout << "INF" << "\t";
   else cout <<  A[k] << "\t";
  }
  cout << endl;
  QSort(A, left, j-1);
  QSort(A, j+1, right);
 }
}

int main(void){
 int ia[] = {48, 36, 68, 72, 12, 48, 02, INFINITY};
 int n = sizeof ia /sizeof ia[0];
 QuickSort(ia, n);
 return 0;
}
