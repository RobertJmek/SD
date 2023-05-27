#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fileInput("timbre.in");
ofstream fileOutput("timbre.out");

bool comparePairs(pair<int, int> X, pair<int, int> Y) {
	return X.first < Y.first;
}

struct CompareHeap {
	bool operator()(int X, int Y) {
		return X > Y;
	}
};

int main() {
	int N, M, K;
	int ans = 0;
	vector<pair<int, int>> intervals;
	priority_queue<int, vector<int>, CompareHeap> minHeap;

	fileInput >> N >> M >> K;

	for (int i = 0; i < M; i++) {
		int m, c;
		fileInput >> m >> c;
		intervals.push_back(make_pair(m, c));
	}

	sort(intervals.begin(), intervals.end(), comparePairs);

	while (N > 0) {
		while (M && intervals[M - 1].first >= N) {
			minHeap.push(intervals[M - 1].second);
			M--;
		}

		ans += minHeap.top();
		minHeap.pop();
		N -= K;
	}

	fileOutput << ans << '\n';

	return 0;
}
