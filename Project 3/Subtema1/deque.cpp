#include <iostream>
#include <fstream>


std::ifstream cin("deque.in");
std::ofstream out("deque.out");


int v[5000001], dque[5000001];

int main()
{
	int left, right, n, k;

	long long S = 0;

	cin >> n >> k;
	
	for (int i = 1; i <= n; i++)
		cin >> v[i];
	left = 1;
	right = 0;

	for (int i = 1; i <= n; i++)
	{
		while (left <= right && v[i] <= v[dque[right]])
			right--;
		right++;
		dque[right] = i;
		if ( 1 - dque[left] > k - i)
			left++;
		if (i >= k)
			S += v[dque[left]];
	}
	out << S;
	return 0;
}