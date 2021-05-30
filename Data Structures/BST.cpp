#include <iostream>
#include <queue>
using namespace std;
template <class T>
class BST{
    class Node{
    public:
        T data;
        Node *left, *right;
        friend class BST<T>;
        Node(T data):data(data), left(nullptr), right(nullptr){}
        Node(T data, Node* left, Node* right):data(data),left(left),right(right){}
    };
    Node *root;
public:
    BST():root(nullptr){}
    Node* insert(Node *root, T data) {
        if(root==nullptr) {
            root = new Node(data,nullptr,nullptr);
        } else if(data <= root->data) {
            root->left = insert(root->left,data);
        } else {
            root->right = insert(root->right,data);
        }
        return root;
    }
    void insert(T data) {
        root = insert(root,data);
    }
    bool search(Node *root, T data) {
        if(root==nullptr) {
            return false;
        } else if(root->data==data) {
            return true;
        } else if(data <= root->data) {
            return search(root->left,data);
        } else {
            return search(root->right,data);
        }
    }
    bool search(T data) {
        return search(root,data);
    }
    int findMax(Node *root) {
        if(root->right==nullptr)
            return root->data;
        return findMax(root->right);
    }
    int findMax() {
        return findMax(root);
    }
    int findMin(Node *root) {
        if(root->left==nullptr)
            return root->data;
        return findMin(root->left);
    }
    int findMin() {
        return findMin(root);
    }
    int findHeight(Node *root) {
        if(root==nullptr)
            return -1;
        int leftHeight = findHeight(root->left);
        int rightHeight = findHeight(root->right);
        return std::max(leftHeight,rightHeight)+1;
    }
    int findHeight() {
        return findHeight(root);
    }
    //Breadth First Search
    void breadthFirst(Node *root) {
        if(root==nullptr)
            return;
        queue<Node *> q;
        q.push(root);
        while(!q.empty()) {
            Node *currentNode = q.front();
            cout << currentNode->data << " ";
            if(currentNode->left!=nullptr)
                q.push(currentNode->left);
            if(currentNode->right!=nullptr)
                q.push(currentNode->right);
            q.pop();
        }
        cout << '\n';
    }
    void breadthFirst() {
        breadthFirst(root);
    }
    //Depth First Search
    void preorder(Node *root) {
        if(root==nullptr)
            return;
        cout << root->data << ' ';
        preorder(root->left);
        preorder(root->right);
    }
    void preorder() {
        preorder(root);
        cout << '\n';
    }
    void inorder(Node *root) {
        if(root==nullptr)
            return;
        inorder(root->left);
        cout << root->data << ' ';
        inorder(root->right);
    }
    void inorder() {
        inorder(root);
        cout << '\n';
    }
    void postorder(Node *root) {
        if(root==nullptr)
            return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << ' ';
    }
    void postorder() {
        postorder(root);
        cout << '\n';
    }
    Node* _rightMin(Node *root) {
        while(root->left != NULL) 
            root = root->left;
	    return root;
    }
    Node* deleteNode(Node *root, T data) {
        if(root==nullptr)
            return root;    
        else if(data < root->data)
            root->left = deleteNode(root->left,data);
        else if(data > root->data)
            root->right = deleteNode(root->right,data);
        else {
            if(root->left==nullptr and root->right==nullptr) {
                delete root;
                root = nullptr;
                return root;
            } else if(root->right==nullptr) {
                Node *tempNode = root;
                root = root->left;
                delete tempNode;
                return root;
            } else if(root->left==nullptr) {
                Node *tempNode = root;
                root = root->right;
                delete tempNode;
                return root;
            } else {
                Node *tempNode = _rightMin(root->right);
                root->data = tempNode->data;
                root->right = deleteNode(root->right, tempNode->data);
            }
        }
    }
    void deleteNode(T data) {
        root = deleteNode(root, data);
    }
};
int main() {
    BST<int> bst;
    bst.insert(868);
    bst.insert(458);
    bst.insert(608);
    bst.insert(519);
    bst.insert(727);
    bst.preorder();
    bst.inorder();
    return 0;
}