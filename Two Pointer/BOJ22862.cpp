#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;

int n, k;
deque<int> arr;

void input() {
    cin >> n >> k;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    while (!arr.empty()) {
        if (arr.front() % 2) {
            arr.pop_front();
        } else {
            break;
        }
    }
    while (!arr.empty()) {
        if (arr.back() % 2) {
            arr.pop_back();
        }
        else {
            break;
        }
    }
}

void solve() {
    input();
    int answer = 0;
    deque<int> dqpos;
    int count, deleted;
    count = deleted = 0;
    int start, end;
    start = end = 0;
    int size = arr.size();
    while (start <= end && end < size) {
        if (start == end) {
            if ((arr[start] % 2)==1) {
                ++start; ++end;
            } else {
                ++end;
                count = 1;
            }
            answer = max(answer, count);
            continue;
        }

        int startnum, endnum;
        startnum = arr[start];
        endnum = arr[end];
        if (deleted < k) {
            if ((endnum % 2)==0) {
                ++end;
                ++count;
            } else {
                ++end;
                ++deleted;
            }
        } else if (deleted == k) {
            if (endnum % 2) {
                ++start;
                if ((startnum % 2) == 0) {
                    --count;
                }
                else {
                    --deleted;
                }
            } else {
                ++end;
                ++count;
            }
        }
        answer = max(answer, count);
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
