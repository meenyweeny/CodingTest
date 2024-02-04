#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<string>
using namespace std;

const int nodesize = 1e4 + 1;
int n, m;
vector<int> arr;
bool visited[8];
unordered_map<string,int> check;
vector<string> answer;

void select(int count, string str) {
    if (count == m) {
        if(check[str]) {
            return;
        }
        check[str] = 1;
        answer.push_back(str);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            continue;
        }
        visited[i] = true;
        select(count + 1, str + to_string(arr[i]) + " ");
        visited[i] = false;
    }
}

void solve() {
    cin >> n >> m;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());
    select(0,"");

    for (auto a : answer) {
        cout << a << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
