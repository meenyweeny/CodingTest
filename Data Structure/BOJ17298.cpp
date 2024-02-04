#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const int nodesize = 1e6 + 1;
vector<int> arr;
vector<int> answer;
priority_queue<int, vector<int>, greater<int>> pq;
int n;

void input() {
    cin>>n;
    arr.resize(n);
    for(int i=0; i<n; i++) {
        cin>>arr[i];
    }
}

void solve() {
    input();
    reverse(arr.begin(), arr.end());
    answer.push_back(-1);
    pq.push(arr[0]);
    for(int i=1; i<n; i++) {
        while(1) {
            if(pq.empty()) {
                answer.push_back(-1);
                break;
            }
            if(pq.top()>arr[i]) {
                answer.push_back(pq.top());
                break;
            } else {
                pq.pop();
            }
        }
        pq.push(arr[i]);
    }
    reverse(answer.begin(), answer.end());
    for(auto a:answer) {
        cout<<a<<' ';
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
