#include<iostream>
#include<algorithm>
using namespace std;

int arr[501][501];
int dp[501][501];
int n;

void solve() {
    cin>>n;
    for(int i=0; i<n; i++) for(int j=0; j<=i; j++) cin>>arr[i][j];
    dp[0][0] = arr[0][0];
    for(int i=1; i<n; i++) {
        dp[i][0] = arr[i][0] + dp[i-1][0];
        dp[i][i] = arr[i][i] + dp[i-1][i-1];
        for(int j=1; j<i; j++) {
            dp[i][j] = max(dp[i-1][j-1],dp[i-1][j]);
            dp[i][j] += arr[i][j];
        }
    }
    int answer = 0;
    for(int i=0; i<n; i++) answer = max(answer, dp[n-1][i]);
    cout<<answer;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
