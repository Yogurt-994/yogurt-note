#include <iostream>
using namespace std;

long Fib(long n){
 if(n <= 1)return n;
 return Fib(n-2) + Fib(n-1);
}

int main(void){
 for(int i = 1; i <7; i++)
  cout << "Fib(" << i << ") = " << Fib(i) << endl;
 return 0;
}
