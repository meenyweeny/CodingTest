#include<iostream>
#include<queue>
using namespace std;

int n,sum;
priority_queue<int, vector<int>, greater<int>> pq;

void solve() {
    cin>>n;
    int k;
    while(n--) {
        cin>>k;
        pq.push(k);
    }
    int tmp = 0;
    while(pq.size()>1) {
        tmp = 0;
        tmp += pq.top();
        pq.pop();
        tmp += pq.top();
        pq.pop();
        pq.push(tmp);
        sum += tmp;
    }
    cout<<sum;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
