#include <iostream>
#include "stackArray.cpp"
using namespace std;
template <class T>
class circularDoublyList{
    class Node{
    public:
        Node* next;
        Node* previous;
        T data;
        Node(T data):data(data),next(nullptr),previous(nullptr){}
        Node(T data, Node *next, Node *previous):data(data),next(next),previous(previous){}
        friend class circularDoublyList<T>;
    };
    Node *head;
    Node *tail;
public:
    circularDoublyList() {
        head = new Node(0);
        head->next = head;
        head->previous = head;
        tail = head;
    }
    bool isEmpty() {
        if(head->next == head)
            return true;
        return false;
    }

    int peekDummy() {
        return head->data;
    }

    T peek_head() {
        return head->next->data;
    }

    T peek_tail() {
        return tail->data;
    }

    void copyList(circularDoublyList<T> toCopy) {
        Node *temp = toCopy.head->next;
        while(temp!=toCopy.head) {
            push_back(temp->data);
            temp = temp->next;
        }
    }
    
    void push_front(T newData) {
        if(isEmpty()) {
            Node *newNode = new Node(newData,head,head);
            head->next = newNode;
            head->previous = newNode;
        } else {
            Node *newNode = new Node(newData,head->next,head);
            head->next->previous = newNode;
            head->next = newNode;
        }
        tail = head->previous;
        head->data+=1;
    }

    void push_back(T newData) {
        if(isEmpty()) {
            push_front(newData);
        } else {
            Node *newNode = new Node(newData,head,head->previous);
            head->previous->next = newNode;
            head->previous = newNode;
        }
        tail = head->previous;
        head->data+=1;
    }

    void addInOrder(T newData) {
        if(isEmpty()) {
            push_front(newData);
        } else {
            if(newData > head->previous->data) {
                Node *newNode = new Node(newData,head,head->previous);
                head->previous->next = newNode;
                head->previous = newNode;
            } else if(newData < head->next->data) {
                Node *newNode = new Node(newData,head->next,head);
                head->next->previous = newNode;
                head->next = newNode;
            } else {
                Node *temp = head->next;
                while(temp!=head) {
                    if(temp->data > newData) {
                        Node *newNode = new Node(newData,temp,temp->previous);
                        temp->previous->next = newNode;
                        temp->previous = newNode;
                    }
                    temp = temp->next;
                }
            }
        }
        tail = head->previous;
        head->data+=1;
    }

    void insertNodeAfter(int toAddAfter, T newData) {
        int count = 0;
        Node *temp = head->next;
        while(count<toAddAfter) {
            temp = temp->next;
            count++;
        }
        Node *newNode = new Node(newData,temp->next,temp);
        temp->next = newNode;
        temp->next->previous = newNode;
        if(temp==tail) {
            tail = newNode;
        }
    }

    void insertNodeAfterRec(Node *temp, int start, int toAddAfter, T newData) {
        if(start>toAddAfter)
            return;
        if(start==toAddAfter) {
            Node *newNode = new Node(newData,temp->next,temp);
            temp->next = newNode;
            temp->next->previous = newNode;
            if(temp==tail) {
                tail = newNode;
            }            
        }
        insertNodeAfterRec(temp->next,start+1,toAddAfter,newData);
    }

    void insertNodeAfterRec(int toAddAfter, T newData) {
        Node *temp = head->next;
        insertNodeAfterRec(temp,0,toAddAfter,newData);
    }

    void insertNodeBefore(int toAddBefore, T newData) {
        int count = 0;
        Node *temp = head->next;
        while(count<toAddBefore){
            temp = temp->next;
            count+=1;
        }
        Node *newNode = new Node(newData,temp,temp->previous);
        temp->previous->next = newNode;
        temp->previous = newNode;
        if(toAddBefore==0) {
            head = newNode;
        }
    }

    void insertNodeBeforeRec(Node *temp, int start, int toAddBefore, T newData) {
        if(start>toAddBefore)
            return;
        if(start==toAddBefore) {
            Node *newNode = new Node(newData,temp,temp->previous);
            temp->previous->next = newNode;
            temp->previous = newNode;
            if(toAddBefore==0) {
                head = newNode;
            }          
        }
        insertNodeBeforeRec(temp->next,start+1,toAddBefore,newData);
    }    

    void insertNodeBeforeRec(int toAddBefore, T newData) {
        Node *temp = head;
        insertNodeAfterRec(temp,0,toAddBefore,newData);
    }

    void deleteNode(T toDelete) {
        Node *temp = head->next;
        while(temp!=head) {
            if(temp->data==toDelete) {
                temp->previous->next = temp->next;
                temp->next->previous = temp->previous;
            }
            temp = temp->next;
            head->data-=1;
        }
    }

    void deleteNodeFromHead() {
        Node *toDel = head->next;
        head->next = toDel->next;
        toDel->previous = head;
        delete toDel;
        head->data-=1;
    }

    void deleteNodeFromTail() {
        Node *toDel = tail;
        toDel->previous->next = head;
        head->previous = toDel->previous;
        tail = toDel->previous;
        delete toDel;
        head->data-=1;
    }

    void deleteAll() {
        Node *current = head->next;
        Node *toDel;
        while(current!=head) {
            toDel = current;
            head->next = current->next;
            current->next->previous = head;
            current = current->next;
            delete toDel;
        }
    }

    void removeDuplicates() {
        Node *current = head->next;
        while(current!=head) {
            T val = current->data;
            Node *currNext = current->next;
            while(currNext!=head) {
                if(currNext->data==val) {
                    currNext->next->previous = currNext->previous;
                    currNext->previous->next = currNext->next;
                }
                currNext = currNext->next;
            }
            current = current->next;
        }
    }

    void difference(circularDoublyList<T> list) {
        Node *toRemove = list.head->next;
        while(toRemove!=list.head) {
            deleteNode(toRemove->data);
            toRemove = toRemove->next;
        }
    }

    bool isExist(T val) {
        Node *temp = head->next;
        while(temp!=head) {
            if(temp->data==val)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void appendUnCommon(circularDoublyList<T> list) {
        Node *toAdd = list.head->next;
        while(toAdd!=list.head) {
            if(!isExist(toAdd->data)) {
                push_back(toAdd->data);
            }
            toAdd = toAdd->next;
        }
    }

    T accumulate() {
        T sum = 0;
        Node *temp = head->next;
        while(temp!=head) {
            sum += temp->data;
            temp = temp->next;
        }
        return sum;
    }

    void greaterThanAverage() {
        Node *temp = head->next;
        T sum = accumulate();
        while(temp!=head) {
            if(temp->data > (sum/head->data))
                cout << temp->data << ' ';
            temp = temp->next;
        }
        cout << '\n';
    }

    //Swapping Nodes of Circular Doubly List By Swapping Pointers not Data
    void swap(int data1, int data2){
        Stack<class Node*> stack;
        Node *temp1 = head->next;
        while(temp1->data!=data1) {
            temp1 = temp1->next;
        }
        stack.push(temp1->next);
        stack.push(temp1->previous);
        Node *temp2 = head;
        while(temp2->data!=data2) {
            temp2 = temp2->next;
        }
        //Checking if elements to swap are next t0 each other
        if(temp1->next->data == data2) {
            temp1->next = temp2->next;
            temp1->previous = temp2;
            temp1->next->previous = temp1;
            //pushing next and previous references in tack
            Node *prev = stack.pop();
            Node *nex = stack.pop();
            temp2->next = temp1;
            temp2->previous = prev;
            temp2->previous->next = temp2;
        } else {
            temp1->next = temp2->next;
            temp1->previous = temp2->previous;
            temp2->previous->next = temp1;
            temp2->next->previous = temp1;
            //pushing next and previous references in tack
            Node *prev = stack.pop();
            Node *nex = stack.pop();
            temp2->previous = prev;
            temp2->next = nex;
            temp2->previous->next = temp2;
            temp2->next->previous = temp2;
        }
    }

    friend ostream& operator << (ostream& out, circularDoublyList<T>& list) {
        if(list.isEmpty()) {
            out << "List is Empty\n";
        } else {
            Node *temp = list.head->next;
            while(temp!=list.head) {
                out << temp->data << " ";
                temp = temp->next;
            }
            out << '\n';
        }
        return out;
    }
};
int main(){
    circularDoublyList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);
    list1.push_back(5);
    cout << list1;
    list1.push_front(10);
    cout << list1;
    list1.push_front(100);
    cout << list1;
    list1.swap(1,2);
    cout << list1;
    return 0;
}