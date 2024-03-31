#include<iostream>
using namespace std;

const int nodesize = 1e6 + 2;
int student[nodesize];
int n,b,c;
unsigned long long answer;

void input() {
    cin>>n;
    for(int i=0; i<n; i++) cin>>student[i];
    cin>>b>>c;
}

void solve() {
    input();
    for(int i=0; i<n; i++) {
        student[i] -= b;
        ++answer;
        if(student[i]<=0) {
            continue;
        }
        int mod = student[i]/c;
        answer += (mod);
        student[i] -= (mod*c);
        if(student[i]>0) {
            ++answer;
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
