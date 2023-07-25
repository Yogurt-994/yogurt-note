#include <iostream>
using namespace std;

void sum(int list[], int n){
 while(--n >= 0)
  cout << list[n] << " ";
}

int main(void){
 int list[] ={8, 9, 34, 77, 99};
 int n = 5;
 sum(list, n);
 return 0;
}
