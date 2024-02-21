#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int nodesize = 1e6 + 1;
int n;
vector<int> arr;
vector<int> lis;

void input() {
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

void solve() {
    input();
    lis.push_back(arr.front());
    for (int i = 1; i < n; i++) {
        if (lis.back() < arr[i]) {
            lis.push_back(arr[i]);
            continue;
        }
        int index = lower_bound(lis.begin(), lis.end(), arr[i]) - lis.begin();
        lis[index] = arr[i];
    }
    cout << lis.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
