#include<iostream>
#include<algorithm>
#include<vector>
#include<fstream>
#include<time.h>
#include<unistd.h>
using namespace std;
ifstream f("algsort.in");
ofstream g("algsort.out");

int main()
{
    int n;
    f >> n;
    vector <int> v;
    for ( int i=0; i < n; i++)
    {
        int c;
        f >> c;
        v.push_back(c);
    }
    clock_t start = clock();

    sort(v.begin(), v.end() );

    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    g<<("Time measured: %.9f seconds.\n", elapsed);

}