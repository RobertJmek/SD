#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

ifstream fin("heapuri.in");
ofstream fout("heapuri.out");

class MinHeap
{
private:
    vector<int> heap;
    int heap_size;

public:
    MinHeap()
    {
        heap_size = 0;
    }

    void minHeapify(int i);

    int parent(int i) { return (i - 1) / 2; }

    int left(int i) { return (2 * i + 1); }

    int right(int i) { return (2 * i + 2); }

    int extractMin();

    void decreaseKey(int i, int new_val);

    int getMin() { return heap[0]; }

    void deleteKey(int i);

    void insertKey(int k);
};

void MinHeap::minHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && heap[l] < heap[i])
        smallest = l;
    if (r < heap_size && heap[r] < heap[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(heap[i], heap[smallest]);
        minHeapify(smallest);
    }
}

int MinHeap::extractMin()
{
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1)
    {
        heap_size--;
        return heap[0];
    }

    int root = heap[0];
    heap[0] = heap[heap_size - 1];
    heap_size--;
    minHeapify(0);

    return root;
}

void MinHeap::decreaseKey(int i, int new_val)
{
    heap[i] = new_val;
    while (i != 0 && heap[parent(i)] > heap[i])
    {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    extractMin();
}

void MinHeap::insertKey(int k)
{
    heap_size++;
    int i = heap_size - 1;
    heap.push_back(k);

    while (i != 0 && heap[parent(i)] > heap[i])
    {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

int main()
{
    MinHeap heap;
    vector <int>Insert;
    int N;
    fin >> N;

    for (int i = 0; i < N; i++)
    {   
        int operation;
        fin >> operation;

        if (operation == 1)
        {   
            int x;
            fin >> x;
            Insert.push_back(x);
            heap.insertKey(x);
        }
        else if (operation == 2)
        {
            int x;
            fin >> x;
            heap.deleteKey(Insert[x]);
        }
        else if (operation == 3)
        {
            cout << heap.getMin() << "\n";
        }
    }

    fin.close();
    fout.close();

    return 0;
}
