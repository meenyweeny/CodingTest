#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int stdsize = 3e4 + 2e3 + 1;
int n,m;
vector<int> graph[stdsize];
int indegree[stdsize];
vector<int> answer;

void input() {
    cin>>n>>m;
    int a,b;
    while(m--) {
        cin >> a >> b;
        graph[a].push_back(b);
        ++indegree[b];
    }
}

void solve() {
    queue<int> q;
    for(int i=1; i<=n; i++) {
        if(!indegree[i]) {
            answer.push_back(i);
            q.push(i);
        }
    }
    while(!q.empty()) {
        int front = q.front();
        q.pop();
        for(auto g:graph[front]) {
            --indegree[g];
            if(!indegree[g]) {
                q.push(g);
                answer.push_back(g);
            }
        }
    }

    for(auto a:answer) {
        cout<<a<<' ';
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();
    return 0;
}
