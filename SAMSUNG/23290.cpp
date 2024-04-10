#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int map[4][4][8];
int moved[4][4][8];
int copied[4][4][8];
int smell[4][4];
bool visit[4][4];
int m,s;
const int n = 4;
pair<int,int> shark;
vector<int> seq;
int fishCount;
const int dx[8] = {0,-1,-1,-1,0,1,1,1};
const int dy[8] = {-1,-1,0,1,1,1,0,-1};
const int sx[4] = {-1,0,1,0};
const int sy[4] = {0,-1,0,1};

void input() {
    cin>>m>>s;
    int x,y,d;
    while(m--) {
        cin>>x>>y>>d;
        --x;
        --y;
        --d;
        ++map[x][y][d];
    }
    cin>>shark.first>>shark.second;
    --shark.first;
    --shark.second;
}

bool checkRange(int x,int y) {
    return x>=0 && x<n && y>=0 && y<n;
}

void copyFish() {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<8; k++) {
                copied[i][j][k] = map[i][j][k];
            }
        }
    }
}

void applyFish() {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<8; k++) {
                map[i][j][k] += copied[i][j][k];
            }
        }
    }
}

void moveFish() {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<8; k++) {
                moved[i][j][k] = 0;
            }
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<8; k++) {
                if(map[i][j][k]==0) { // 옮길 고기 없음
                    continue;
                }
                int dir = k;
                while(1) {
                    int nx = i + dx[dir];
                    int ny = j + dy[dir];

                    if(!checkRange(nx,ny)) { // 격자 벗어나면 못 감
                        --dir; // 그 방향으로 갈 수 없으면 방향을 45도 반시계
                        if(dir==-1) {
                            dir=7;
                        }
                        if(dir==k) { // 한 바퀴 돌았는데도 못 간 것임
                            moved[i][j][k] += map[i][j][k];
                            break;
                        }
                        continue;
                    } else if(smell[nx][ny]>0) { // 냄새 있으면 못 감
                        --dir;
                        if(dir==-1) {
                            dir=7;
                        }
                        if(dir==k) {
                            moved[i][j][k] += map[i][j][k];
                            break;
                        }
                        continue;
                    } else if(nx==shark.first && ny==shark.second) { // 상어 있으면 못 감
                        --dir;
                        if(dir==-1) {
                            dir=7;
                        }
                        if(dir==k) {
                            moved[i][j][k] += map[i][j][k];
                            break;
                        }
                        continue;
                    } else {
                        moved[nx][ny][dir] += map[i][j][k]; // 고기 그 방향으로 옮김
                        break;
                    }
                }
            }
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<8; k++) {
                map[i][j][k] = moved[i][j][k];
            }
        }
    }
}

void findSequence(vector<int> now, int eaten, int bx, int by, bool visited[4][4]) {
    if(now.size()==3) { // 3번 이동 방향 다 정했으면, 그걸로 할지 말지 결정
        if(eaten>fishCount) {
            fishCount = eaten;
            seq = now;
        }
        return;
    }

    bool tmp[4][4];
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            tmp[i][j] = visited[i][j];
        }
    }

    for(int i=0; i<4; i++) {
        int nx = bx + sx[i];
        int ny = by + sy[i];
        if(!checkRange(nx,ny)) {
            continue;
        }
        int sum = 0;
        if(!tmp[nx][ny]) {
            for(int k=0; k<8; k++) {
                sum += map[nx][ny][k];
            }
        }
        tmp[nx][ny] = true;
        now.push_back(i);
        findSequence(now,eaten+sum,nx,ny,tmp);
        tmp[nx][ny] = visited[nx][ny];
        now.pop_back();
    }
}

void moveShark() {
    int nx = shark.first;
    int ny = shark.second;

    for(int i=0; i<3; i++) { // 이동 완료
        int dir = seq[i];
        nx += sx[dir];
        ny += sy[dir]; // 격자 내 좌표임이 보장

        int eaten = 0;
        for(int k=0; k<8; k++) { // 고기 먹음
            eaten += map[nx][ny][k];
            map[nx][ny][k] = 0;
        }
        if(eaten>0) {
            smell[nx][ny] = 3;
        }
    }
    seq.clear();
    shark = {nx,ny}; // 이동 과정
}

void reduceSmell() {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            --smell[i][j];
            if(smell[i][j]<0) {
                smell[i][j]=0;
            }
        }
    }
}

void getAnswer() {
    int answer = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<8; k++) {
                answer += map[i][j][k];
            }
        }
    }
    cout<<answer;
}

void solve() {
    input();
    while(s--) {
        copyFish();
        moveFish();
        fishCount = -1;
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                visit[i][j] = false;
            }
        }
        findSequence({},0,shark.first,shark.second,visit);
        moveShark();
        reduceSmell();
        applyFish();
    }
    getAnswer();
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
