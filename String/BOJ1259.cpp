#include<iostream>
#include<string>
using namespace std;

string str;

bool judge(string s) {
    int len = s.length();
    for (int i = 0; i < len / 2; i++) {
        int j = len - 1 - i;
        if (s[i] != s[j]) {
            return false;
        }
    }
    return true;
}

void solve() {
    cin >> str;
    while (str!="0") {
        cout << (judge(str) ? "yes" : "no") << '\n';
        cin >> str;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();
    return 0;
}
