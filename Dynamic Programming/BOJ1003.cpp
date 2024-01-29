#include<iostream>
using namespace std;

long dp[41][2];

void makedp() {
    dp[0][0] = 1;
    dp[1][1] = 1;
    dp[2][0] = dp[2][1] = 1;

    for(int i=3; i<=40; i++) {
        dp[i][0] = (dp[i-1][0] + dp[i-2][0]);
        dp[i][1] = (dp[i-1][1] + dp[i-2][1]);
    }
}

void solve() {
    int t;
    cin>>t;
    makedp();
    int x;
    while(t--) {
        cin>>x;
        cout<<dp[x][0]<<' '<<dp[x][1]<<'\n';
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
}
