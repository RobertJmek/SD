#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

ifstream fin("datorii.in");
ofstream fout("datorii.out");

int main()
{
    int n, m;
    fin >> n >> m;
    vector<int> zile(n+1);
    for (int i = 1; i < n+1; ++i)
    {
        fin >> zile[i];
    }
    for (int i = 0; i < m; ++i)
    {
        int cod, t, v, p, q;
        fin >> cod;
        if (cod == 0)
        {
            fin >> t >> v;
            zile[t] -= v;
        }
        else
        {
            fin >> p >> q;
            int suma = 0;
            for (int j = p; j <= q; ++j)
            {
                suma += zile[j];
            }
            fout << suma << '\n';
        }

    }

return 0;

}
