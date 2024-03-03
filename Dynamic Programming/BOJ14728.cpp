#include<iostream>
#include<algorithm>
using namespace std;

const int maxsize = 1e2 + 1;
const int maxtime = 1e4 + 1;
int n,t;
int info[maxsize][2];
int dp[maxsize][maxtime];

void input() {
    cin>>n>>t;
    for(int i=0; i<n; i++) cin>>info[i][0]>>info[i][1];
}

void solve() {
    input();
    for(int i=0; i<=t; i++) dp[0][i] = info[0][0] > i ? 0 : info[0][1];
    for(int i=1; i<n; i++) {
        int time = info[i][0];
        int score = info[i][1];
        for(int j=0; j<=t; j++) {
            if(time>j) {
                dp[i][j] = dp[i-1][j];
                continue;
            }
            dp[i][j] = max(dp[i-1][j], score + dp[i-1][j-time]);
        }
    }
    cout<<dp[n-1][t];
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
