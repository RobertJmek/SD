#include <fstream>
#include <vector>

using namespace std;

const char InFile[] = "muzica.in";
const char OutFile[] = "muzica.out";
const int MOD = 10003;

ifstream fin(InFile);
ofstream fout(OutFile);

int N, M, A, B, C, D, E, sol, x, R;
vector<int> H[MOD];

inline void Insert(int val)
{
    int key = val % MOD;
    if (key < 0)
    {
        key = -key;
    }
    H[key].push_back(val);
}

inline int Check(int val)
{
    int key = val % MOD;
    if (key < 0)
    {
        key = -key;
    }
    for (vector<int>::iterator it = H[key].begin(); it != H[key].end(); ++it)
    {
        if (*it == val)
        {
            *it = H[key][H[key].size() - 1];
            H[key].pop_back();
            return 1;
        }
    }
    return 0;
}

int main()
{
    fin >> N >> M;
    fin >> A >> B >> C >> D >> E;
    for (register int i = 1; i <= N; ++i)
    {
        fin >> x;
        Insert(x);
    }
    fin.close();

    sol += Check(A);
    sol += Check(B);
    for (register int i = 3; i <= M; ++i)
    {
        R = (1LL * C * B + 1LL * D * A) % E;
        A = B;
        B = R;
        sol += Check(R);
    }

    fout << sol;
    fout.close();
    return 0;
}
