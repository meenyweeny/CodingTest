#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n,m;
bool liar[51];
int parent[51];
int lie[51];
vector<vector<int>> party;

void input() {
    cin>>n>>m;
    int l,k;
    cin>>l;
    while(l--) {
        cin>>k;
        liar[k] = true;
    }
    party.resize(m);
    for(int i=0; i<m; i++) {
        cin>>l;
        while(l--) {
            cin>>k;
            party[i].push_back(k);
        }
        sort(party[i].begin(), party[i].end());
    }
}

int find(int x) {
    if(x==parent[x]) {
        return x;
    } else {
        return parent[x] = find(parent[x]);
    }
}

void merge(int x,int y) {
    int xroot = find(x);
    int yroot = find(y);
    if(!(!liar[yroot] && !liar[xroot])) {
        liar[yroot] = liar[xroot] = true;
    }
    if(xroot == yroot) {
        return;
    }
    if(xroot>yroot) {
        swap(xroot,yroot);
    }
    parent[yroot] = xroot;
}

void makeSet() {
    for(int i=1; i<=n; i++) {
        parent[i] = i;
    }
    for(auto p:party) {
        for(int i=1; i<p.size(); i++) {
            merge(p[0],p[i]);
        }
    }
}

void makeFalse() {
    for(int i=1; i<=n; i++) {
        if(!liar[i]) {
            continue;
        }
        for(int j=1; j<=n; j++) {
            if(i==parent[j]) {
                lie[j] = -1;
                for(int k=1; k<=n; k++) {
                    if(parent[k]==j) {
                        parent[k] = i;
                        lie[k] = -1;
                    }
                }
            }
        }
    }
}

int check() {
    int answer = 0;
    for(auto p:party) {
        bool flag = true;
        for(int i=0; i<p.size(); i++) {
            if(lie[p[i]] < 0) {
                flag = false;
                break;
            }
        }
        answer += flag;
    }
    return answer;
}

void solve() {
    input();
    makeSet();
    makeFalse();
    cout<<check();
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
