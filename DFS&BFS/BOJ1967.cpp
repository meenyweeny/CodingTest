#include<iostream>
#include<vector>
using namespace std;

const int nodesize = 1e4 + 1;
int n;
vector<pair<int, int>> graph[nodesize];
int maxdist, maxnode;
bool visited[nodesize];

void input() {
    cin >> n;
    int u, v, d;
    for (int i = 1; i < n; i++) {
        cin >> u >> v >> d;
        graph[u].push_back({ v,d });
        graph[v].push_back({ u,d });
    }
}

void dfs(int x, int dist) {
    visited[x] = true;
    if (dist > maxdist) {
        maxdist = dist;
        maxnode = x;
    }
    for (auto edge : graph[x]) {
        if (visited[edge.first]) {
            continue;
        }
        dfs(edge.first, dist + edge.second);
    }
}

void solve() {
    input();
    fill(visited, visited + nodesize, false);
    dfs(1,0);
    fill(visited, visited + nodesize, false);
    dfs(maxnode, 0);
    cout << maxdist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
