/*
陈老师：
  我是刘志鹏，有个问题想向您请教一下，在您新版的《数据结构——使用C++语言描述》人民邮电出版社的教材中，Prim算法是ExtLGraph类的一个成员函数，ExtLGraph继承自LGraph类，而LGraph类是一个有向图的邻接表存储结构类。
这样在运行Prim算法的时候会出现与实际情况不同的结果。您是如何解决这个问题的？
附录是我编写的Prim算法的源程序。
                        刘志鹏
                        2006-9-19 19 10:58
*/
#include <iostream>
using namespace std;

enum ResultCode{Underflow, Overflow, Success,
	        Duplicate, NotPresent, Failure,HasCycle,
	        OutofBounds};

template<class T>
struct ENode{
 ENode(){nextArc =NULL;}
 ENode(int vertex, T weight, ENode* next){
  adjVex =vertex; w =weight; nextArc =next;
 }
 int adjVex;
 T w;
 ENode* nextArc;
};

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
struct LGraph: public Graph<T>{
 public:
  LGraph(int mSize);
  ~LGraph();
  ResultCode Insert(int u, int v, T& w);
  ResultCode Remove(int u, int v);
  bool Exist(int u, int v)const;
  int Vertices()const{return n;}
  void Output();
 protected:
  ENode<T>** a;
  int n, e;
};

template<class T>
void LGraph<T>::Output(){
 ENode<T>* q;
 for(int i =0;i <n; i++){
  q =a[i];
    //a[i]本身已经是第一个结点的地址，故而不能写成q=a[i]->adjVex!!
  while(q){
   cout << "(" << i << "  " 
        <<  q->adjVex << "  " << q->w << ")  ";
   q =q->nextArc;
  }
  cout << endl;
 }
 cout << endl << endl;
}

template<class T>
LGraph<T>::LGraph(int mSize){
 n = mSize; e =0;
 a =new ENode<T>*[n];
 for(int i=0; i<n; i++)a[i] =NULL;
}

template<class T>
LGraph<T>::~LGraph(){
 ENode<T>*p, *q;
 for(int i =0;i <n; i++){
  p =a[i]; q =p;
  while(p){
   p =p->nextArc; delete q; q =p;
  }
 }
 delete []a;
}

template<class T>
bool LGraph<T>::Exist(int u, int v)const{
 if(u <0 || v<0 || u>n-1 || v>n-1 || u==v) return false;
 ENode<T>* p =a[u];
 while(p && p->adjVex != v)p=p->nextArc;
 if(!p) return false; 
  else return true;
}

template<class T>
ResultCode LGraph<T>::Insert(int u, int v, T& w){
 if(u <0 || v <0 || u>n-1 || v >n-1 || u ==v) return Failure;
 if(Exist(u, v)) return Duplicate;
 ENode<T>* p = new ENode<T>(v, w, a[u]);
 a[u] =p; e++;
 return Success;
}

template<class T>
ResultCode LGraph<T>::Remove(int u, int v){
 if(u <0 || v <0 || u>n-1 || v>n-1 || u ==v) return Failure;
 ENode<T>* p =a[u], *q = NULL;
 while(p&&p->adjVex != v){
  q =p; p=p->nextArc;
 } 
 if(!p) return NotPresent;
 if(q) q->nextArc =p->nextArc;
  else a[u]=p->nextArc;
 delete p;
 e--;
 return Success;
}

//===============================================

template<class T>
class ExtLGraph: public LGraph<T>{
 public:
  ExtLGraph(int mSize):LGraph<T>(mSize){}
  void Prim(int k, int* nearest, T* lowcost);
 private:
  static const int INFTY = 999;
};

template<class T>
void ExtLGraph<T>::Prim(int k, int* nearest, T* lowcost){
 bool* mark = new bool[LGraph<T>::n];
 ENode<T>* p;
 if(k < 0 || k>LGraph<T>::n-1) throw OutofBounds;
 for(int i =0; i < LGraph<T>::n; i++){
  nearest[i] = -1; mark[i] = false;
  lowcost[i] = INFTY;
 }
 lowcost[k] =0; nearest[k] = k; mark[k] =true;
 for(int i = 1; i<LGraph<T>::n; i++){
  for(p = LGraph<T>::a[k]; p; p=p->nextArc){
   int j =p->adjVex;
   if((!mark[j]) && (lowcost[j] > p->w)){
    lowcost[j] = p->w; 
    nearest[j] = k;
   }
  }
  T min = INFTY;
  for(int j =0; j <LGraph<T>::n; j++)
   if((!mark[j]) && (lowcost[j] < min)){
    min = lowcost[j];  k =j;
   }
   mark[k] =true;
 }
 /*for(int i = 0; i < 6; i++)
  cout << mark[i] << "\t";
 cout << endl;*/
}

//==================================================

int main(void){
 const int size = 6;
 ExtLGraph<int> lg(size);
 cout << endl << endl 
      << "逐步建构图9-11的Prim算法(P200)"  << endl << endl;
 int w =5; lg.Insert(0, 3, w); lg.Insert(3, 0, w); 
 w =6; lg.Insert(0, 1, w); lg.Insert(1, 0, w);
 w =1; lg.Insert(0, 2, w); lg.Insert(2, 0, w);
 w =5; lg.Insert(2, 3, w); lg.Insert(3, 2, w);
 w =5; lg.Insert(2, 1, w); lg.Insert(1, 2, w);
 w =3; lg.Insert(1, 4, w); lg.Insert(4, 1, w);
 w =6; lg.Insert(2, 4, w); lg.Insert(4, 2, w);
 w =4; lg.Insert(2, 5, w); lg.Insert(5, 2, w);
 w =5; lg.Insert(3, 5, w); lg.Insert(5, 3, w);
 w =6; lg.Insert(4, 5, w); lg.Insert(5, 4, w);
 //LGraph是有向图，最后的结果与事实不符合
 int* nearest = new int[size];
 int* lowcost = new int[size];
 lg.Prim(0, nearest, lowcost);
 for(int j =0; j< size; j++)
  cout << "(" << nearest[j] << "," << j
       << "," << lowcost[j] << ")\t";
 delete []nearest;
 delete []lowcost;
 cout << "为什么中间一个会与实际结果不同？陈老师是如何解决这个问题的？"
      << endl;
 return 0;
}
