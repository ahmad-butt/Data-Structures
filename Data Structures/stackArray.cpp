#include <iostream>
using namespace std;

template <class T>
class Stack{ 
	T *x;
	int p, size;
public:
	Stack(int s=10){	size = s; x = new T[size];	p = 0;	}
	bool isFull(){	return p == size;						}
	bool isEmpty(){	return p == 0;						}
	void push(T d){
		if (isFull())	throw (size);
		x[p++]	= d;
	}
	T pop(){
		if (!isEmpty());
		return x[--p];
	}
	T seeTop(){
		if (!isEmpty());	
		return x[p-1];
	}
	~Stack(){	delete []x;	}
};
// int main() {
// 	Stack<int> stack;
// 	stack.push(10);
// 	stack.push(1);
// 	stack.push(0);
// 	stack.push(100);
// 	cout << stack.pop() << '\n';
// 	cout << stack.pop() << '\n';
// 	cout << stack.pop() << '\n';
// 	cout << stack.pop() << '\n';
// }