#include<iostream>
using namespace std;

int n;
int arr[1001];
int dp[1001];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++) {
        int before = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (arr[i] > arr[j]) {
                before = max(before, dp[j]);
            }
        }
        dp[i] = before + 1;
    }
    int answer = 1;
    for (int i = 1; i <= n; i++) {
        answer = max(answer, dp[i]);
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    input();
    return 0;
}
