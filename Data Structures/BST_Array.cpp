#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define NONODE -1

class BSTreeArray{
	int *x, size;
public:
	BSTreeArray(const int SIZE){
		size = SIZE;
		this->x = new int[size];
		for (int i=0;i<size;i++)
			x[i] = NONODE;
	}
	BSTreeArray(int *x, const int SIZE){
		size = SIZE;
		this->x = new int[size];
		for (int i=0;i<size;i++)
			this->x[i] = x[i];
	}
	//Worker Function
	void insert(int index, int data){
		if (index>=size)	return;
		if (x[index] == NONODE)	{
			x[index] = data;
			return;
		}
		if (x[index]>data)	
			insert(index*2, data);
		else
			insert(index*2+1, data);
	}
	//Wrapper Function
	void insert(int data){
		insert(1, data);
	}
	int findHighest(int index){
		while (index*2+1 < size && x[index*2+1]!=NONODE)
			index = index * 2 + 1;
		return index;
	}
	int findLowest(int index){
		while (index*2 < size && x[index*2]!=NONODE)
			index = index * 2 ;
		return index;
	}
	bool isNode(int index){
		if (index<size && x[index] != NONODE)	return true;
		return false;
	}
	void deleteNode(int index, int data){
		if (index>=size)		return;
		if (x[index]== NONODE)	return;
		if (x[index]>data)	
			deleteNode(index*2, data);
		else if (x[index]<data)
			deleteNode(index*2+1, data);
		else{//data found
			if (!isNode(index*2) && !isNode(index*2+1)){
				x[index] = NONODE;
				return;
			}
			else if (!isNode(index*2)){
				int lowestIndex = findLowest(index*2+1);
				x[index] = x[lowestIndex];
				deleteNode (lowestIndex, x[lowestIndex]);
			}
			else{
				int highestIndex = findHighest(index*2);
				x[index] = x[highestIndex];
				deleteNode (highestIndex, x[highestIndex]);
			}
		}	
	}	
	void deleteNode(int data){
		deleteNode(1, data);
	}
	int findNode(int index, int data){
		if (index>=size)		return -1;
		if (x[index]== NONODE)	return -1;
		if (x[index]>data)	
			return findNode(index*2, data);
		else if (x[index]<data)
			return findNode(index*2+1, data);
		else
			return index;
	}	
	int findNode(int data){
		return findNode(1, data);
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

	//Part-1: Sum of Nodes
	int sumOfNodes(int index) {
		if(index >= size or x[index]==NONODE)
			return 0;
		int sum = 0;
		sum += sumOfNodes(2*index);
		sum = sum+x[index];
		sum += sumOfNodes(2*index+1);

		return sum;
	}
	void sumOfNodes() {
		cout << "Sum of Tree is: " << sumOfNodes(1) << '\n';
	}

	//Part-2: count of sub-tree
	int countOfNodes(int root) {
		if(root>=size or x[root]==NONODE)
			return 0;
		return 1+countOfNodes(2*root)+countOfNodes(2*root+1);
	}

	//Part-3: compare trees
	bool compare(int index, BSTreeArray tree2) {
		// if both trees are empty
		if((x[index]==NONODE) and (tree2.x[index]==NONODE))
			return true;
		// if one tree is empty
		else if((x[index]==NONODE) and (tree2.x[index]!=NONODE))
			return false;
		else if((x[index]!=NONODE) and (tree2.x[index]==NONODE))
			return false;
		// if both are non-empty
		else {
			if(x[index]==tree2.x[index] and compare(2*index,tree2) and compare(2*index+1,tree2))
				return true;
			else
				return false;
		}
	}
	void compare(BSTreeArray tree2) {
		if(compare(1, tree2))
			cout << "Trees are identical\n";
		else
			cout << "Trees are not identical\n";
	}

	//Part-4 :is BST or not
	bool isBST(int index, long long MIN, long long MAX) {
        if(index>=size || x[index]==NONODE)
            return true;
        if(x[index] > MIN and x[index] < MAX and isBST(2*index,MIN,x[index]) and isBST(2*index+1,x[index],MAX))
            return true;
        return false;
    }
    void isBST() {
        if(isBST(1,INT64_MIN,INT64_MAX))
			cout << "Tree is Binary Search Tree\n";
		else
			cout << "Tree is not Binary Search Tree\n";
    }

	~BSTreeArray(){	delete []x;	}
};
int main(){
	srand(time(0));
	int d ;
	BSTreeArray tree1(2048);
	BSTreeArray tree2(2048);
	int arr1[] = {NONODE,25,36,48,54,29,NONODE,38,NONODE,NONODE,42,56,NONODE,NONODE,NONODE,43};
	BSTreeArray tree3(arr1,16);
	int arr[10] = {10, 8, 11, 5, 9};
	for(int i=0; i<5; i++) {
		tree1.insert(arr[i]);
		tree2.insert(arr[i]);
	}
	cout << "\n\t====Data for Tree-1====\n\n";
	cout << "Inorder Traversal of tree-1: ";
	tree1.inOrder();
	tree1.sumOfNodes();
	cout << "Number of Nodes: " << tree1.countOfNodes(1) << '\n';
	cout << "\n\t====Data for Tree-2====\n\n";
	cout << "Inorder Traversal of tree-2: ";
	tree2.inOrder();
	tree2.sumOfNodes();
	cout << "Number of Nodes: " << tree2.countOfNodes(1) << '\n';
	cout << "\n\t====Data for Tree-3====\n\n";
	cout << "Considering arr1[] as tree-3: \n";
	tree3.sumOfNodes();
	cout << "Number of Nodes: " << tree3.countOfNodes(1) << '\n';
	cout << "\n--------------------------------------\n";
	cout << "\nComparing tree-1 and tree-2\n";
	tree1.compare(tree2);
	cout << "\n--------------------------------------\n";
	cout << "\nComparing tree-1 and tree-3\n";
	tree1.compare(tree3);
	cout << "\n--------------------------------------\n";

	cout << "\nChecking if tree-1 is binary or not\n";
	tree1.isBST();
	cout << "\n--------------------------------------\n";

	cout << "\nChecking if tree-2 is binary or not\n";
	tree1.isBST();
	cout << "\n--------------------------------------\n";

	cout << "\nChecking if tree-3 is binary or not\n";
	tree3.isBST();
	cout << "\n--------------------------------------\n";

	tree2.insert(100);
	cout << "\nInserting in tree-2 and comparing again with tree-1\n";
	tree1.compare(tree2);
	cout << "\n--------------------------------------\n";
	return 0;
}