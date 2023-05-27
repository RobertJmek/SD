#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("paranteze.in");
ofstream fout("paranteze.out");

int main()
{   
    class paranteza
    {
        public:
        ~paranteza() = default;
        paranteza() = default;
        paranteza(const char& caracter, const int& i) { type = caracter; index = i; }
        char type;
        int index;
    };
    int maxL = 0, nowL = 0;
    int n;
    fin >> n;
    vector <bool> used(n, false);
    char input[n];
    for (int i = 0; i < n; i++)
        fin >> input[i];
    vector <paranteza> stack;
    for (int i = 0; i < n; i++)
    {
        if ( input[i] == '(' || input[i] == '[' || input[i] == '{' )
        {
            stack.push_back(paranteza(input[i],i));
        }
        else if ( input[i] == ')' || input[i] == ']' || input[i] == '}' )
        {
            if ( input[i] == ')' )
            {
                if ( stack.back().type == '(')
                {
                    used[stack.back().index] = true;
                    stack.pop_back();
                }
                else stack.clear();
            }
            else if  ( input[i] == ']' )
            {
                if ( stack.back().type == '[' )
                {
                    used[stack.back().index] = true;
                    stack.pop_back(); 
                }
                else stack.clear();
            }
            else if  ( input[i] == '}' )
            {
                if ( stack.back().type == '{' )
                {
                    used[stack.back().index] = true;
                    stack.pop_back(); 
                }
                else stack.clear();
            }
        }
    }

int i = 0;
while ( i <= n )
    {
        if ( used[i] == true )
        {
            nowL += 2;
            if ( i != n )
                if ( used[i+1] != true)
                    i++;
        }
        else 
            { 
                if (nowL > maxL )
                {
                maxL = nowL;
                nowL = 0;
                }
            }
        i++;
    }

    fout << maxL ;
    return 0;
}