#include<iostream>
#include<algorithm>
using namespace std;

const int maxweight = 1e5 + 1;
const int maxsize = 1e2 + 1;
int dp[maxsize][maxweight];
int arr[maxsize][2];
int n,k;

void input() {
    cin>>n>>k;
    for(int i=0; i<n; i++) cin>>arr[i][0]>>arr[i][1];
}

void solve() {
    input();
    for(int i=0; i<=k; i++) dp[0][i] = i>=arr[0][0] ? arr[0][1] : 0;
    for(int i=1; i<n; i++) {
        int weight = arr[i][0];
        int value = arr[i][1];
        for(int j=0; j<=k; j++) {
            if(weight>j) {
                dp[i][j] = dp[i-1][j];
                continue;
            }
            dp[i][j] = max(dp[i-1][j],value+dp[i-1][j-weight]);
        }
    }
    cout<<dp[n-1][k];
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
