#include <iostream>
#include <fstream>
using namespace std;

ifstream inputFile("matrice3.in");
ofstream outputFile("matrice3.out");

const int N = 251;

int n, m, qq, x[N][N], lg2[N];
unsigned char rmq[9][9][N][N];

inline int query(int x1, int y1, int x2, int y2)
{
    int smax, t1, l0 = x2 - x1 + 1, l1 = y2 - y1 + 1;
    int lg0 = lg2[l0], lg1 = lg2[l1];

    smax = max(rmq[lg0][lg1][x1][y1], rmq[lg0][lg1][x2 - (1 << lg0) + 1][y2 - (1 << lg1) + 1]);
    t1 = max(rmq[lg0][lg1][x2 - (1 << lg0) + 1][y1], rmq[lg0][lg1][x1][y2 - (1 << lg1) + 1]);

    return t1 > smax ? t1 : smax;
}

int main()
{
    int i, j, k, l, x1, x2, y1, y2, pas;

    char a[N];

    inputFile >> n >> m >> qq;
    inputFile.getline(a, N);

    for (i = 1; i <= n; ++i)
    {
        inputFile.getline(a, N);
        for (j = 1; j <= m; ++j)
        {
            x[i][j] = a[j - 1] - '0';
            x[i][j] = -x[i][j];
        }
    }

    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            if (x[i][j] != -1)
            {

                if (x[i - 1][j] != -1)
                    x[i][j] = x[i - 1][j];

                if (x[i - 1][j - 1] != -1 && x[i - 1][j - 1] < x[i][j])
                    x[i][j] = x[i - 1][j - 1];

                if (x[i][j - 1] != -1 && x[i][j - 1] < x[i][j])
                    x[i][j] = x[i][j - 1];

                if (x[i - 1][j] == -1 || x[i][j - 1] == -1 || x[i - 1][j - 1] == -1)
                    x[i][j] = 0;

                x[i][j] += 1;

                rmq[0][0][i][j] = x[i][j];
            }

    lg2[1] = 0;

    for (k = 1; (1 << k) <= m; ++k)
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= m - (1 << k) + 1; ++j)
            {
                int l1 = (1 << (k - 1));

                rmq[0][k][i][j] = max(rmq[0][k - 1][i][j], rmq[0][k - 1][i][j + l1]);
            }
    for (k = 1; (1 << k) <= n; ++k)
        for (i = 1; i <= n - (1 << k) + 1; ++i)
            for (j = 1; j <= m; ++j)
            {
                int l1 = (1 << (k - 1));

                rmq[k][0][i][j] = max(rmq[k - 1][0][i][j], rmq[k - 1][0][i + l1][j]);
            }

    for (i = 2; i <= n || i <= m; ++i)
        lg2[i] = lg2[i >> 1] + 1;

    for (i = 1; (1 << i) <= n; ++i)
        for (j = 1; (1 << j) <= m; ++j)
            for (k = 1; k <= n - (1 << i) + 1; ++k)
                for (l = 1; l <= m - (1 << j) + 1; ++l)
                {
                    int l1 = 1 << (i - 1), l2 = 1 << (j - 1), t1;

                    rmq[i][j][k][l] = max(rmq[i - 1][j - 1][k][l],
                                          rmq[i - 1][j - 1][k + l1][l]);
                    t1 = max(rmq[i - 1][j - 1][k][l + l2],
                             rmq[i - 1][j - 1][k + l1][l + l2]);

                    if (t1 > rmq[i][j][k][l])
                        rmq[i][j][k][l] = t1;
                }

    for (i = 1; i <= qq; ++i)
    {
        inputFile >> x1 >> y1 >> x2 >> y2;

        pas = 1 << 9;

        for (j = 0; pas != 0; pas >>= 1)
            if (j + pas <= x2 - x1 && j + pas <= y2 - y1 &&
                query(x1 + j + pas, y1 + j + pas, x2, y2) - 1 >= j + pas)
                j += pas;

        outputFile << j + 1 << "\n";
    }

    return 0;
}
