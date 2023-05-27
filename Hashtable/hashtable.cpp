#include <iostream>
#include <vector>
#include <fstream>
#include <list>

using namespace std;

ifstream fin("input.txt");

int n = 666013;
class HashTable {
    private:
        vector <int>Vhash;
        int hash(int& key) { return key % n; }
        public:
        HashTable(int& n) : Vhash(n) {}
        HashTable();
        void insert(int& key)
        {
            int index = hash(key);
            while (Vhash[index] != 0  && Vhash[index] != -1)
            {
            index++;
            }
            Vhash[index] = key;
        }
        void remove(int key)
        {
            int index = hash(key);
            while ( Vhash[index+1] == key && Vhash[index] != 0 && Vhash[index] != -1)
            {
                index++;
            }
            Vhash[index] = -1;
        }
        bool search(int key)
        {
            int index = hash(key);
            while (Vhash[index] != key)
            {
                index++;
            }
            if (Vhash[index] == key)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        void print()
        {
            for (int i = 0; i < 30; i++)
            {
                cout << Vhash[i] << " ";
            }
            cout << endl;
        }

};

int main()
{
    HashTable H(n);
    int key;
    for (int i = 0; i < 10; i++)
    {
        fin >> key;
        H.insert(key);
    }
    H.print();
    H.remove(2);
    H.print();
    cout << H.search(2) << endl;
    return 0;
}
