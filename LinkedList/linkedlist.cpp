#include<iostream>

class Node
{
public:
    int value;
    Node* next;
    Node* prev;
public:
    Node(const int& val) {  value = val; }
    Node( const int& val, Node* pr) { value = val; prev = pr; }
    Node() = default;
    ~Node() = default;
    

};

class List : public Node
{
private:
    Node *begin;
    Node *end;
public:
    List()
    {
        begin = nullptr;
        end = nullptr;
    }
    ~List() {}
    void afisare()
    {
        Node* nextnode = begin;
        while( nextnode != nullptr )
        {
            std::cout << nextnode->value << " ";
            nextnode = nextnode->next;
        }
        delete nextnode;
    }
    void pushback(const int& val)
    {
        Node *nnode = new Node(val);
        nnode->next = nullptr;
        if ( begin == nullptr && end == nullptr)
        {
            begin = nnode;
            end = nnode;
        }
        else
        {   
            nnode->prev = end;
            end->next = nnode;
            end = nnode;
        }
    }
    void pop()
    {   
        if ( end != nullptr )
            {
            Node *tmp = end;
            end  = end->prev;
            delete tmp->next;
            if ( tmp->prev )
                tmp->prev->next = nullptr;
            else begin = nullptr;
            delete tmp;

            }
    }

};

int main()
{
    List Lista;
    Lista.pushback(1);
    Lista.afisare();
    std::cout<<std::endl;
    Lista.pushback(2);
    Lista.afisare();
    std::cout<<std::endl;
    Lista.pushback(3);
    Lista.afisare();
    std::cout<<std::endl;
    Lista.pop();
    Lista.afisare();
    std::cout<<std::endl;
    Lista.pop();
    Lista.afisare();
    std::cout<<std::endl;
    Lista.pop();
}