#include<iostream>
using namespace std;

const int housesize = 1e3 + 1;
int dp[housesize][3];
int price[housesize][3];
int n;

void input() {
    cin>>n;
    for(int i=1; i<=n; i++) {
        cin>>price[i][0]>>price[i][1]>>price[i][2];
    }
}

void solve() {
    input();
    dp[1][0] = price[1][0];
    dp[1][1] = price[1][1];
    dp[1][2] = price[1][2];
    for(int i=2; i<=n; i++) {
        dp[i][0] = dp[i][1] = dp[i][2] = 2e9;
        dp[i][0] = min(dp[i-1][1],dp[i-1][2]) + price[i][0];
        dp[i][1] = min(dp[i-1][0],dp[i-1][2]) + price[i][1];
        dp[i][2] = min(dp[i-1][1],dp[i-1][0]) + price[i][2];
    }
    int answer = min(dp[n][0], dp[n][1]);
    answer = min(answer,dp[n][2]);
    cout<<answer;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
