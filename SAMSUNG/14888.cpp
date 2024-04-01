#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> oper;
int n;
int arr[20];
int minans, maxans;

void input() {
	cin >> n;
	oper.resize(4);
	for (int i = 0; i < n; i++) cin >> arr[i];
	for (int i = 0; i < 4; i++) cin >> oper[i];
}

void run(vector<int> op, int sum, int idx) {
	if (idx == n) {
		minans = min(minans, sum);
		maxans = max(maxans, sum);
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (op[i] == 0) {
			continue;
		}
		--op[i];
		int newSum = sum;
		if (i == 0) {
			newSum += arr[idx];
		} else if (i == 1) {
			newSum -= arr[idx];
		} else if (i == 2) {
			newSum *= arr[idx];
		} else {
			newSum /= arr[idx];
		}
		run(op, newSum, idx + 1);
		++op[i];
	}
}

void solve() {
	input();
	minans = 2e9;
	maxans = -2e9;
	run(oper, arr[0], 1);
	cout << maxans << '\n' << minans;
}

int main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios_base::sync_with_stdio(false);

	solve();
	return 0;
}
