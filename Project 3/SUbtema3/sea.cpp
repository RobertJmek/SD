#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

ifstream fin("sea.in");
ofstream fout("sea.out");

int n, m;
pair<double, double> v[402], arr[402];
double fx[100002];
int fn[100002];

double dist(double x, double y) {
  return x * x + y * y;
}

void Bubble(int n, pair<double, double> p[], double x) {
  while (1) {
    bool ok = 0;
    for (int i = 0; i < n - 1; i++)
      if (dist(x - p[i].first, p[i].second) > dist(x - p[i + 1].first, p[i + 1].second))
        swap(p[i], p[i + 1]), ok = 1;
    if (!ok)
      break;
  }
}

int main() {
  fin >> n >> m;
  for (int i = 0; i < n; i++) {
    fin >> v[i].first >> v[i].second;
  }
  sort(v, v + n);
  for (int i = 0; i < m; i++) {
    fin >> fx[i] >> fn[i];
  }
  int j = 0;
  for (int i = 0; i < m; i++) {
    while (j < n && v[j].first <= fx[i]) {
      arr[j] = v[j];
      j++;
    }
    Bubble(j, arr, fx[i]);
    fout << fixed << setprecision(4) << sqrt(dist(arr[fn[i] - 1].first - fx[i], arr[fn[i] - 1].second)) << "\n";
  }
  return 0;
}
