#include <iostream>
using namespace std;

template <class T>
class SinglyLinkedList {
public:
    class Node {
    public:
        friend class SinglyLinkedList<T>;
        Node* next;
        T data;
        Node():next(nullptr){}
        Node(T data, Node *next):data(data), next(next){}
    };
    Node* head;
    int size;
    SinglyLinkedList():head(nullptr),size(0){}

    //Utility Functions
    int getSize() {
        return size;
    }
    bool isEmpty() {
        if(head==nullptr) {
            return true;
        }
        return false;
    }
    T peak_first() {
        if(isEmpty()) {
            throw runtime_error("Empty List");
        } else {
            return head->data;
        }
    }

    //Appending Linked List
    void append(const T& data) {
        if(head==nullptr) {
            head = new Node(data, nullptr);
            cout << "Node Appended.\n\n";
        } else {
            Node *ptr = head;
            while(ptr->next!=nullptr) {
                ptr = ptr->next;
            }
            ptr->next = new Node(data, nullptr);
            cout << "Node Appended.\n\n";
        }
            size++;
    }

    // Pre-Appending Linked List
    void preAppend(const T& data) {
        if(head==nullptr) {
            head = new Node(data, nullptr);
            cout << "Node Pre-Appended.\n\n";
        } else {
            head = new Node(data, head);
            cout << "Node Pre-Appended.\n\n";
        }
            size++;
    }

    //Insert at certain position
    void insert(const T& data, int position) {
        int i=1;
        Node* ptr = head;
        while(i<position) {
            ptr = ptr->next;
            i++;
        }
        ptr->next = new Node(data,ptr->next);
    }

    //Poping elements
    void pop_back() {
        if(isEmpty()) {
            cout << "List is already empty\n";
        } else {
            int s = getSize(), i=0;
            Node* ptr = head;
            Node* ptr1 = head;
            while(ptr->next!=nullptr) {
                ptr = ptr->next;
            }
            delete ptr;
            while(i<(s-1)) {
                ptr1 = ptr1->next;
                i++;
            }
            ptr1->next = nullptr;
        }
        size--;
        // n1--->n2--->n3--->null
    }

    void pop_front() {
        if(isEmpty()) {
            cout << "List is already empty\n";
        } else {
            Node* ptr = head;
            head = head->next;
            delete ptr;
        }
        size--;
    }

    //erase elements from list

    void erase(int position) {
        Node* ptr = head;
        Node* ptr1 = head;
        int i=1, j=1, s = getSize();
        while(i<position) {
            ptr = ptr->next;
            i++;
        }
        while(j<(position-1)) {
            ptr1 = ptr1->next;
            j++;
        }
        ptr1->next = ptr->next;
        delete ptr;
        size--;
    }

    //ostream operator for SinglyList
    friend ostream& operator << (ostream& out, SinglyLinkedList<T>& list) {
        Node *temp = list.head;
        if(list.isEmpty()) {
            cout << "List is Empty.\n";
        } else {
            while(temp!=nullptr) {
            out << temp->data;
                if(temp->next!=nullptr)
                    cout << "---->";
            temp = temp->next;
            }
            out << '\n' << '\n';
        }
        return out;
    }
};
int main() {
    SinglyLinkedList<float> list;
    list.append(10.69);
    cout << list;
    list.append(20);
    cout << list;
    list.preAppend(69.69);
    cout << list;
    list.preAppend(6969.69);
    cout << list;
    list.insert(45.88, 2);
    cout << list;
    SinglyLinkedList<string> list1;
    list1.append("Ahmad Butt");
    list1.append("Ali Butt");
    cout << list1;
    list1.insert("Don",1);
    cout << list1;
    list1.preAppend("Sheldon Cooper");
    cout << list1;
    list1.pop_back();
    cout << list1;
    list1.pop_front();
    cout << list1;
    list.erase(2);
    cout << list;
    return 0;
}