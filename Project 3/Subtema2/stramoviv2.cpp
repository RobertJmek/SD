#include <fstream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;
using std::ifstream;
using std::ofstream;

const int MAX_NUM_ELEMENTE = 250002;
const int MAX_NUM_INTEROGARI = 300002;

int numElemente, numInterogari;
int pozitiiElemente[MAX_NUM_ELEMENTE];
vector<int> valoriElemente[MAX_NUM_ELEMENTE], pozitiiInterogari[MAX_NUM_ELEMENTE];
pair<int, int> interogari[MAX_NUM_INTEROGARI];
vector<int> elementeCurente, rezultat;
bool vizitat[MAX_NUM_ELEMENTE];
int indexElementCurent;

int main()
{
    ifstream fin("stramosi.in");
    ofstream fout("stramosi.out");

    fin >> numElemente >> numInterogari;
    for (int i = 1, valoare; i <= numElemente; ++i)
    {
        fin >> valoare;
        valoriElemente[valoare].push_back(i);
    }
    for (int i = 1; i <= numInterogari; ++i)
    {
        fin >> interogari[i].first >> interogari[i].second;
        pozitiiInterogari[interogari[i].first].push_back(interogari[i].second);
    }

    indexElementCurent = 0;
    rezultat.push_back(0);
    vizitat[0] = true;

    for (vector<int>::iterator it = valoriElemente[indexElementCurent].begin(); it != valoriElemente[indexElementCurent].end(); ++it)
        elementeCurente.push_back(*it);
    while (!elementeCurente.empty())
    {
        indexElementCurent = elementeCurente.back();
        if (vizitat[indexElementCurent])
        {
            rezultat.pop_back();
            elementeCurente.pop_back();
            continue;
        }

        vizitat[indexElementCurent] = true;
        rezultat.push_back(indexElementCurent);

        for (int i = 0; i < pozitiiInterogari[indexElementCurent].size(); ++i)
        {
            if (pozitiiInterogari[indexElementCurent][i] > rezultat.size() - 1)
                pozitiiInterogari[indexElementCurent][i] = 0;
            else
                pozitiiInterogari[indexElementCurent][i] = rezultat[rezultat.size() - 1 - pozitiiInterogari[indexElementCurent][i]];
        }
        for (vector<int>::iterator it = valoriElemente[indexElementCurent].begin(); it != valoriElemente[indexElementCurent].end(); ++it)
            elementeCurente.push_back(*it);
    }

    for (int i = 1; i <= numInterogari; ++i)
    {
        fout << pozitiiInterogari[interogari[i].first][pozitiiElemente[interogari[i].first]] << '\n';
        ++pozitiiElemente[interogari[i].first];
    }

    fin.close();
    fout.close();
}