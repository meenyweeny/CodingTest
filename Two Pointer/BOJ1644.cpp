#include<iostream>
#include<vector>
using namespace std;

const int nodesize = 4e6 + 1;
bool prime[nodesize];
int n;
vector<int> arr;

void makePrime() {
    for (int i = 2; i <= 2000; i++) {
        if (prime[i]) {
            continue;
        }
        for (int j = 2; j <= 2e6; j++) {
            int k = i * j;
            if (k >= nodesize) {
                break;
            }
            prime[k] = true;
        }
    }
}

void makeArr() {
    for (int i = 2; i <= n; i++) {
        if (!prime[i]) {
            arr.push_back(i);
        }
    }
}

void solve() {
    cin >> n;
    makePrime();
    makeArr();
    int answer = 0;
    int start, end;
    start = end = 0;
    int sum = 0;
    while (start <= end) {
        if (start >= arr.size() || end >= arr.size()) {
            break;
        }
        if (start == end) {
            sum = arr[start];
        }
        if (sum < n) {
            ++end;
            if (end < arr.size()) {
                sum += arr[end];
            }
            continue;
        }
        if (sum > n) {
            sum -= arr[start];
            ++start;
            continue;
        }
        if (sum == n) {
            ++answer;
            sum -= arr[start];
            ++start;
            continue;
        }
    }
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
