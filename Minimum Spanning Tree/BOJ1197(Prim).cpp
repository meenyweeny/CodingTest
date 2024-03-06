#include<iostream>
#include<algorithm>
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

const int nodesize = 1e4 + 1;
int v,e;
vector<edge> graph[nodesize];
bool visited[nodesize];

void input() {
    cin>>v>>e;
    int a,b,c;
    while(e--) {
        cin>>a>>b>>c;
        graph[a].push_back({b,c});
        graph[b].push_back({a,c});
    }
}

void solve() {
    input();
    priority_queue<edge> pq;
    visited[1] = true;
    for(auto g:graph[1]) {
        pq.push(g);
    }
    int count = v-1;
    int answer = 0;
    while(!pq.empty() && count > 0) {
        edge front = pq.top();
        pq.pop();

        if(!visited[front.vertex]) {
            visited[front.vertex] = true;
            --count;
            answer += front.weight;

            for(auto g:graph[front.vertex]) {
                if(!visited[g.vertex]) {
                    pq.push(g);
                }
            }
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
