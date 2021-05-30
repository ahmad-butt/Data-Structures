#include <iostream>
#include <string.h>
using namespace std;
template <class T>
class LinkedList {
    class Node {
    public:
        Node* next;
        T data;
        friend class LinkedList<T>;
        Node():next(nullptr){}
        Node(T data, Node *next=nullptr):data(data), next(next){}
    };
    Node *head;
    int size;
public:
    //Contructor
    LinkedList():head(nullptr),size(0){};

    //Utility Functions
    bool isEmpty(){
        if(size==0)
            return true;
        return false;
    }

    int getSize(){
        return size;
    }

    void clear(){
        Node *temp = head;
        while(temp!=nullptr) {
            pop_front();
            temp = temp->next;
        }
    }

    
    //List Operations
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

    void pop_back() {
        if(!isEmpty()) {
            Node *toDelete = head;
            Node *mark = head;
            while(toDelete->next!=nullptr)
                toDelete = toDelete->next;
            while(mark->next->next!=nullptr)
                mark = mark->next;
            mark->next = nullptr;
            delete toDelete;
            toDelete = nullptr;
            mark->next = nullptr;
            size-=1;
        } else {
            cout << "Cannot pop-back from an empty list\n";
        }
    }

    void pop_front() {
        if(!isEmpty()) {
            Node *temp = head;
            head = temp->next;
            delete temp;
            temp = nullptr;
            size-=1;
        }
    }

    T peek_head(){
        return head->data;
    }

    void addNodeAfterNth(T data, int index){
        if(index>getSize() or index<0){
            cout << "Cannot add after " << index << " position\n";
        } else {
            if(index==0) {
                head->next = new Node(data,head->next);
                size+=1;
            } else {
                int count = 0;
                Node* temp = head;
                while(count<index){
                    temp = temp->next;
                    count+=1;
                }
                temp->next = new Node(data,temp->next);
                size+=1;
            }
        }
    }

    void addNodeAfter(T toAdd, T afterThis) {
        if(!isEmpty()) {
            if(head->data == afterThis){
                addNodeAfterNth(toAdd,0);
            } else {
                Node *temp = head;
                while(temp!=nullptr) {
                    if(temp->data==afterThis) {
                        temp->next = new Node(toAdd,temp->next);
                        size+=1;
                        break;
                    }
                    temp = temp->next;
                }
                if(temp==nullptr){
                    cout << "Node to add after is not present\n";
                }
            }   
        } else {
            cout << "List is Empty\n";
        }
    }
    
    void addNodeBeforeNth(T data, int index){
        if(index>getSize() || index<0){
            cout << "Error: You cannot add node before " << index << " position\n";
        } else {
            int count = 0;
            if(index==0){
                Node *temp = new Node(data,head);
                head = temp;
                size+=1;
            } else {
                Node *temp = head;
                while(count<index-1){
                    temp = temp->next;
                    count+=1;
                }
                temp->next = new Node(data,temp->next);
                size+=1;
            }
        }
    }

    void addNodeBefore(T toAdd, T beforeThis) {
        if(!isEmpty()) {
            if(head->data == beforeThis){
                addNodeBeforeNth(toAdd,0);
            } else {
                Node *temp = head;
                while(temp!=nullptr) {
                    if(temp->next->data==beforeThis) {
                        temp->next = new Node(toAdd,temp->next);
                        size+=1;
                        break;
                    }
                    temp = temp->next;
                }
                if(temp==nullptr){
                    cout << "Node to add after is not present\n";
                }
            }   
        } else {
            cout << "List is Empty\n";
        }
    }

    void removeNthNode(int index){
        if(index>getSize() || index<0){
            cout << "Error: You cannot delete node at " << index << " position\n";
        } else {
            if(index==0){
                head = head->next;
                size-=1;
            } else {
                int count = 0;
                Node *temp = head;
                while(count<index-1){
                    temp = temp->next;
                    count+=1;
                }
                Node* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
                toDelete = nullptr;
                size-=1;
            }
        }
    }

    T searchNodeAt(int index) {
        if(index>=getSize() || index<0){
            throw "Error: You cannot search node out of bound\n";
        } else {
            if(index==0){
                return head->data;
            } else {
                int count = 0;
                Node *temp = head;
                while(count<index){
                    temp = temp->next;
                    count+=1;
                }
                return temp->data;
            }
        }
    }

    void searchNode(T data) {
        if(isEmpty()) {
            cout << "List is Empty\n";
        } else {
            int count = -1;
            Node *temp = head;
            for(int i=0; temp!=nullptr; i++){
                if(temp->data==data){
                    count = i;
                    break;
                }
                temp = temp->next;
            }
            if(count!=-1)
                cout << "Node present at position " << count <<'\n';
            else
                cout << "Node not found\n";
        }
    }

    void modify(T toChange, T newValue) {
        if(!isEmpty()) {
            if(head->data==toChange) {
                head->data = newValue;
            } else {
                Node *temp = head;
                while(temp!=nullptr) {
                    if(temp->data==toChange) {
                        temp->data = newValue;
                        break;
                    }
                    temp = temp->next;
                }
                if(temp==nullptr)
                    cout << "Node to modify is not present in list\n";
            }
        } else {
            cout << "List is Empty\n";
        }
    }

    bool compareLists(LinkedList<T> list2) {
        int count = 0;
        for(Node* n1=head; n1!=nullptr; n1 = n1->next) {
            for(Node* n2 = list2.head; n2!=nullptr; n2 = n2->next) {
                if(n1->data==n2->data){
                    count+=1;
                    break;
                }
            }
        }
        if(count==getSize())
            return true;
        return false;
    }

    void bubbleSort() {
        for(Node* n1=head; n1!=nullptr; n1 = n1->next) {
            for(Node* n2=head; n2!=nullptr; n2=n2->next) {
                if(n1->data < n2->data) {
                    T temp = n1->data;
                    n1->data = n2->data;
                    n2->data = temp;
                }
            }
        }
    }

    void removeNegative() {
        while(head->data<0) {
            pop_front();
        }
        while(head->next->data<0){
            head->next = head->next->next;
        }
        // Node *temp = head;
        // while(temp!=nullptr) {
        //     if(temp->next->data<0)
        //         temp->next = temp->next->next;
        //     temp = temp->next;
        // }
    }

    friend ostream& operator << (ostream& out, LinkedList<T>& l){
        if(!l.isEmpty()) {
            Node *temp = l.head;
            while(temp!=nullptr){
                out << temp->data << " ----> ";
                if(temp->next==nullptr)
                    cout << "nullptr";
                temp = temp->next;
            }
            out << '\n';
        } else {
            out << "List is Empty\n";
        }
        return out;
    }
};
int main() {
    
    LinkedList<int> list1;
    list1.push_back(-8);
    list1.push_back(-9);
    list1.push_back(-6);
    list1.push_back(-5);
    list1.push_back(67);
    cout << list1;
    list1.removeNegative();
    cout << list1;
    return 0;
}