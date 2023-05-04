#include<iostream>
#include<time.h>
#include<unistd.h>
#include<fstream>
#include <algorithm>
#include <execution>

using namespace std;

ifstream f("algsort.in");
ofstream g("algsort.out");

//// Radix baza 10:

int max(int vec[], int n)
{
    int nrMax=vec[0];
    for( int i = 1; i < n; i++ )
    {
        if ( vec[i] > nrMax )
            nrMax = vec[i];
    }

    return nrMax;
}

void Countsort(int vec[], int n, int digit)

{
    int finalvec[n];
    int i, count[10] = {0};
    cout << count[0];
    for ( i = 0; i < n; i++)
    {
        count[(vec[i] / digit) % 10]++;
    }
    for ( i = 1; i < 10; i++ )
    {
        count[i] += count[i - 1];
    }
    for ( i = n - 1; i >= 0; i-- )
    {
        finalvec[count[(vec[i] / digit ) % 10] - 1 ] = vec[i];
        count[(vec[i] / digit) % 10 ]--;
    }
    for ( i = 0; i < n; i++)
        vec[i] = finalvec[i];
}

void radix( int vec[], int n)


{
    int ma=max(vec, n);
    for ( int digit = 1; ma / digit > 0; digit *= 10 )
        Countsort(vec,n,digit);
}

/// Merge sort:

void merge(int v[], int st, int mij, int dr)
{
    int lminiv_1 = mij - st + 1;
    int lminiv_2 = dr - mij;

    int miniv_1[lminiv_1];
    int miniv_2[lminiv_2];

    for( int i=0; i < lminiv_1; i++)
        miniv_1[i] = v[st + i];
    for ( int i=0; i < lminiv_2; i++)
        miniv_2[i] = v[mij + 1 + i];
    
    int index_1 = 0;
    int index_2 = 0;

    int index_t = st;


    while( index_1 < lminiv_1 && index_2 < lminiv_2 )
    {
        if ( miniv_1[index_1] <= miniv_2[index_2] )
        {   v[index_t] = miniv_1[index_1];
            index_1++;
        }
        else 
        {
            v[index_t] = miniv_2[index_2];
            index_2++;
        }
        index_t++;
    }
    while ( index_1 < lminiv_1 )
    {
        v[index_t] = miniv_1[index_1];
        index_1++;
        index_t++;
    }
    while ( index_2 < lminiv_2 )
    {
        v[index_t] = miniv_2[index_2];
        index_2++;
        index_t++;
    }
}

void MergeSort ( int v[], int start, int stop)
{
    if ( start >= stop)
        return;

    auto mid = start + ( stop - start) / 2;
    MergeSort(v,start,mid);
    MergeSort(v, mid + 1, stop);
    merge(v,start,mid,stop);


}

/// Insertion sort:

void insertion(int v[],int n)
{
    int key=0,i,j;
    for ( i=1; i<n; i++ )
        {
            key = v[i];
            j = i - 1;
            while ( j >= 0 && v[j] > key)
            {
                v[ j + 1] = v[j];
                j--;

            }
            v[j+1] = key;
        }   
}

/// Shelsortv:

void shellSort(int arr[], int n)
{
    for (int gp = n/2; gp > 0; gp /= 2)
    {
        for (int i = gp; i < n; i += 1)
        {
            int tmp = arr[i];
            int j;            
            for (j = i; j >= gp && arr[j - gp] > tmp; j -= gp)
                arr[j] = arr[j - gp];
              
            arr[j] = tmp;
        }
    }
}

//  Countsort:

void countsort(int v[],int n)
{
    int maxe;
    int j=0;
    maxe = max(v,n);
    if ( maxe > 2090000 )
        {
            cout << "Nu pot sorta asta!! Maximul e mult prea mare!!";
        }
    else {
    int count[maxe+1]={0};
    for ( int i=0; i < n; i++ )
    {
        count[v[i]] ++;
    }
    for ( int i=0; i <= maxe; i++ )
    {
        while ( count[i] != 0)
        {
            v[j] = i;
            j++;
            count[i] --;
        }
    }
    }

}

/// Test sortare:

bool sort_test(int vec[],int n)
{   
    bool ok=true;
    for ( int i=0; i < n-1; i++ )
    {
        if ( vec[i+1] < vec[i] )
        {    ok = false;
        }
    return ok;
}
}


/// Afisare vector:

void afisare_v(int v[],int n)
{
    for ( int i=0; i < n; i++)
        cout << v[i] << " ";
}

int main()
{   
    int n;
    f >> n;
    int v[n];
    for ( int i=0; i<n; i++ )
        {   
            f >> v[i];
        }
    clock_t start = clock();
    MergeSort(v,0,n-1);
///     radix(v,n);   
///     insertion(v,n);
///      shellSort(v,n);
///     countsort(v,n);
///    sort(v.begin(),v.end());
    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    g<<("Time measured: %.9f seconds.\n", elapsed);
    cout<<sort_test(v,n);
    

}