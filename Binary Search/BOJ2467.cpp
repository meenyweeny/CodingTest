#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
vector<int> arr;

void solve() {
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    pair<int, int> answer;
    int comp = 2e9 + 1;
    for (int i = 0; i < n; i++) {
        int start = 0;
        int end = n - 1;
        while (start <= end) {
            int mid = (start + end) / 2;
            int sum;
            if (mid == i) {
                sum = arr[i] < 0 ? -2e9 : 2e9;
            } else {
                sum = arr[i] + arr[mid];
            }
            if (comp > abs(sum)) {
                comp = abs(sum);
                answer = { i,mid };
            }
            if (sum == 0) {
                cout << arr[answer.first] << ' ' << arr[answer.second] << '\n';
                return;
            }
            if (sum > 0) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
    }
    if (answer.first > answer.second) {
        swap(answer.first, answer.second);
    }
    cout << arr[answer.first] << ' ' << arr[answer.second] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
