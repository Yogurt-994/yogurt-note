#include <iostream>
using namespace std;

enum ResultCode{Underflow, Overflow, Success,
	        Duplicate, NotPresent, Failure};

template<class T>
class Graph{
 public:
  virtual ~Graph(){}
  virtual ResultCode Insert(int u, int v, T& w)=0;
  virtual ResultCode Remove(int u, int v)=0;
  virtual bool Exist(int u, int v)const=0;
 protected:
};

template<class T>
class MGraph:public Graph<T>{
 public:
  MGraph(int mSize, const T& noedg);
  ~MGraph();
  ResultCode Insert(int u, int v, T& w);
  ResultCode Remove(int u, int v);
  bool Exist(int u, int v)const;
  int Vertices()const{return n;}
  void Output();
 protected:
  T** a;
  T noEdge;
  int n, e;
};

template<class T>
void MGraph<T>::Output(){
 for(int i =0; i <n; i++){
  for(int j =0; j <n; j++){
   if(a[i][j] == noEdge)
    cout << "NE" << "\t";
   else cout << a[i][j] << "\t";
  }
  cout << endl;
 }
 cout << endl << endl << endl;
}

template<class T>
MGraph<T>::MGraph(int mSize, const T& noedg){
 n =mSize; e =0; noEdge =noedg;
 a = new T*[n];
 for(int i =0; i <n; i++){
  a[i] =new T[n];
  for(int j =0; j <n; j++) a[i][j] =noEdge;
  a[i][i] =0;
 }
}

template<class T>
MGraph<T>::~MGraph(){
 for(int i =0; i<n; i++) delete []a[i];
 delete []a;
}

template<class T>
bool MGraph<T>::Exist(int u, int v)const{
 if(u <0 || v <0 || u >n-1 || v >n-1 || u ==v || a[u][v] ==noEdge)
  return false;
 return true;
}

template<class T>
ResultCode MGraph<T>::Insert(int u, int v, T& w){
  if(u <0 || v <0 || u >n-1 || v >n-1 || u ==v) return Failure;
  if(a[u][v] != noEdge) return Duplicate;
  a[u][v] =w; e++; return Success;
}

template<class T>
ResultCode MGraph<T>::Remove(int u, int v){
 if(u <0 || v <0 || u >n-1 || v >n-1 || u ==v) return Failure;
 if(a[u][v] == noEdge) return NotPresent;
 a[u][v] =noEdge; e--; return Success; 
}

int main(void){
 MGraph<int> mg(4, 99);
 cout << "逐步建构图9-7(f)的邻接矩阵(P178)" << endl;
 int w =4; mg.Insert(1, 0, w); mg.Output(); 
 w =5; mg.Insert(1, 2, w); mg.Output();
 w =3; mg.Insert(2, 3, w); mg.Output();
 w =1; mg.Insert(3, 0, w); mg.Output();  
 w =1; mg.Insert(3, 1, w); mg.Output();
 return 0;
}
