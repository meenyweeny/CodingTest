#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct edge {
    int vertex;
    int weight;

    bool operator<(const edge & b) const {
        return weight > b.weight;
    }
};

const int nodesize = 2e4 + 1;
const int inf = 2e9;
int dist[nodesize];
int start,v,e;
priority_queue<edge> pq;
vector<edge> graph[nodesize];

void input() {
    cin>>v>>e;
    cin>>start;
    int a,b,w;
    while(e--) {
        cin>>a>>b>>w;
        graph[a].push_back({b,w});
    }
}

void dijkstra() {
    fill(dist,dist+nodesize,inf);
    dist[start] = 0;
    pq.push({start,0});

    while(!pq.empty()) {
        edge front = pq.top();
        pq.pop();

        if(front.weight > dist[front.vertex]) {
            continue;
        }

        for(auto g:graph[front.vertex]) {
            if(dist[front.vertex]+g.weight < dist[g.vertex]) {
                dist[g.vertex] = dist[front.vertex] + g.weight;
                pq.push({g.vertex, dist[g.vertex]});
            }
        }
    }
}

void solve() {
    input();
    dijkstra();
    for(int i=1; i<=v; i++) {
        if(dist[i]==inf) {
            cout<<"INF";
        } else {
            cout<<dist[i];
        }
        cout<<'\n';
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
}
