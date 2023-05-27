#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("stramosi.in");
ofstream fout("stramosi.out");

class Node
{
public:
    int value;
    Node *parent = nullptr;
    Node *child = nullptr;

    Node() = default;
    Node(const int &value)
    {
        this->value = value;
    }
    Node(const Node *nodee)
    {
        if (nodee)
        {
            this->parent = nodee->parent;
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

    void newInsert(int &copil, int &parinte)
    {
        
    }

};

int main()
{
    int n, m;
    
    fin >> n >> m;

    vector<int> parinti(n+1);

    for (int i = 1; i < n+1; ++i)
    {
        fin >> parinti[i];
    }

    for (int i = 0; i < m; ++i)
    {
        int nod, numarordine, contor = 0, numarordineINITIAL;
        fin >> nod >> numarordine;
        nod = parinti[nod];
        numarordineINITIAL = numarordine;
        --numarordine;
        contor++;
        while ( numarordine > 0 && nod != 0)
        {
            nod = parinti[nod];
            --numarordine;
            contor++;
        }
        if ( contor == numarordineINITIAL )
        {
            fout << nod << '\n';
        }
        else
        {
            fout << 0 << '\n';
        }
    }

}