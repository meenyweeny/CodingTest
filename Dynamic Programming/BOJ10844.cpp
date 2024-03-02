#include<iostream>
using namespace std;

const int mod = 1e9;
int n;
int dp[101][10];

void solve() {
    cin>>n;
    for(int i=1; i<=9; i++) dp[1][i] = 1;
    for(int i=2; i<=n; i++) {
        dp[i][0] = dp[i-1][1];
        dp[i][0] %= mod;
        dp[i][9] = dp[i-1][8];
        dp[i][9] %= mod;
        for(int j=1; j<9; j++) {
            dp[i][j] = dp[i-1][j+1];
            dp[i][j] += dp[i-1][j-1];
            dp[i][j] %= mod;
        }
    }
    unsigned long long answer = 0;
    for(int i=0; i<10; i++) {
        answer += dp[n][i];
        answer %= mod;
    }
    cout<<answer;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
