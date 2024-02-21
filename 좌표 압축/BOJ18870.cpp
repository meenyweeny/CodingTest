#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
vector<int> arr;
vector<int> uniq;

void input() {
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
}

void solve() {
    input();
    uniq = arr;
    sort(uniq.begin(), uniq.end());
    uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());
    for (auto a : arr) {
        int index = lower_bound(uniq.begin(), uniq.end(), a) - uniq.begin();
        cout << index << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
