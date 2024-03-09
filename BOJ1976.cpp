#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int nodesize = 201;
int n,m;
vector<int> graph[nodesize];
int parent[nodesize];
bool visited[nodesize];
vector<int> path;

int find(int x) {
    if(parent[x]==x) {
        return x;
    } else {
        return parent[x] = find(parent[x]);
    }
}

bool merge(int x,int y) {
    int xroot = find(x);
    int yroot = find(y);
    if(xroot==yroot) {
        return false;
    }
    if(xroot>yroot) {
        swap(xroot,yroot);
    }
    parent[yroot] = xroot;
    return true;
}

void input() {
    cin>>n>>m;
    for(int i=1; i<=n; i++) parent[i] = i;
    int k;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin>>k;
            if(j>i && k) {
                merge(i, j);
            }
        }
    }
    path.resize(m);
    for(int i=0; i<m; i++) cin>>path[i];
}

bool checkUnion(int x,int y) {
    int xroot = find(x);
    int yroot = find(y);
    return xroot == yroot;
}

void solve() {
    input();
    for(int i=1; i<m; i++) {
        if(!checkUnion(path[i-1],path[i])) {
            cout<<"NO";
            return;
        }
    }
    cout<<"YES";
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
