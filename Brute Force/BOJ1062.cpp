#include<iostream>
#include<vector>
using namespace std;

int n,k;
vector<string> arr;
bool alpha[26];
int answer = 0;

void input() {
    cin>>n>>k;
    arr.resize(n);
    for(int i=0; i<n; i++) {
        cin>>arr[i];
    }
}

void count_string(bool set[26]) {
    int count = 0;
    for(auto str:arr) {
        bool flag = true;
        for(int i=4; i<str.length()-4; i++) {
            if(!set[str[i]-'a']) {
                flag = false;
                break;
            }
        }
        count += flag;
    }
    answer = max(answer,count);
}


void make_alpha(bool set[26], int count, int before) {
    if(count>=k) {
        count_string(set);
        return;
    }
    for(int i=before; i<26; i++) {
        if(set[i]) {
            continue;
        }
        set[i] = true;
        make_alpha(set,count+1,i+1);
        set[i] = false;
    }
}

void solution() {
    if(k<5) {
        cout<<0;
        return;
    }

    alpha['a'-'a'] = alpha['n'-'a'] = alpha['t'-'a'] = alpha['i'-'a'] = alpha['c'-'a'] = true;
    k-=5;
    make_alpha(alpha,0,0);
    cout<<answer;
}

void solve() {
    input();
    solution();
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
