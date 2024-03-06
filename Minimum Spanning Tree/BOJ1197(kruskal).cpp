#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct edge {
    int u,v;
    int weight;

    bool operator<(const edge & b) const {
        return weight > b.weight;
    }
};

const int nodesize = 1e4 + 1;
int v,e;
vector<edge> edges;
int parent[nodesize];

void input() {
    cin>>v>>e;
    int a,b,c;
    while(e--) {
        cin>>a>>b>>c;
        edges.push_back({a,b,c});
    }
}

int find(int x) {
    if(parent[x]==x) {
        return x;
    } else {
        return parent[x] = find(parent[x]);
    }
}

bool merge(int x,int y) {
    int xpar = find(x);
    int ypar = find(y);
    if(xpar==ypar) {
        return false;
    }
    if(xpar>ypar) {
        swap(xpar,ypar);
    }
    parent[ypar] = xpar;
    return true;
}

void solve() {
    input();
    sort(edges.begin(),edges.end());
    for(int i=1; i<=v; i++) parent[i] = i;
    int count = v-1;
    int answer = 0;
    while(count>0 && !edges.empty()) {
        edge front = edges.back();
        edges.pop_back();
        if(merge(front.u,front.v)) {
            answer += front.weight;
            --count;
        }
    }
    cout<<answer;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
