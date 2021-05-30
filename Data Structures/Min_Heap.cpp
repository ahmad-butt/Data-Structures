#include <bits/stdc++.h>
using namespace std;

template <class T>
class MinHeap{
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
    T _getMinimum() {
        return arr[0];
    }

    //Adjust heap from bottom to top (Swap elements of heap until all child nodes are greater than parent node)
    void _adjustBottomToTop(int index, int newData) {
        arr[index] = newData;
        // while(index!=0 and arr[index] < arr[_getParent(index)]) {
        //     _swap(&arr[index], &arr[_getParent(index)]);
        //     index = _getParent(index);
        // }
        for(int i=index; i!=0 and arr[i] < arr[_getParent(i)]; i = _getParent(i)) {
            _swap(&arr[i], &arr[_getParent(i)]);
        }
    }

    //Adjust heap from top to bottom after deletion of Min element (Swap lowest node to parent node than swap with Min child until heap properties are satisfied)
    //than return Min element
    void _heapify(int index) {
        int left = _getLeft(index);
        int right = _getRight(index);
        int minimum = index;
        if(left < size and arr[left] < arr[minimum])
            minimum = left;
        if(right < size and arr[right] < arr[minimum])
            minimum = right;
        if(minimum!=index) {
            _swap(&arr[index],&arr[minimum]);
            _heapify(minimum);
        }
    }
public:
    MinHeap(int capacity) : capacity(capacity), size(0) {
        arr = new T[capacity];
    }
    
    //Insert Element in heap
    void insert(T data) {
        if(size==capacity) {
            throw "ERROR: Can't insert more elements because Capcaity is Full\n";
        }
        int index = size;
        _adjustBottomToTop(index, data);
        size++;
    }

    //Delete Minimum Element from heap
    T extractMinimum() {
        if(size <= 0) {
            throw "ERROR: Can't delete further because Heap is empty.\n";
        }
        if(size==1) {
            size--;
            return _getMinimum();
        }
        T toExtract = _getMinimum();
        arr[0] = arr[size-1];
        size--;
        _heapify(0);

        return toExtract;
    }
};

int main() {
    MinHeap<int> h(11);
    try{
        h.insert(23);
        h.insert(34);
        h.insert(56);
        h.insert(68);
        h.insert(15);
        h.insert(78);
        h.insert(24);
        h.insert(38);
    } catch (const char *str) {
        cout << str;
    }
    try{
        cout << h.extractMinimum() << " ";
        cout << h.extractMinimum() << " ";
        cout << h.extractMinimum() << " ";
        cout << h.extractMinimum() << " ";
        cout << h.extractMinimum() << " ";
        cout << h.extractMinimum() << " ";
        cout << h.extractMinimum() << " ";
        cout << h.extractMinimum() << " ";
    } catch (const char *str) {
        cout << '\n' << str;
    }
    return 0;
}