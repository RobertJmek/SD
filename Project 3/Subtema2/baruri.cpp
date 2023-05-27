#include <fstream>
#include <cstring>

using namespace std;

ifstream inputFile("baruri.in");
ofstream outputFile("baruri.out");

int t, n, m, i, x, y, op, d, a[100010];

long long getSum(int x)
{
    long long sum = 0;
    while (x)
    {
        sum += a[x];
        x -= x & -x;
    }
    return sum;
}

void update(int pos, int val)
{
    while (pos <= n)
    {
        a[pos] += val;
        pos += pos & -pos;
    }
}

int main()
{
    inputFile >> t;
    while (t--)
    {
        memset(a, 0, sizeof(a));
        inputFile >> n;
        for (i = 1; i <= n; i++)
        {
            inputFile >> x;
            update(i, x);
        }
        inputFile >> m;
        while (m--)
        {
            inputFile >> op >> x >> y;
            if (op == 0)
            {
                int xx = max(x - y, 1);
                int yy = min(n, x + y);
                outputFile << getSum(x - 1) - getSum(xx - 1) + getSum(yy) - getSum(x) << "\n";
            }
            else if (op == 1)
            {
                update(y, x);
            }
            else if (op == 2)
            {
                update(y, -x);
            }
            else
            {
                int z;
                inputFile >> z;
                update(y, -x);
                update(z, x);
            }
        }
    }
    return 0;
}
