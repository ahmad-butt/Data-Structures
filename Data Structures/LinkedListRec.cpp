#include <iostream>
#define SENT -9999
using namespace std;

/*
addInOrder
deleteNode
printRecReverse
printRec
*/

template <class T>
class LinkedList{
    class Node{
    public:
        Node *next;
        T data;
        friend class LinkedList<T>;
        Node():next(nullptr){}
        Node(T data, Node *next=nullptr):data(data), next(next){}
    };
    Node *head, *tail;
    int size;
public:
    LinkedList():head(nullptr),tail(nullptr),size(0){}
    
    //Testing Methods
    void push_front(T data){
        if(isEmpty()){
            head = new Node(data);
            size+=1;
        } else {
            Node *newNode = new Node(data);
            newNode->next = head;
            head = newNode;
            size+=1;
        }
    }

    void push_back(T data) {
        if(isEmpty()){
            head = new Node(data);
            size+=1;
        }  else {
            Node* newNode = head;
            while(newNode->next!=nullptr){
                newNode = newNode->next;
            }
            newNode->next = new Node(data);
            size+=1;
        }
    }

    bool isEmpty(){
        if(size==0)
            return true;
        return false;
    }

    T peek_head() {
        return head->data;
    }

    //Recursive Methods
    Node* addInOrder(T data, Node* head) {
        if(head==nullptr){
            tail = new Node(data);
            size+=1;
            return tail;
        }
        if(head->data >= data) {
            Node* newNode = new Node(data,head);
            return newNode;
        }
        head->next = addInOrder(data,head->next);
        size+=1;
        return head;
    }

    Node* addInOrder(T data) {
        return head = addInOrder(data,head);
    }

    Node* deleteNode(T data, Node* head){
        if(head==nullptr)
            throw "Either element to delete not found or list is Empty\n";
        if(head->data==data) {
            Node* toReturn = head->next;
            delete head;
            return toReturn;
        }
        head->next = deleteNode(data,head->next);
        return head;
    }

    Node* deleteNode(T data) {
        return head = deleteNode(data,head);
    }

    void printRec(Node *head){
        if(head==nullptr){
            return;
        }
        cout << head->data << " ---> ";
        printRec(head->next);
    }

    void printRec(){
        printRec(head);
        cout << '\n';
    }

    int compareRec(LinkedList<T> list, Node *start) {
        if(size>list.size)
            return 1;
        if(list.size>size)
            return -1;
        if(start->data==list.head->data){
            return 0;
        }
        return compareRec(list,start->next);
    }

    int compareRec(LinkedList<T> list) {
        return compareRec(list,head);
    }

    void merge(Node *head) {
        if(head==nullptr)
            return;
        push_back(head->data);
        merge(head->next);
    }
    void merge(LinkedList<T> list) {
        merge(list.head);
    }

    // void removeDuplicates(Node *start, Node *next) {
    //     if(next==nullptr)
    //         return;
    //     if(start->data==next->data) {
    //         Node *toDel = next;
    //         next = next->next;
    //         delete toDel;
    //         removeDuplicates(start,next);
    //     }
    //     removeDuplicates(start->next,next->next);
    // }

    void removeDuplicates() {
        Node *temp1 = head, *temp2;
        while(temp1->next!=nullptr) {
            temp2 = temp1;
            while(temp2->next!=nullptr) {
                if(temp1->data==temp2->next->data) {
                    Node *toDel = temp2->next;
                    temp2->next = temp2->next->next;
                    delete(toDel);
                } else {
                    temp2 = temp2->next;
                }
            }
            temp1 = temp1->next;
        }
    }

    void removeDuplicatesRec(Node *start) {
        if(start->next==nullptr)
            return;
        Node *tempNode = start;
        if(tempNode->next==nullptr)
            return;
        if(start->data == tempNode->next->data) {
            Node *toDel = tempNode->next;
            tempNode->next = tempNode->next->next;
            removeDuplicatesRec(tempNode->next);
        }
        removeDuplicatesRec(start->next);
    }

    void removeDuplicatesRec() {
        removeDuplicatesRec(head);
    }

    void splitNode(Node* head) {
        if(head==nullptr)
            return;
        if(head->data>=50 and head->data%2==0) {
            T newData = head->data/2;
            head->data = newData;
            head->next = new Node(newData,head->next);
            splitNode(head->next);
        }else if(head->data>=50 and head->data%2!=0) {
            T newData = head->data/2;
            head->data = newData+1;
            head->next = new Node(newData,head->next);
            splitNode(head->next);
        } else splitNode(head->next);
    }

    void splitNode() {
        splitNode(head);
    }

    void printRecReverse(Node *head) {
        if(head==nullptr){
            return;
        }
        printRecReverse(head->next);
        cout << head->data << " ---> ";
    }

    void printRecReverse() {
        printRecReverse(head);
        cout << '\n';
    }

};

int main() {
    LinkedList<int> list;
    list.push_back(46);
    list.push_back(23);
    list.push_back(59);
    list.push_back(37);
    list.push_back(46);
    list.push_back(64);
    list.push_back(46);
    list.push_back(29);
    list.printRec();
    list.removeDuplicatesRec();
    list.printRec();
    return 0;
}