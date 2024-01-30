#include<iostream>
using namespace std;

const int len = 1e3 + 1;
string a,b;
int dp[len][len];

void solve() {
    cin>>a;
    cin>>b;

    a = "0" + a;
    b = "1" + b;
    for(int i=1; i<a.size(); i++) {
        char now = a[i];
        for(int j=1; j<b.size(); j++) {
            char comp = b[j];

            if(now==comp) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    cout<<dp[a.size()-1][b.size()-1];
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
