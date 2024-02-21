#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
vector<int> arr;

void input() {
    cin>>n;
    arr.resize(n);
    for(int i=0; i<n; i++) cin>>arr[i];
}

void solve() {
    input();
    sort(arr.begin(), arr.end());
    int start = 0;
    int end = n-1;
    pair<int,int> answer;
    int comp = 2e9 + 1;
    while(start<end) {
        int now = arr[start] + arr[end];
        if(abs(now)<comp) {
            answer = {arr[start],arr[end]};
            comp = abs(now);
        }
        if(now<0) {
            ++start;
        } else if(now==0) {
            break;
        } else {
            --end;
        }
    }
    cout<<answer.first<<' '<<answer.second;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
