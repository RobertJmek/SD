#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream f("abce.in");
ofstream g("abce.out");


class Node
{
public:
    int height = 0;
    int value;
    int counter = 0;
    Node *parent = nullptr;
    Node *right_son = nullptr;
    Node *left_son = nullptr;

    Node() = default;
    Node(const int &value)
    {
        this->value = value;
        this->counter++;
    }
    Node(const Node *nodee)
    {
        if (nodee)
        {
            this->counter = nodee->counter;
            this->height = nodee->height;
            this->left_son = nodee->left_son;
            this->parent = nodee->parent;
            this->right_son = nodee->right_son;
            this->value = nodee->value;
        }
    }
    ~Node() = default;
};

class AVL
{
public:
    Node *root_ = nullptr;
    AVL() = default;
    AVL(Node *node) { this->root_ = node; }
    ~AVL() = default;

    int heightCalc(Node* node)
    {
        if ( node->left_son && node->right_son )
            return std::max( node->left_son->height, node->right_son->height ) + 1;
        else if ( node->left_son )
            return node->left_son->height + 1;
        else if ( node->right_son )
            return  node->right_son->height + 1;
        else
            return 0;
    }

    void rebalance(Node *node)
    {
        if (node == nullptr)
            return;
        if (Balance(node) > 1)
        {
            if ( Balance(node->left_son) > 0 )
                RR(node);
            else
                LR(node);
        }
        else if (Balance(node) < -1)
        {
            if (Balance(node->right_son) < 0)
                LL(node);
            else
                RL(node);
        }
        else
            rebalance(node->parent);
    }


void RR(Node* node)
{
    /// Rotatie dreapta
    Node* aux = new Node(node->left_son->value);
    if ( node == root_ )
        root_ = aux;
    else if ( node == node->parent->left_son)
        {
            node->parent->left_son = aux;
            aux->parent = node->parent;
        }
    else if ( node == node->parent->right_son)
        {
            node->parent->right_son = aux;
            aux->parent = node->parent;
        }
    aux->right_son = node;
    if (node->left_son->left_son)
    {
        aux->left_son = node->left_son->left_son;
        node->left_son->left_son->parent = aux;
    }
    node->parent = aux;
    if ( node->left_son->right_son )
        {
        node->left_son->right_son->parent = node;
        node->left_son = node->left_son->right_son;
        }
    else
    {
    node->left_son = nullptr;
    delete node->left_son;
    }
    if (aux->left_son)
        aux->left_son->height = heightCalc(aux->left_son);
    aux->right_son->height = heightCalc(aux->right_son);
    aux->height = heightCalc(aux);
    
}


void RL(Node* node)
{
    /// Rotatie dreapta-stanga
    RR(node->right_son);
    LL(node);
}

void LR(Node* node)
{
    /// Rotatie stanga-dreapta
    LL(node->left_son);
    RR(node);
}

void LL(Node* node)
{
    /// Rotatie stanga 
    Node* aux = new Node(node->right_son->value);
    if ( node == root_ )
        root_ = aux;
    else if ( node == node->parent->left_son)
        {
            node->parent->left_son = aux;
        }
    else if ( node == node->parent->right_son)
        {
            node->parent->right_son = aux;
        }
    aux->left_son = node;
    if ( node->right_son->right_son ) 
        aux->right_son = node->right_son->right_son;
    aux->parent = node->parent;
    node->parent = aux;
    if ( node->right_son->right_son )
    {
        node->right_son->right_son->parent = aux;
        aux->right_son = node->right_son->right_son;
    }
    if ( node->right_son->left_son )
    {
        node->right_son->left_son->parent = node;
        node->right_son = node->right_son->left_son;
    }
    else 
    {
        node->right_son = nullptr;
        delete node->right_son;
    }
    aux->left_son->height = heightCalc(aux->left_son);
    if ( aux->right_son)
        aux->right_son->height = heightCalc(aux->right_son);
    aux->height = heightCalc(aux);
}

    bool Balanced(Node* node)
    {
        if ( Balance(node) <= 1 && Balance(node) >= -1 )
            return true;
        else
            return false;
    }

    void Hplus(Node* node)
    {
        while ( node && node->parent )
        {
            if ( node->parent->height <= node->height+1 )
                node->parent->height = node->height+1;
                node = node->parent;
        }
    }

    void Hminus(Node* node)
    {
        while ( node->parent )
        {
        node->height= heightCalc(node);
        node = node->parent;
        }
        node->height= heightCalc(node);
    }

    int Balance(Node *node)
    {
        int leftH = 0;
        int rightH = 0;
        if (node->left_son)
            leftH = node->left_son->height;
        if (node->right_son)
            rightH = node->right_son->height;
        return (leftH - rightH);
    }

    bool findV(int &value)
    {
        Node *current = root_;
        while (current != nullptr)
        {
            if (value > current->value)
                current = current->right_son;
            else if (value < current->value)
            {
                current = current->left_son;
            }
            else
                return true;
        }
        return false;
    }

    Node *findN(Node *root, int &value)
    {
        Node *current = root;
        while (current != nullptr)
        {
            if (value > current->value)
                current = current->right_son;
            else if (value < current->value)
            {
                current = current->left_son;
            }
            else
                return current;
        }
        return nullptr;
    }

    void insert_(Node *current, int &newval)
    {
        if (root_ == nullptr)
        {
            if (current)
                root_ = new Node(current);
            else
            {
                current = new Node(newval);
                root_ = current;
                root_->counter--;
            }
        }
        if (newval > current->value)
            if (current->right_son)
            {
                insert_(current->right_son, newval);
            }
            else
            {
                current->right_son = new Node(newval);
                current->right_son->parent = current;
            }
        else if (newval < current->value)
            if (current->left_son)
            {
                insert_(current->left_son, newval);
            }
            else
            {
                current->left_son = new Node(newval);
                current->left_son->parent = current;
            }
        else if (newval == current->value)
            current->counter++;
        Node* nodadaugat = findN(root_,newval);
        Hminus(nodadaugat);
        rebalance(nodadaugat);
    }

    void printAVL(Node *root)
    {
        if (root != nullptr)
        {
            if (root->left_son) printAVL(root->left_son);
            {
            
                cout << "Nodul are valoarea: " << root->value << endl;
                if (root->parent == nullptr)
                    cout << "Este radacina" << endl;
                else
                    cout << "Parinte:" << root->parent->value << endl;
                if (root->right_son)
                    cout << "Fiu drept " << root->right_son->value << endl;
                if (root->left_son)
                    cout << "Fiu stang " << root->left_son->value << endl;
                cout << "Counter: " << root->counter << endl;
                cout << "Height: " << root->height << endl;
            }
            if (root->right_son) printAVL(root->right_son);
        }
    }

    Node *max(Node *current)
    {
        while (current->right_son)
        {
            current = current->right_son;
        }
        return current;
    }

    Node *min(Node *current)
    {
        while (current->left_son)
            current = current->left_son;
        return current;
    }

    void delVal(int &value)
    {
        Node *delN = findN(root_, value);
        if (delN->counter > 1)
            delN->counter--;
        else
        {
            if ( delN->left_son == nullptr && delN->right_son == nullptr )
            {
                Node* temp = delN->parent;
                if ( delN->value > delN->parent->value )
                    delN->parent->right_son = nullptr;
                else { delN->parent->left_son = nullptr; }
                delN = nullptr;
                delete delN;
                Hminus(temp);
                rebalance(temp);

            }
            else if ( delN->left_son && !delN->right_son ) 
            {
                Node* temp = delN->parent;
                delN->left_son->parent = delN->parent;
                 if ( delN == delN->parent->left_son )
                    delN->parent->left_son = delN->left_son;
                else
                {
                    delN->parent->right_son = delN->left_son;
                }
                delN = nullptr;
                delete delN;
                Hminus(temp);
                rebalance(temp);
            }
            else if (!delN->left_son && delN->right_son)
            {   
                Node* temp = delN->parent;
                delN->right_son->parent = delN->parent;
                if (delN == delN->parent->left_son)
                    delN->parent->left_son = delN->right_son;
                else
                {
                    delN->parent->right_son = delN->right_son;
                }
                delN = nullptr;
                delete delN;
                Hminus(temp);
                rebalance(temp);
            }
            else
            {
                Node* swap = succesor(delN->right_son,nullptr,delN->value);
                int val = swap->value;
                delVal(swap->value);
                delN->value = val;
           }
        }
    }

    Node* predecesor(Node* root, Node* prec, int& value)
    {
        if ( root == nullptr ) return prec;
        if ( value < root->value )
        {
            return predecesor(root->left_son,prec,value);
        }
        else
        {
            prec = root;
            return predecesor(root->right_son,prec,value);
        }
    return prec;
    }

    Node* succesor(Node* root, Node* suc, int& value)
    {
        if (root == nullptr ) return suc;

        if ( value > root->value )
        {   
            return succesor(root->right_son,suc,value);
        }
        else
        {
            suc = root;
            return succesor(root->left_son,suc,value);
        }

    }

    void Interval(int&  x, int& y, Node* root)
    {
        if (root != nullptr)
        {
            Interval(x,y,root->left_son);
            {
                if ( root->value >= x && root->value <= y)
                {
                    g << root->value << " ";
                }
            }
            Interval(x,y,root->right_son);
        }
    }

};

int main()
    {
        AVL avl;
        int nroperatii;
        f >> nroperatii;
        for ( int i=0; i < nroperatii; i++ )
        {
            int operatie;
            f >> operatie;
            if ( operatie == 1 )
            {
                int newval;
                f >> newval;
                avl.insert_(avl.root_,newval);
            }
            if ( operatie == 2 )
            {
                int todel;
                f >> todel;
                avl.delVal(todel);
            }
            if ( operatie == 3 )
            {
                int tofind;
                f >> tofind;
                g << avl.findV(tofind) << endl;
            }
            if ( operatie == 4 )
            {
                int X;
                f >> X;
                if ( avl.findV(X) ) 
                    g << X << endl;
                else  
                    g << avl.predecesor(avl.root_,nullptr,X)->value << endl;
            }
            if  ( operatie == 5)
            {
                int X;
                f >> X;
                if ( avl.findV(X) )
                    g << X << endl;
                else
                    g << avl.succesor(avl.root_,nullptr,X)->value << endl;
            }
            if ( operatie == 6 )
            {
                int x,y;
                f >> x >> y;
                avl.Interval(x,y,avl.root_);
                g << endl;
            }
        }
    avl.printAVL(avl.root_);

    }
