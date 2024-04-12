#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int map[52][52];
vector<pair<int,int> > seq;
int n,m,d,s;
int maxSize;
pair<int,int> shark;
vector<int> refill;
int answer[4];
const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};

void input() {
    cin>>n>>m;
    shark = {n/2, n/2};
    maxSize = n*n;
    --maxSize;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin>>map[i][j];
        }
    }
}

bool checkRange(int x,int y) {
    return x>=0 && x<n && y>=0 && y<n;
}

void makeMap() {
    int nx,ny;
    nx = shark.first;
    ny = shark.second;
    int fx[4] = {0,1,0,-1};
    int fy[4] = {-1,0,1,0};
    int fd = 0;
    int count = 0;
    int iter = 0;
    int tmp = 1;
    int length = 1;
    while(1) {
        nx += fx[fd];
        ny += fy[fd];
        if(!checkRange(nx,ny)) {
            break;
        }
        seq.push_back({nx,ny});
        ++tmp;
        ++iter;
        if(iter==length) {
            fd++;
            fd%=4;
            ++count;
            iter = 0;
            if(count==2) {
                count = 0;
                ++length;
            }
        }
    }
}

void blizard() {
    int nx = shark.first;
    int ny = shark.second;
    for(int i=0; i<s; i++) {
        nx += dx[d];
        ny += dy[d];
        map[nx][ny] = 0;
    }
}

void fillMap() {
    int sz = seq.size();
    refill.clear();
    for(int i=0; i<sz; i++) {
        pair<int,int> next = seq[i];
        int now = map[next.first][next.second];
        if(now==0) {
            continue;
        }
        refill.push_back(now);
    }
    fill(&map[0][0],&map[51][52],0);
    for(int i=0; i<refill.size(); i++) {
        pair<int,int> next = seq[i];
        map[next.first][next.second] = refill[i];
    }
    refill.clear();
}

bool bombContinuous() {
    bool flag = false;
    int before = 0;
    int count = 0;
    for(int i=0; i<seq.size(); i++) {
        pair<int,int> nxt = seq[i];
        int now = map[nxt.first][nxt.second];
        if(now!=before) {
            if(count>3) {
                flag = true;
                int q=i-1;
                for(int cnt=0; cnt<count; cnt++) {
                    map[seq[q].first][seq[q].second] = 0;
                    --q;
                }
                answer[before] += count;
            }
            count = 1;
            before = now;
        } else {
            ++count;
        }
    }
    return flag;
}

void magic() {
    refill.clear();
    int before = 0;
    int count = 0;
    for(int i=0; i<seq.size(); i++) {
        int now = map[seq[i].first][seq[i].second];
        if(now==0) {
            break;
        }
        if(now!=before) {
            if(before==0) {
                count = 1;
                before = now;
                continue;
            } else {
                refill.push_back(count);
                refill.push_back(before);
                count = 1;
                before = now;
            }
        } else {
            ++count;
        }
    }
    refill.push_back(count);
    refill.push_back(before);

    fill(&map[0][0],&map[51][52],0);
    for(int i=0; i<refill.size(); i++) {
        if(i>=seq.size()) {
            break;
        }
        pair<int,int> nxt = seq[i];
        int now = refill[i];
        map[nxt.first][nxt.second] = now;
    }
}

void solve() {
    input();
    makeMap();
    while(m--) {
        cin>>d>>s;
        --d;
        blizard();
        fillMap();
        while(1) {
            if(!bombContinuous()) {
                break;
            }
            fillMap();
        }
        magic();
    }
    cout<<(1*answer[1])+(2*answer[2])+(3*answer[3]);
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
