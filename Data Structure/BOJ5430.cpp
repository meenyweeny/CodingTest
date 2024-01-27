#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;

deque<int> arr;
string command;
int n;
bool is_front;

void input() {
    cin>>command;
    cin>>n;
    char ch;
    int k = 0;
    cin>>ch;
    while(1) {
        cin>>ch;
        if(ch==']' || ch==',') {
            if(k!=0) {
                arr.push_back(k);
                k = 0;
            }
        }
        if(ch==']') {
            break;
        }
        if(ch==',') {
            continue;
        }
        k*=10;
        k+=(ch-'0');
    }
}

void solution() {
    for(auto cmd:command) {
        if(cmd=='R') {
            is_front = !is_front;
        } else {
            if(arr.empty()) {
                cout<<"error\n";
                return;
            }
            is_front ? arr.pop_front() : arr.pop_back();
        }
    }

    if(!is_front) {
        reverse(arr.begin(),arr.end());
    }
    cout<<'[';
    for(int i=0; i<arr.size(); i++) {
        cout<<arr[i];
        if(i!=arr.size()-1) {
            cout<<',';
        }
    }
    cout<<"]\n";
}

void solve() {
    int t;
    cin>>t;
    while(t--) {
        arr.clear();
        is_front = true;
        input();
        solution();
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solve();
}
