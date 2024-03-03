#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n;
vector<string> arr;
vector<pair<int,int>> priority;
vector<int> value;

void input() {
    cin>>n;
    arr.resize(n);
    for(int i=0; i<n; i++) cin>>arr[i];
}

void solve() {
    input();
    value.resize(26);
    for(int i=0; i<26; i++) priority.push_back({0,i});
    for(auto str:arr) {
        int weight = 1;
        for(int i=str.length()-1; i>=0; i--) {
            int index = str[i] - 'A';
            priority[index].second = index;
            priority[index].first += weight;
            weight *= 10;
        }
    }
    sort(priority.begin(), priority.end());
    reverse(priority.begin(), priority.end());
    int val = 9;
    for(auto p:priority) {
        value[p.second] = val--;
    }
    unsigned long long answer = 0;
    for(auto str:arr) {
        int weight = 1;
        int sum = 0;
        for(int i=str.length()-1; i>=0; i--) {
            sum += (value[str[i]-'A'] * weight);
            weight *= 10;
        }
        answer += sum;
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
