#include<iostream>
#include<algorithm>
using namespace std;

const int nodesize = 1e5 + 1;
int n,m,unit;
pair<int,int> tree[nodesize<<2];

void get_unit() {
    unit = 2;
    while(1) {
        if(unit>=n) {
            break;
        }
        unit *= 2;
    }
}

void input() {
    cin>>n>>m;
    get_unit();
    for(int i=0; i<n; i++) {
        cin>>tree[i+unit].first;
        tree[i+unit].second = tree[i+unit].first;
    }
}

void build() {
    for(int i=unit-1; i>0; i--) {
        tree[i].first = min(tree[i*2].first, tree[i*2+1].first);
        tree[i].second = max(tree[i*2].second, tree[i*2+1].second);
    }
}

pair<int,int> query(int start,int end) {
    --start; --end; start+=unit; end+=unit;
    pair<int,int> answer;
    answer.first = 2e9;
    answer.second = -1;
    while(start<=end) {
        if(start%2) {
            answer.first = min(answer.first, tree[start].first);
            answer.second = max(answer.second, tree[start].second);
            ++start;
        }
        if(!(end%2)) {
            answer.first = min(answer.first, tree[end].first);
            answer.second = max(answer.second, tree[end].second);
            --end;
        }
        start/=2;
        end/=2;
    }
    return answer;
}

void solve() {
    pair<int,int> tmp = {2e9,-1};
    fill(tree,tree+(nodesize<<2),tmp);
    input();
    build();
    int s,e;
    while(m--) {
        cin>>s>>e;
        pair<int,int> answer = query(s,e);
        cout<<answer.first<<' '<<answer.second<<'\n';
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
