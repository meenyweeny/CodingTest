#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

struct edge {
    int vertex;
    int weight;

    bool operator<(const edge & b) const {
        return weight > b.weight;
    }
};

const int nodesize = 1e3 + 1;
const int inf = 2e9;
int n,m,s,e;
vector<edge> graph[nodesize];
int parent[nodesize], dist[nodesize];

void input() {
    cin>>n>>m;
    int w;
    while(m--) {
        cin>>s>>e>>w;
        graph[s].push_back({e,w});
    }
    cin>>s>>e;
}

void dijkstra() {
    dist[s] = 0;
    parent[s] = -1;
    fill(dist,dist+nodesize,inf);
    priority_queue<edge> pq;
    pq.push({s,0});

    while(!pq.empty()) {
        int front = pq.top().vertex;
        int weight = pq.top().weight;
        pq.pop();

        if(dist[front] < weight) {
            continue;
        }

        for(auto g:graph[front]) {
            if(dist[g.vertex] > weight + g.weight) {
                dist[g.vertex] = weight + g.weight;
                pq.push({g.vertex, dist[g.vertex]});
                parent[g.vertex] = front;
            }
        }
    }
}

void solve() {
    input();
    dijkstra();
    int now = e;
    vector<int> answer;
    while(1) {
        answer.push_back(now);
        if(now==s) {
            break;
        }
        now = parent[now];
    }
    reverse(answer.begin(), answer.end());
    cout<<dist[e]<<'\n'<<answer.size()<<'\n';
    for(auto a:answer) cout<<a<<' ';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
