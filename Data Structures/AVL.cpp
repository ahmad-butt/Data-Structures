#include <iostream>
using namespace std;

template <class T>
class AVL {
    class Node {
        T data;
        Node *left, *right;
        int height;
    public:
        Node(T data):data(data),left(nullptr), right(nullptr){}
        Node(T data, Node *left, Node *right, int height):data(data),left(nullptr), right(nullptr){}
        friend class AVL<T>;
    };

    int getHeight(Node *root) {
        if(root==nullptr)
            return 0;
        return root->height;
    }

    void updateHeight(Node *root) {
        if(root==nullptr)
            return;
        root->height = 1+std::max(getHeight(root->left),getHeight(root->right));
    }

    int getBalance(Node *root) {
        if(root==nullptr)
            return 0;
        return getHeight(root->left) - getHeight(root->right);
    }

    Node* rotateRight(Node *root) {
        Node * leftOfRoot = root->left;
        Node * rightOfLeftOfRoot = leftOfRoot->right;

        leftOfRoot->right = root;
        root->left = rightOfLeftOfRoot;

        updateHeight(root);
        updateHeight(leftOfRoot);

        return leftOfRoot;
    }

    Node* rotateLeft(Node *root) {
        Node * rightOfRoot = root->right;
        Node * leftOfRightOfRoot = rightOfRoot->left;

        rightOfRoot->left = root;
        root->right = leftOfRightOfRoot;

        updateHeight(root);
        updateHeight(rightOfRoot);

        return rightOfRoot;
    }

    Node* rightMin(Node *root) {
        if(root->left==nullptr)
            return root;
        return rightMin(root->left);
    }

    Node* balancing(Node * root) {
        int balanceFactor = getBalance(root);
        if(balanceFactor > 1 and getBalance(root->left) >= 0)
            return rotateRight(root);
        if(balanceFactor < -1 and getBalance(root->right) <= 0)
            return rotateLeft(root);
        if(balanceFactor > 1 and getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if(balanceFactor < -1 and getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }
    
public:
    Node *root;
    AVL():root(nullptr){}

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

    Node* insert(Node *root, T data) {
        if(root==nullptr) {
            root = new Node(data);
        } else if(data < root->data) {
            root->left = insert(root->left,data);
        } else {
            root->right = insert(root->right,data);
        }
        updateHeight(root);
        return balancing(root);    
    }
    void insert(T data) {
        root = insert(root,data);
    }

    Node *deleteNode(Node *root, T data) {
        if(root==nullptr) {
            return balancing(root);
        } else if(data > root->data) {
            root->right = deleteNode(root->right, data);
        } else if(data < root->data) {
            root->left = deleteNode(root->left, data);
        } else {
            //No child case
            if(root->left==nullptr and root->right==nullptr) {
                delete root;
                root = nullptr;
            } else if (root->left==nullptr and root->right!=nullptr) {
                Node *temp = root;
                root = root->right;
                delete temp;
                temp = nullptr;
            } else if(root->left!=nullptr and root->right==nullptr) {
                Node *temp = root;
                root = root->left;
                delete temp;
                temp = nullptr;
            } else {
                Node* rightMinimum = rightMin(root->right);
                root->data = rightMinimum->data;
                root->right = deleteNode(root->right, rightMinimum->data);
            }
        }
        updateHeight(root);
        return balancing(root);
    }

    void deleteNode(T data) {
        root = balancing(deleteNode(root, data));
    }
    
    void inOrder(Node *root) {
        if(root==nullptr)
            return;
        inOrder(root->left);
        cout << root->data << ' ';
        inOrder(root->right);
    }
    void inOrder() {
        inOrder(root);
        cout << '\n';
    }
    void preOrder(Node *root) {
        if(root==nullptr)
            return;
        cout << root->data << ' ';
        preOrder(root->left);
        preOrder(root->right);
    }
    void preOrder() {
        preOrder(root);
        cout << '\n';
    }
};
int main() {
    AVL<int> bst;
    bst.insert(141);
    bst.insert(567);
    bst.insert(134);
    bst.insert(500);
    bst.insert(369);
    bst.preOrder();
    bst.inOrder();
	// balanced_tree.deleteNode(16);
	// balanced_tree.inOrder();
}