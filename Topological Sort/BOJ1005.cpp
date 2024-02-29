#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const int nodesize = 1e3 + 1;
int n, k, w;
int price[nodesize];
int indegree[nodesize];
vector<int> graph[nodesize];
vector<int> revgraph[nodesize];
int dp[nodesize];

void init() {
    fill(price, price + nodesize, 0);
    fill(indegree, indegree + nodesize, 0);
    fill(dp, dp + nodesize, 0);
    for (int i = 0; i < nodesize; i++) {
        graph[i].clear();
        revgraph[i].clear();
    }
}

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> price[i];
    }
    int a, b;
    while (k--) {
        cin >> a >> b;
        graph[a].push_back(b);
        revgraph[b].push_back(a);
        ++indegree[b];
    }
    cin >> w;
}

int topology() {
    queue<pair<int, int>> q;
    for (int i = 1; i <= n; i++) {
        if (!indegree[i]) {
            q.push({ i,1 });
            dp[i] = price[i];
        }
    }

    while (!q.empty()) {
        int front = q.front().first;
        int level = q.front().second;
        q.pop();

        if (front == w) {
            break;
        }

        for (auto g : graph[front]) {
            --indegree[g];
            if (!indegree[g]) {
                int value = 0;
                for (auto rg : revgraph[g]) {
                    value = max(value, dp[rg]);
                }
                q.push({ g,level + 1 });
                dp[g] = value + price[g];
            }
        }
    }

    return dp[w];
}

void solve() {
    int t;
    cin >> t;
    while (t--) {
        init();
        input();
        cout << topology() << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
