#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct Bet {
	int amount, time;
};

const int HASH_MOD = 666013;
vector<Bet> bets[HASH_MOD];
vector<int> times;
int n, m, t;

int main() {
	freopen("pariuri.in", "r", stdin);
	freopen("pariuri.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &m);
		for (int j = 1; j <= m; j++) {
			bool found = false;
			Bet newBet;
			scanf("%d %d", &newBet.time, &newBet.amount);
			for (vector<Bet>::iterator it = bets[newBet.time % HASH_MOD].begin(); it != bets[newBet.time % HASH_MOD].end(); it++) {
				Bet& existingBet = *it;
				if (existingBet.time == newBet.time) {
					found = true;
					existingBet.amount += newBet.amount;
				}
			}
			if (!found) {
				bets[newBet.time % HASH_MOD].push_back(newBet);
				times.push_back(newBet.time);
				t++;
			}
		}
	}
	printf("%d\n", t);
	while (!times.empty()) {
		int currentTime = times.back();
		times.pop_back();
		for (vector<Bet>::iterator it = bets[currentTime % HASH_MOD].begin(); it != bets[currentTime % HASH_MOD].end(); it++) {
			Bet& bet = *it;
			if (bet.time == currentTime)
				printf("%d %d ", bet.time, bet.amount);
			continue;
		}
	}
	return 0;
}
