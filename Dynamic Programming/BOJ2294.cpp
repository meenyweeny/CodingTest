#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> coins;
int n,k;
int dp[10001];

void input() {
    cin>>n>>k;
    coins.resize(n);
    for(int i=0; i<n; i++) cin>>coins[i];
}

void solve() {
    input();
    sort(coins.begin(), coins.end());
    fill(dp,dp+10001,2e9);
    for(int i=0; i<n; i++) {
        int now = coins[i];
        if(now>k) break;
        dp[now] = 1;
        for(int p=now+1; p<=k; p++) {
            dp[p] = min(1+dp[p-now],dp[p]);
        }
    }
    cout<<(dp[k]>=2e9 ? -1 : dp[k]);
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
