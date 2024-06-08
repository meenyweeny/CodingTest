#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;

void solve() {
    cin>>n;
    vector<int> v;
    v.resize(n);
    for(int i=0; i<n; i++) cin>>v[i];
    sort(v.begin(), v.end());
    for(int i=0; i<n; i++) {
        cout<<v[i]<<'\n';
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
