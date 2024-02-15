#include<iostream>
#include<algorithm>
using namespace std;

const int nodesize = 1e5 + 1;
int n,s;
int arr[nodesize];
int answer = 2e9;

void solve() {
    cin>>n>>s;
    for(int i=1; i<=n; i++) {
        cin>>arr[i];
        arr[i] += arr[i-1];
    }

    int start, end;
    start = end = 1;
    while(start<=end && end<=n) {
        int sum = arr[end];
        sum -= arr[start-1];
        if(sum>=s) {
            answer = min(answer, end-start+1);
            ++start;
        } else {
            ++end;
        }
    }
    cout << ((answer==2e9) ? 0 : answer);
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
