#include <bits/stdc++.h>
using namespace std;

template <class T>
class MaxHeap{
    T *arr;     //Pointer to Array of elements in heap
    int capacity;   //Maximum possible size of heap
    int size;   //current number of elements in heap

    void _swap(T *num1, T *num2) {
        *num1 = *num1+*num2;
        *num2 = *num1-*num2;
        *num1 = *num1-*num2;
    }

    int _getParent(int index) {
        return (index/2);
    }
    int _getLeft(int index) {
        return (2*index);
    }
    int _getRight(int index) {
        return (2*index+1);
    }
    T _getMaximum() {
        return arr[0];
    }

    //Adjust heap from bottom to top (Swap elements of heap until all child nodes are smaller than parent node)
    void _adjustBottomToTop(int index, T newData) {
        arr[index] = newData;
        for(int i=index; i!=0 and arr[i] > arr[_getParent(i)]; i=_getParent(i)) {
            _swap(&arr[i], &arr[_getParent(i)]);
        }
    }

    //Adjust heap from top to bottom after deletion of max element (Swap lowest node to parent node than swap with Max child until heap properties are satisfied)
    //than return max element
    void _heapify(int index) {
        int left = _getLeft(index);
        int right = _getRight(index);
        int maximum = index;
        if(left < size and arr[left] > arr[maximum]) {
            maximum = left;
        }
        if(right < size and arr[right] > arr[maximum]) {
            maximum = right;
        }
        if(maximum!=index){
            _swap(&arr[index],&arr[maximum]);
            _heapify(maximum);
        }
    }
public:
    MaxHeap(int capacity) : capacity(capacity), size(0) {
        arr = new T[capacity];
    }

    //Insert Element in heap
    void insert(T data) {
        if(size>=capacity) {
            throw "ERROR: Can't insert more elements because Capcaity is Full\n";
        }
        int index = size;
        _adjustBottomToTop(index,data);
        size++;
    }

    //Delete Maximum Element from heap
    T extractMaximum() {
        if(size<=0) {
            throw "ERROR: Can't delete further because Queue is empty.\n";
        }
        if(size==1) {
            size--;
            return _getMaximum();
        }
        T toExtract = _getMaximum();
        arr[0] = arr[size-1];
        size--;
        _heapify(0);
        return toExtract;
    }

};
int main() {
    MaxHeap<int> h(11);
    int choice, input;

    cout << "\n=> Press 1 to insert element with Prority\n";
    cout << "=> Press 2 to delete element with Priority\n";
    cout << "=> Press 0 to stop simulation\n\n";

    do{
        cin >> choice;
        if(choice==1) {
            cout << "Enter Task with Proirity: ";
            cin >> input;
            try{
                h.insert(input);
                cout << "Task with Proirity " << input << " is added\n";
            } catch (const char *str) {
                cout << str;
            }
        } else if(choice==2) {
            try{
                cout << "Task with proirity "  << h.extractMaximum() << " is removed\n";
            } catch (const char *str) {
                cout << '\n' << str;
            }
        } else if(choice==0){
            cout << "Ending Simulation\n";
        } else {
            cout << "Invalid Operation\n";
        }
        cout << '\n';
    }while(choice!=0);
    return 0;
}