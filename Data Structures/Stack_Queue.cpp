#include <iostream>
#include <string.h>
using namespace std;
template <class T>
class Stack_Queue{
    class Node{
        T data;
        Node* next;
        public:
        Node(T data):data(data),next(nullptr){}
        Node(T data, Node* next):data(data),next(next){}
        friend class Stack_Queue<T>;
    };
    Node *head, *tail;
    bool _isEmpty() {
        if(head->next == nullptr)
            return true;
        return false;
    }
public:
    Stack_Queue(){
        head = new Node(0);
        tail =  nullptr;
    }
    void push(T data) {
        head->next = new Node(data,head->next);
        head->data+=1;
    }
    T seeTop() {
        if(_isEmpty()) {
            throw "Empty Stack\n";
        } else {
            return head->next->data;
        }
    }
    T pop() {
        if(_isEmpty()) {
            throw "Empty Stack\n";
        } else {
            Node *temp = head->next;
            T res = temp->data;
            //h --> 1 2 3 4
            head->next = temp->next;
            delete temp;
            head->data-=1;
            return res;
        }
    }
    void enqueue(T data) {
        if(_isEmpty()) {
            head->next = new Node(data);
            tail = head->next;
        } else {
            tail->next = new Node(data);
            tail = tail->next;
        }
        head->data+=1;
    }
    T dequeue() {
        if(_isEmpty()) {
            throw "Empty Stack\n";
        } else {
            Node *temp = head->next;
            T res = temp->data;
            //h --> 1 2 3 4
            head->next = temp->next;
            delete temp;
            head->data-=1;
            return res;
        }
    }
};
// int main() {
//     Stack_Queue<float> stack;
//     stack.push(8.908);
//     stack.push(69.69);
//     stack.push(9.6);
//     try{
//         cout << stack.pop() << '\n';
//         cout << stack.pop() << '\n';
//         cout << stack.pop() << '\n';
//         cout << stack.pop() << '\n';
//     } catch(const char* str) {
//         cout << str;
//     }
//     Stack_Queue<int> queue;
//     queue.enqueue(10987);
//     queue.enqueue(17854);
//     queue.enqueue(10101);
//     cout << queue.pop() << '\n';
//     cout << queue.pop() << '\n';
//     cout << queue.pop() << '\n';
//     return 0;
// }