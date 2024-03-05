#include<iostream>
#include<algorithm>
using namespace std;

int n, d, k, c;
int type[3001];
int arr[3000001];

void input() {
    cin >> n >> d >> k >> c;
    for (int i = 0; i < n; i++) cin >> arr[i];
}

void solve() {
    input();
    int start = 0;
    int end = k - 1;
    int count = 0;
    for (int i = start; i <= end; i++) {
        if (!type[arr[i]]) {
            ++count;
        }
        ++type[arr[i]];
    }
    int answer = count + !type[c];
    for (int i = 1; i <= n; i++) {
        --type[arr[start]];
        if (!type[arr[start]]) {
            --count;
        }
        ++end;
        ++start;
        end %= n;
        start %= n;
        if (!type[arr[end]]) {
            ++count;
        }
        ++type[arr[end]];
        answer = max(answer, count + !type[c]);
    }
    cout << answer;
    return;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}

//슬라이딩윈도우
