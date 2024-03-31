#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

const int nodesize = 4e2 + 2;
bool likes[nodesize][nodesize];
int map[nodesize][nodesize];
vector<int> seq;
int n;

void input() {
    cin>>n;
    int k,x;
    for(int i=0; i<n*n; i++) {
        cin>>k;
        seq.push_back(k);
        for(int j=0; j<4; j++) {
            cin>>x;
            likes[k][x] = true;
        }
    }
}

bool checkRange(int x,int y) {
    return x>=0 && x<n && y>=0 && y<n;
}

int getScore() {
    int answer = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            int now = map[i][j];
            int likeCount = 0;
            for(int d=0; d<4; d++) {
                int nx = i + "2011"[d] - '1';
                int ny = j + "1120"[d] - '1';
                if(!checkRange(nx,ny)) {
                    continue;
                }
                likeCount += likes[now][map[nx][ny]];
            }
            if(likeCount!=0) {
                --likeCount;
                answer += pow(10,likeCount);
            }
        }
    }
    return answer;
}

void findSeat(int now) {
    pair<int,int> seat;
    int likeCount = -1;
    int emptyCount = -1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(map[i][j]) { // 이미 누가 앉아있으면 건너뜀
                continue;
            }
            int like = 0;
            int emptys = 0;
            for(int d=0; d<4; d++) {
                int nx = i + "2011"[d] - '1';
                int ny = j + "1120"[d] - '1';
                if(!checkRange(nx,ny)) {
                    continue;
                }
                like += likes[now][map[nx][ny]];
                emptys += (map[nx][ny]==0);
            }
            if(likeCount<like) {
                likeCount = like;
                seat = {i,j};
                emptyCount = emptys;
            } else if(likeCount==like) {
                if(emptys>emptyCount) {
                    emptyCount = emptys;
                    seat = {i,j};
                }
            }
        }
    }
    map[seat.first][seat.second] = now;
}

void solve() {
    input();
    for(auto s:seq) {
        findSeat(s);
    }
    cout<<getScore();
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
