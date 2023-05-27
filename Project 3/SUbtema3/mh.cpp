#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

set<int> multipliiE;
vector<int> elemente;
int auxiliar = 0;
ifstream in("heapuri.in");
ofstream out("heapuri.out");

void insertElement(int number) {
    elemente.push_back(number);
    multipliiE.insert(number);
}

void deleteElement(int position) {
    int x = elemente[position];
    multipliiE.erase(x);
}

int main() {
    int numOperations;
    in >> numOperations;
    vector<pair<int, int>> operations;

    for (int i = 0; i < numOperations; ++i) {
        int operationType, number;
        in >> operationType;
        if (operationType == 1 || operationType == 2) {
            in >> number;
            operations.push_back({operationType, number});
        } else {
            operations.push_back({operationType, -1});
        }
    }

    for (const auto& op : operations) {
        int operationType = op.first;
        int number = op.second;

        if (operationType == 1) {
            insertElement(number);
        } else if (operationType == 2) {
            deleteElement(number - 1);
        } else if (operationType == 3) {
            out << *multipliiE.begin() << endl;
        }
    }

    in.close();
    out.close();

    return 0;
}
