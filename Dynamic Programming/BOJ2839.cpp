#include<iostream>
#include<algorithm>
using namespace std;

const int nodesize = 5e3 + 1;
int dp[nodesize];

void solve() {
    int n;
    cin >> n;
    dp[0] = 0;
    dp[1] = dp[2] = dp[4] = -1;
    dp[3] = dp[5] = 1;
    for (int i = 6; i <= n; i++) {
        if (dp[i - 3] == -1 && dp[i - 5] == -1) {
            dp[i] = -1;
        } else if (dp[i - 3] == -1) {
            dp[i] = dp[i - 5] + 1;
        } else if(dp[i-5]==-1) {
            dp[i] = dp[i - 3] + 1;
        } else {
            dp[i] = min(dp[i - 3], dp[i - 5]) + 1;
        }
    }
    cout << dp[n];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
