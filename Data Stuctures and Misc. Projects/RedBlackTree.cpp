/**********************************************
 * Description:
 * This file implements a red-black tree Node class,
 * a RedBlackTree class, and a Binary Search Tree class
 * A good amount of code was given to me in a handout and the
 * rest was completed for the class
 **********************************************/

#include <iostream>
#include <queue>
using namespace std;
#include <vector>

using namespace std;

// Node class for Red-Black Tree
class Node {
public:
    int val;
    bool isBlack; // False for a red node
    Node *left, *right, *parent;

    Node(int val)
            : val(val), isBlack(false), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Red black tree
class RedBlackTree {
public:
    Node *root;
    RedBlackTree() : root(nullptr) {}

    void insert(int val) {
        Node *newNode = new Node(val);
        root = insertNode(root, newNode);
        balanceAfterInsert(newNode);
    }

    void levelOrderTraversal() {
        if (root == nullptr) {
            return;
        }
        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node *node = q.front();
                q.pop();
                cout << "(" << node->val
                     << (node->isBlack ? "|B) " : "|R) "); // Ternary operator, feel free to
                // rewrite as if/else
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            cout << endl;
        }
    }

private:
    Node *insertNode(Node *current, Node *newNode) {
        if (current == nullptr) {
            return newNode;
        }
        if (newNode->val < current->val) {
            current->left =
                    insertNode(current->left, newNode); // update current's left!
            current->left->parent = current;
        } else {
            current->right = insertNode(current->right, newNode);
            current->right->parent = current;
        }
        return current;
    }
    // Pseudocode can be found on page 266 of the CLRS handout
    void leftRotate(Node *node) {
        Node *temp = node->right;
        node->right = temp->left;
        if (temp->left != nullptr) {
            temp->left->parent = node;
        }
        temp->parent = node->parent;
        if (node->parent == nullptr) {
            root = temp;
        } else if (node == node->parent->left) {
            node->parent->left = temp;
        } else {
            node->parent->right = temp;
        }
        temp->left = node;
        node->parent = temp;
    }
    void rightRotate(Node *node) {
        Node *temp = node-> left;
        node->left = temp-> right;
        if(temp->right != nullptr){
            temp->right->parent = node;
        }
        temp->parent = node->parent;
        if (node->parent == nullptr) {
            root = temp;
        } else if (node == node->parent->right) {
            node->parent->right = temp;
        } else {
            node->parent->left = temp;
        }
        temp->right = node;
        node->parent = temp;
    }
    void balanceAfterInsert(Node *node) {
        while (node != root && !node->parent->isBlack) { // pg 268 pseudocode line 3
            if (node->parent == node->parent->parent->left) {
                Node *uncle = node->parent->parent->right;
                if (uncle != nullptr && !uncle->isBlack) {

                    // Case 1 Uncle is red
                    node->parent->isBlack = false;
                    uncle->isBlack = true;
                    node->parent->parent->isBlack = false;
                    node = node->parent->parent;

                    // Case 1 end
                } else {
                    if (node == node->parent->right) {
                        // Begin case 2
                        node = node->parent;
                        leftRotate(node);
                        // End case 2
                    }
                    // Case 3
                    node->parent->isBlack = true;          // line 14 of pseudocode pg 268
                    node->parent->parent->isBlack = false; // line 15
                    rightRotate(node->parent->parent);
                    // End of case 3
                }
            } else { // This section of the code maps to line 17 of the pseudocode
                // (with everything flipped)
                Node *uncle = node->parent->parent->left;
                // We are restarting line 6 through 16, except flipping the logic
                if (uncle != nullptr && !uncle->isBlack) {
                    // Mirror case 1, uncle is red
                    node->parent->isBlack = true;
                    uncle->isBlack = true;
                    node->parent->parent->isBlack = false;
                    node = node->parent->parent;
                    // End mirror case 1
                } else {
                    if (node == node->parent->left) {
                        // Beginning mirror case 2
                        node = node->parent;
                        rightRotate(node);
                        // End of mirror case 2
                    }
                    // Beginning mirror case 3
                    node->parent->isBlack = true;
                    node->parent->parent->isBlack = false;
                    leftRotate(node->parent->parent);
                    // End of mirror case 3
                }
            }
        }
        root->isBlack = true; // Line 18 of pseudocode
        // (after you finish redoing line 5-16 but reversed)
    }
};


template<typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

template<typename T>
class BinarySearchTree {
    TreeNode<T>* root;

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(T val) {
        root = insertNode(root, val);
    }

    bool find(T val) {
        return findNode(root, val) != nullptr;
    }

    void levelOrderTraversal() {
        if (root == nullptr) {
            return;
        }
        queue<TreeNode<T>*> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode<T>* node = q.front();
                q.pop();
                cout << node->data << " ";
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            cout << endl;
        }
    }

private:
    TreeNode<T>* insertNode(TreeNode<T>* node, T val) {
        if (node == nullptr) {
            return new TreeNode<T>(val);
        }
        if (val < node->data) {
            node->left = insertNode(node->left, val);
        } else {
            node->right = insertNode(node->right, val);
        }
        return node;
    }

    TreeNode<T>* findNode(TreeNode<T>* node, T val) {
        if (node == nullptr || node->data == val) {
            return node;
        }

        if (val < node->data) {
            return findNode(node->left, val);
        } else {
            return findNode(node->right, val);
        }
    }
};


int main() {
    BinarySearchTree<int> bst;
    RedBlackTree rbt;
    for(int i = 20; i > 0; i--){
        bst.insert(i);
        rbt.insert(i);
    }
    cout << "Printing out level order traversal of binary search tree: " << endl;
    // Notice this tree does not balance, and the values inserted are strictly increasing
    // this means our tree is essentially a "bent" linked list
    bst.levelOrderTraversal();
    cout << "Printing out level order traversal of red black tree: " << endl;
    // Notice this tree does indeed balance!  the height of the tree will be log2(number of nodes)
    rbt.levelOrderTraversal();
    return 0;
}

