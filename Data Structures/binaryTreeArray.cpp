#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

#define NONODE -1

class BTreeArray{
	int *x, size;
public:
	BTreeArray(int *x, const int SIZE){
		size = SIZE;
		this->x = new int[size];
		for (int i=0;i<size;i++)
			this->x[i] = x[i];
	}
	void preOrder(int i){
		if (i >= size || x[i] == NONODE)
			return;
		cout << x[i] << ' ';
		preOrder(2*i);
		preOrder(2*i+1);
	}
	void preOrder(){
		preOrder(1);
		cout << '\n';
	}
	void inOrder(int i){
		if (i >= size || x[i] == NONODE)
			return;
		inOrder(2*i);
		cout << x[i] << ' ';
		inOrder(2*i+1);
	}
	void inOrder(){
		inOrder(1);
		cout << '\n';
	}
	void postOrder(int i){
		if (i >= size || x[i] == NONODE)
			return;
		postOrder(2*i);
		postOrder(2*i+1);
		cout << x[i] << ' ';
	}
	void postOrder(){
		postOrder(1);
		cout << '\n';
	}
	int findHeight(int i){
		if (i>=size || x[i]==NONODE)	return -1;
		int h1 = findHeight(2*i);
		int h2 = findHeight(2*i+1);
		if (h1 > h2)	return h1+1;
		else 			return h2+1;
	}
	int findHeight(){
		return findHeight(1);
	}
    bool isBST(int index, long long MIN, long long MAX) {
        if(index>=size || x[index]==NONODE)
            return true;
        if(x[index] > MIN and x[index] < MAX and isBST(2*index,MIN,x[index]) and isBST(2*index+1,x[index],MAX))
            return true;
        return false;
    }
    bool isBST() {
        return isBST(1,INT64_MIN,INT64_MAX);
    }
	~BTreeArray(){	delete []x;	}
};
int main(){
	int d[]={NONODE,25,36,48,54,29,NONODE,38,NONODE,NONODE,42,56,NONODE,NONODE,NONODE,43,NONODE,NONODE,NONODE,NONODE,
				50,40,NONODE,NONODE,NONODE,NONODE,NONODE,NONODE,NONODE,NONODE,58,27};
	BTreeArray tree(d, 32);
	tree.preOrder();
	tree.inOrder();
	tree.postOrder();
	cout << tree.isBST() << '\n';
    int arr[] = {NONODE,10,8,11,5,9,NONODE,NONODE};
    BTreeArray tree1(arr, 7);
    tree1.postOrder();
    tree1.inOrder();
    tree1.preOrder();
    cout << "Height: " << tree1.findHeight() << '\n';
    cout << tree1.isBST() << '\n';
	return 0;
}
