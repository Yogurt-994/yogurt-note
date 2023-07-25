#include <iostream>
#include <cassert>
using namespace std;

enum ResultCode{Underflow, Overflow, Success, 
		Duplicate, NotPresent};
const int MaxNum = 9999;
template<class T>
class DynamicSet{
 public:
  virtual ResultCode Search(T& x)const=0;
  virtual ResultCode Insert(T& x)=0;
  virtual ResultCode Remove(T& x)=0;
  virtual ~DynamicSet(){}
  //virtual bool IsEmpty()const=0;
  //virtual bool IsFull()const=0;
};

template<class T>
struct BTNode{
 BTNode(){lChild = rChild = NULL;}
 BTNode(const T& x){
  element =x;
  lChild = rChild = NULL;
 }
 BTNode(const T& x, BTNode<T>* l, BTNode<T>* r){
  element = x;
  lChild = l; 
  rChild = r;
 }
 T element;
 BTNode<T>* lChild, *rChild;
};

template<class T>
class BSTree:public DynamicSet<T>{
 public:
  BSTree(){root = NULL;}
  virtual ~BSTree(){Clear(root);}
  ResultCode Search(T& x)const;
  ResultCode Insert(T& x);
  ResultCode Remove(T& x);
  void Clear(BTNode<T>* t){
   if(t){
    Clear(t->lChild);
    Clear(t->rChild);
    cout << "delete " << t->element << "..." << endl;
    delete t;
   }
  }
 protected:
  BTNode<T>* root;
 private:
  ResultCode Search(BTNode<T>* p, T& x)const;
};

template<class T>
ResultCode BSTree<T>::Search(T& x)const{
 return Search(root, x);
}

template<class T>
ResultCode BSTree<T>::Search(BTNode<T>* p, T& x)const{
 if(!p) return NotPresent;
 else if(x < p->element)return Search(p->lChild, x);
 else if(x > p->element)return Search(p->rChild, x);
 else{
   x = p->element;
   return Success;
 }
}

template<class T>
ResultCode BSTree<T>::Insert(T& x){
 BTNode<T>* p=root,*q=NULL;
 while(p){
  q = p;
  if(x<p->element)p=p->lChild;
  else if(x>p->element)p=p->rChild;
  else{
   x =p->element; return Duplicate;
  }
 }
 p=new BTNode<T>(x);
 if(!root) root =p;
 else if(x < q->element)q->lChild =p;
 else q->rChild =p;
 return Success;
}

template<class T>
ResultCode BSTree<T>::Remove(T& x){
 BTNode<T>*c,*s,*r,*p=root,*q=NULL;
 while(p && p->element !=x){
  q =p;
  if(x<p->element)p=p->lChild;
  else p=p->rChild;
 }
 if(!p)return NotPresent;
 x =p->element;
 if(p->lChild && p->rChild){
  s=p->rChild; r=p;
  while(s->lChild){r=s;s=s->lChild;}
  p->element =s->element;
  p=s; q=r;
 }
 if(p->lChild)c=p->lChild; 
   else c=p->rChild;
 if(p==root) root =c;
 else if(p==q->lChild)q->lChild =c;
 else q->rChild = c;
 delete p;
 return Success;
}

int main(void){
 BSTree<int> bsTree;
 int x =28; bsTree.Insert(x); x=21; bsTree.Insert(x);
 x=25; bsTree.Insert(x); x=36; bsTree.Insert(x);
 x=33; bsTree.Insert(x); x=43; bsTree.Insert(x);
 return 0;
}
