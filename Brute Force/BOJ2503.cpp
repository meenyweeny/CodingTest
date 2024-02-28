#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct info {
    string str;
    int strike;
    int ball;
};

vector<info> arr;
bool avail[10];

bool checkAvail(string x) {
    fill(avail, avail + 10, false);
    for (auto i : x) {
        if (i == '0') {
            return false;
        }
        if (avail[i - '0']) {
            return false;
        }
        avail[i - '0'] = true;
    }
    return true;
}

void input() {
    int n;
    cin >> n;
    int a, b, c;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> c;
        arr.push_back({ to_string(a),b,c });
    }
}

bool check(string x) {
    bool flag = true;
    for (auto now : arr) {
        string nowString = now.str;
        int strike = 0;
        int ball = 0;
        for (int i = 0; i < 3; i++) {
            char origin = now.str[i];
            for (int j = 0; j < 3; j++) {
                char comp = x[j];
                if (origin == comp) {
                    if (i == j) {
                        ++strike;
                    } else {
                        ++ball;
                    }
                }
            }
        }
        if (now.strike != strike || now.ball != ball) {
            return false;
        }
    }
    return true;
}

void solve() {
    input();
    int answer = 0;
    for (int i = 100; i < 1000; i++) {
        string now = to_string(i);
        if (!checkAvail(now)) {
            continue;
        }
        answer += check(now);
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
