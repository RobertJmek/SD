#include <iostream>

using namespace std;

class Node
{
public:
    float value;
    Node *right_son = nullptr;
    Node *left_son = nullptr;
    ~Node() = default;
    Node() = default;
    Node(const float &value) { this->value = value; }
};

class BST
{
public:
    Node *root;
    void insert(float value) {
        if(root) {
            _insert(root, value);
        } else {
            root = new Node(value);
        }
    }

private:
    void _insert(Node* node, float value) {
        if(value > node->value) {
            if(node->right_son != nullptr) {
                this->_insert(node->right_son, value);
            } else {
                node->right_son = new Node(value);
            }
        } else if ( value  < node->value ){
            if(node->left_son != nullptr) {
                this->_insert(node->left_son, value);
            } else {
                node->left_son = new Node(value);
            }
        }
    }
};