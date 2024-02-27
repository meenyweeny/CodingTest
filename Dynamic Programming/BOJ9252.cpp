#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string a, b;
int lcs[1005][1005];

void input() {
    cin >> a;
    cin >> b;
}

void solve() {
    input();
    if (a.size() > b.size()) {
        swap(a, b);
    }
    a = "-" + a;
    b = "@" + b;
    for (int i = 1; i < a.size(); i++) {
        char now = a[i];
        for (int j = 1; j < b.size(); j++) {
            char comp = b[j];
            if (now == comp) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }
    cout << lcs[a.length()-1][b.length()-1] << endl;
    string answer = "";
    int i, j;
    i = a.length() - 1;
    j = b.length() - 1;
    while (1) {
        if (lcs[i][j] == 0) {
            break;
        }
        if ((lcs[i][j] != lcs[i - 1][j]) && (lcs[i][j] != lcs[i][j - 1])) {
            answer += a[i];
            --i; --j;
        } else if (lcs[i][j] == lcs[i - 1][j]) {
            --i;
        } else {
            --j;
        }
    }
    reverse(answer.begin(), answer.end());
    cout << answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
