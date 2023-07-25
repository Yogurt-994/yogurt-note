#include <iostream>
using namespace std;

void rsum(int list[], int n){
 if(--n >=0){
  cout << list[n] << " ";
  rsum(list, n);
 }
}

int main(void){
 int list[] ={8, 9, 34, 77, 99};
 int n = 5;
 rsum(list, n);
 return 0;
}
