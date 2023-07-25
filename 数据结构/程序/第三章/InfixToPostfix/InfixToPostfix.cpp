#include "SeqStack.h"
#include <cctype>
using namespace std;

int icp(const char c){
 int result = -1;
 switch(c){
  case '#': result = 0; break;
  case '(': result = 7; break;
  case '*':
  case '/': result = 4; break;
  case '+':
  case '-': result = 2; break;
  case ')': result = 1;
 }
 return result;
}

int isp(const char c){
 int result = -1;
 switch(c){
  case '#': result = 0; break;
  case '(': result = 1; break;
  case '*':
  case '/': result = 5; break;
  case '+':
  case '-': result = 3; break;
  case ')': result = 7;
 }
 return result;
}

void infixToPostfix(){
 SeqStack<char> s;
 char ch, y;
 s.push('#');
 while(cin >> ch, ch != '#'){
  if(isdigit(ch)||isalpha(ch)) cout << ch;
  else if(ch == ')')
   for(y = s.Top(), s.pop(); y != '('; y = s.Top(), s.pop())
    cout << y;
  else{
   for(y = s.Top(), s.pop(); icp(ch) <= isp(y); y = s.Top(), s.pop())
    cout << y;
   s.push(y); s.push(ch);
  }
 }
 while(!s.isEmpty()){
  y = s.Top(); s.pop();
  if(y != '#') cout << y;
 }
 cout << endl;	
}

int main(void){
 infixToPostfix();
 return 0;
}

/*程序运行结果：
(a + b) * c #
ab+c*
*/
