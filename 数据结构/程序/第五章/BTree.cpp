#include <iostream>
using namespace std;

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
class BinaryTree{
 public:
  BinaryTree(){root = NULL;}
  ~BinaryTree(){Clear(root);}
  bool IsEmpty()const;
  void Clear();
  bool Root(T& x)const;
  BTNode<T>* Root();
  void MakeTree(const T& e, BinaryTree<T>& left, 
                            BinaryTree<T>& right);
  void BreakTree(T& e, BinaryTree<T>& left, 
                            BinaryTree<T>& right);
  void PreOrder(void(*Visit)(T& x));
  void InOrder(void(*Visit)(T& x));
  void PostOrder(void(*Visit)(T& x));
  int Size();
  BTNode<T>* Copy(BTNode<T>* t);
  int Count(){ return Count(root);}
 protected:
  BTNode<T>* root;
 private:
  int Size(BTNode<T>* t);
  int Count(BTNode<T>* t){
    if(!t) return 0;
    if(((t->lChild) && (!t->rChild))||((!t->lChild) && (t->rChild)))
      return 1;
    return Count(t->lChild) + Count(t->rChild);
  }
  void Clear(BTNode<T>* t);
  void PreOrder(void(*Visit)(T& x),BTNode<T>* t);
  void InOrder(void(*Visit)(T& x), BTNode<T>* t);
  void PostOrder(void(*Visit)(T& x), BTNode<T>* t);
};

template<class T>
void Visit(T& x){
   cout << x << "\t";
}

template<class T>
BTNode<T>* BinaryTree<T>::Root(){return root;}

template<class T>
void BinaryTree<T>::Clear(BTNode<T>* t){
   if(t){
    Clear(t->lChild);
    Clear(t->rChild);
    cout << "delete " << t->element << "..." << endl;
    delete t;
   }
}

template<class T>
bool BinaryTree<T>::Root(T& x)const{
 if(root){
  x = root->element; 
  return true;
 }
 else return false;
}

template<class T>
void BinaryTree<T>::MakeTree(const T& x, 
	BinaryTree<T>& left,BinaryTree<T>& right){
 if(root || &left == &right) return;
 root = new BTNode<T>(x, left.root, right.root);
 left.root = right.root = NULL;
}

template<class T>
void BinaryTree<T>::BreakTree(T& x, 
	BinaryTree<T>& left,BinaryTree<T>& right){
 if(!root || &left == &root || left.root || right.root)
  return;
 x = root->element;
 left.root = root->lChild;
 right.root = root->rChild;
 delete root;
 root = NULL;
}

template<class T>
void BinaryTree<T>::PreOrder(void(*Visit)(T& x)){
 PreOrder(Visit,root);
}

template<class T>
void BinaryTree<T>::PreOrder(void(*Visit)(T& x), BTNode<T>* t){
 if(t){
  Visit(t->element);
  PreOrder(Visit, t->lChild);
  PreOrder(Visit, t->rChild);
 }
}

template<class T>
void BinaryTree<T>::InOrder(void(*Visit)(T& x)){
 InOrder(Visit,root);
}

template<class T>
void BinaryTree<T>::InOrder(void(*Visit)(T& x), BTNode<T>* t){
 if(t){
  InOrder(Visit, t->lChild);
  Visit(t->element);
  InOrder(Visit, t->rChild);
 }
}

template<class T>
void BinaryTree<T>::PostOrder(void(*Visit)(T& x)){
 PostOrder(Visit,root);
}

template<class T>
void BinaryTree<T>::PostOrder(void(*Visit)(T& x), BTNode<T>* t){
 if(t){
  PostOrder(Visit, t->lChild);
  Visit(t->element);
  PostOrder(Visit, t->rChild);
 }
}

template<class T>
int BinaryTree<T>::Size(){
 return Size(root);
}

template<class T>
int BinaryTree<T>::Size(BTNode<T>* t){
 if(!t) return 0;
 return Size(t->lChild) + Size(t->rChild) + 1;
}

/*
template<class T>
BTNode<T>* BinaryTree<T>::Copy(BTNode<T>* t){
 if(!root) return NULL;
 BTNode<T>* q = new BTNode<T>(t->element);
 q->lChild = Copy(t->lChild);
 q->rChild = Copy(t->rChild);
 return q;
}//Copy到目前为止我还不会在main函数中调用
*/

int main(void){
 BinaryTree<char>a, b, x, y, z;
 y.MakeTree('E', a, b);
 z.MakeTree('F', a, b);
 x.MakeTree('C', y, z);
 y.MakeTree('D', a, b);
 z.MakeTree('B', a, x);
 cout << endl << "PreOrder\t";
 z.PreOrder(Visit);
 cout << endl << "InOrder\t\t";
 z.InOrder(Visit);
 cout << endl << "PostOrder\t";
 z.PostOrder(Visit);
 cout << endl;
 cout << "Tree's Size = " 
      << z.Size() << endl;
 cout << "Tree's Count = "
      << z.Count() << endl;
 return 0;
}
