#include<iostream>
using namespace std;

const int nodesize = 1e3 + 1;
const int mod = 1e4 + 7;
int dp[nodesize];
int n;

void solve() {
    cin>>n;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    for(int i=4; i<=n; i++) {
        dp[i] = (dp[i-1] + dp[i-2]);
        dp[i]%=mod;
    }
    cout<<dp[n];
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
}
