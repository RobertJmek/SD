#include <fstream>

using namespace std;

const int MAX_N = 200100;
const int MOD = 666013;

ifstream fin("permheap.in");
ofstream fout("permheap.out");

int d[MAX_N];

long long put(long long a, int b) {
  if (!b) {
    return 1;
  }
  if (b & 1) {
    return (a * put(a, b - 1)) % MOD;
  }
  long long x = put(a, b / 2);
  return (x * x) % MOD;
}

int fact[MAX_N];
int IM[MAX_N];

long long comb(int n, int k) {
  return ((1LL * fact[n] * IM[n - k]) % MOD * IM[k]) % MOD;
}

int imparte(int n) {
  int h = 0;
  for (; (1 << h) * 2 - 1 < n; h++);

  int r = n - (1 << h) + 1;

  if (r >= (1 << (h - 1))) {
    return (1 << h) - 1;
  }
  else {
    return (1 << (h - 1)) + r - 1;
  }
}

int main() {
  int n;
  fin >> n;

  fact[0] = IM[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = (1LL * fact[i - 1] * i) % MOD;
    IM[i] = put(fact[i], MOD - 2);
  }

  d[0] = 1;
  d[1] = 1;
  for (int i = 2; i <= n; i++) {
    int left = imparte(i);
    d[i] = ((comb(i - 1, left) * d[left]) % MOD * d[i - left - 1]) % MOD;
  }

  fout << d[n];

  return 0;
}
