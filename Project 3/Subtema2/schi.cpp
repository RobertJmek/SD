#include <fstream>
#include <cmath>

using namespace std;

ifstream inputFile("schi.in");
ofstream outputFile("schi.out");

int n;
int* v = new int[30100]; // v[i] = numarul de oameni care au ajuns la pozitia i
int* bucket = new int[300];
bool* occupied = new bool[30100];
int* place = new int[30100];
int bucketsize;

void query(int x, int poz)
{
    int i = 0;
    int sum = 0;
    while (sum + bucket[i] < x && i < n / bucketsize)
    {
        sum += bucket[i];
        ++i;
    }
    int j;
    for (j = i * bucketsize; sum != x && j <= n; ++j)
    {
        sum += occupied[j];
    }
    bucket[(j - 1) / bucketsize]--;
    occupied[j - 1] = 0;
    place[j - 1] = poz;
}

void decrement(int x)
{

}

int main()
{
    inputFile >> n;
    bucketsize = 200;
    int i;
    bucket[0] = bucketsize - 1;
    for (i = 1; i <= n / bucketsize; ++i)
    {
        bucket[i] = bucketsize;
    }
    bucket[n / bucketsize] = n - (n / bucketsize) * bucketsize + 1;
    for (i = 1; i <= n; ++i)
    {
        occupied[i] = 1;
        inputFile >> v[i];
    }
    int aux;
    for (i = n; i > 0; --i)
    {
        query(v[i], i);
    }
    for (i = 1; i <= n; ++i)
    {
        outputFile << place[i] << "\n";
    }
    return 0;
}
