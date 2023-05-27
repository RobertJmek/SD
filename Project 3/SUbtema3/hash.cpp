#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

ifstream cin("hashuri.in");
ofstream cout("hashuri.out");
double y = (sqrt(5) - 1) / 2;
int m;
struct Node {
    int info = 0;
    Node* next = nullptr;
} *h[5200002];

void insert(Node*& first, int value) {
    Node* newNode = new Node;
    newNode->info = value;
    newNode->next = first;
    first = newNode;
}

int get_index(int x) {
    return m * (x * y - floor(x * y));
}

void search(Node* first, int value) {
    if (first == nullptr) {
        cout << "0\n";
    } else {
        int found = 0;
        Node* p = first;
        while (p != nullptr) {
            if (p->info == value) {
                found = 1;
                break;
            }
            p = p->next;
        }
        if (found == 1)
            cout << "1\n";
        else
            cout << "0\n";
    }
}

void remove(Node*& first, int value) {
    if (first == nullptr)
        return;
    Node* temp;
    if (first->info == value) {
        temp = first;
        first = first->next;
        delete temp;
        return;
    }
    Node* current = first;
    while (current->next != nullptr && current->next->info != value) {
        current = current->next;
    }
    if (current->next == nullptr)
        return;
    Node* toDelete = current->next;
    current->next = current->next->next;
    delete toDelete;
}

int main() {
    int n;
    m = 5200000;
    cin >> n;
    int x, j;
    for (; n; n--) {
        cin >> x >> j;
        if (x == 1)
            insert(h[get_index(j)], j);
        else if (x == 2) {
            remove(h[get_index(j)], j);
        } else if (x == 3)
            search(h[get_index(j)], j);
    }

    return 0;
}
