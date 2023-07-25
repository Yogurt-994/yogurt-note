#include <iostream>
using namespace std;

template<class T>
void InsertSort(T A[], int n){
 for(int i = 1; i < n; i++){
  int j = i;
  T temp =A[i];
  while(j >0 && temp < A[j-1]){
   A[j] =A[j-1]; j--;
  }
  A[j] = temp;
  cout << "╣з" << i << "лк\t";
  for(int k = 0; k < n; k++)
   cout <<  A[k] << "\t";
  cout << endl;
 }
}

int main(void){
 int ia[] = {48, 36, 68, 72, 12, 48, 02};
 int n = sizeof ia /sizeof ia[0];
 InsertSort(ia, n);
 
 return 0;
}
