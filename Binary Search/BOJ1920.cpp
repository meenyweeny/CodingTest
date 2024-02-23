#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int nodesize = 1e5 + 1;
vector<int> arr;

void input() {
    int n;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
}

void solve() {
    input();
    sort(arr.begin(), arr.end());
    int m; cin >> m;
    int k;
    while (m--) {
        cin >> k;
        cout << binary_search(arr.begin(), arr.end(), k)<<'\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
