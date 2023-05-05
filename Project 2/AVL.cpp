#include <iostream>
using namespace std;

class Node
{
public:
    int height = 0;
    int value;
    int counter = 0;
    Node* parent = nullptr;
    Node* right_son = nullptr;
    Node* left_son = nullptr;


    Node() = default;
    Node( const int& value ) { this->value = value; this->counter++; }
    ~Node() = default;

};

class AVL
{
public:
    Node* root_ = nullptr;
    AVL() = default;
    AVL(Node* node ) { this->root_ = node; }
    ~AVL() = default;
    int Balance(Node* node)
    {
        int leftH = 0;
        int rightH = 0;
        if ( node->left_son )
            leftH = node->left_son->height;
        if ( node->right_son )
            rightH = node->right_son->height;
        return leftH-rightH;
    }

    bool find(int value)
    {
        Node* current = root_;
        while ( current != nullptr ) 
        {
            if ( value > current->value )
                current = current->right_son;
            else if ( value < current->value) {
                current = current->left_son;
            }
                else return true;
        }
        return false;  
    }
    void insert_(Node* current, int& newval)
        {   
            bool OK = false;
            if ( newval > current->value )
                if ( current->right_son )
                {
                    insert_(current->right_son, newval );
                    if ( OK )
                        current->height++;
                }
                else {
                    if ( !(current->left_son) )
                        OK = true;
                    current->right_son = new Node(newval);
                    current->right_son->parent = current;
                    }
            else if( newval < current->value )
                if ( current->left_son )
                {
                    insert_(current->left_son, newval);
                    if ( OK )
                        current->height++;
                }
                else {
                    if ( !(current->right_son) )
                        OK = true;
                    current->left_son = new Node(newval);
                    current->left_son->parent = current;
                     }
            else if ( newval == current->value )
                current->counter++;
        }

};

int main()
{

}