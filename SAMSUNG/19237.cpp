#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
using namespace std;

struct sharkinfo {
    int index;
    int x,y,dir;
    bool alive;
};

struct smellinfo {
    int shark, power;
};

const smellinfo emptysmell = {0,0};
smellinfo smell[22][22];
int n,m,k;
int remain;
vector<vector<int>> prior[404];
vector<sharkinfo> shark;
int map[22][22];
int tmp[22][22];
const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};

void input() {
    cin>>n>>m>>k;
    remain = m;
    shark.resize(m+1);
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin>>map[i][j];
            if(map[i][j]!=0) {
                int index = map[i][j];
                shark[index] = {index,i,j,0,true};
            }
            smell[i][j] = emptysmell;
        }
    }
    int d;
    for(int i=1; i<=m; i++) {
        cin>>d;
        shark[i].dir = d-1;
    }
    for(int i=1; i<=m; i++) {
        prior[i].resize(4);
        for(int iter=0; iter<4; iter++) {
            for(int j=0; j<4; j++) {
                cin>>d;
                --d;
                prior[i][iter].push_back(d);
            }
        }
    }
}

bool checkRange(int x,int y) {
    return x>=0 && x<n && y>=0 && y<n;
}

void spreadSmell() {
    for(int i=1; i<=m; i++) {
        if(shark[i].alive) {
            smell[shark[i].x][shark[i].y] = {shark[i].index,k};
        }
    }
}

void reduceSmell() {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(smell[i][j].shark == 0 && smell[i][j].power == 0) {
                continue;
            }
            --smell[i][j].power;
            if(smell[i][j].power==0) {
                smell[i][j] = emptysmell;
            }
        }
    }
}

void moveShark() {
    fill(&tmp[0][0],&tmp[21][22],0);
    for(int i=1; i<=m; i++) {
        if(!shark[i].alive) {
            continue;
        }
        int x = shark[i].x;
        int y = shark[i].y;
        int dir = shark[i].dir;
        int nextdir = -1;

        // 냄새 없는 칸 찾기
        for(int d=0; d<4; d++) {
            int next = prior[i][dir][d];
            int nx = x + dx[next];
            int ny = y + dy[next];
            if(!checkRange(nx,ny)) {
                continue;
            }
            if(smell[nx][ny].shark == 0 && smell[nx][ny].power == 0) {
                nextdir = next;
                break;
            }
        }

        if(nextdir!=-1) { // 냄새 없는 칸을 찾은 것
            // 그 상어는 이제 그 방향으로 이동하면 됨
            shark[i].dir = nextdir;
            shark[i].x = x + dx[nextdir];
            shark[i].y = y + dy[nextdir];

            if(tmp[shark[i].x][shark[i].y]!=0) { // 이미 다른 상어가 있음
                shark[i].x = shark[i].y = -1;
                shark[i].alive = false;
                --remain;
            } else {
                tmp[shark[i].x][shark[i].y] = i;
            }
            continue;
        }

        // 내 냄새가 있는 칸 찾기
        for(int d=0; d<4; d++) {
            int next = prior[i][dir][d];
            int nx = x + dx[next];
            int ny = y + dy[next];
            if(!checkRange(nx,ny)) {
                continue;
            }
            if(smell[nx][ny].shark == i) {
                nextdir = next;
                break;
            }
        }

        if(nextdir!=-1) { // 내 냄새 있는 칸을 찾음
            // 그 상어는 이제 그 방향으로 이동하면 됨
            shark[i].dir = nextdir;
            shark[i].x = x + dx[nextdir];
            shark[i].y = y + dy[nextdir];

            if(tmp[shark[i].x][shark[i].y]!=0) { // 이미 다른 상어가 있음
                shark[i].x = shark[i].y = -1;
                shark[i].alive = false;
                --remain;
            } else {
                tmp[shark[i].x][shark[i].y] = i;
            }
            continue;
        }
    }

    // map을 새로 이동한 상어들로 만들어주기
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            map[i][j] = tmp[i][j];
        }
    }
}

void solve() {
    input();
    int answer = 0;
    spreadSmell();
    while(1) {
        if(answer==1000) {
            answer = -1;
            break;
        }
        ++answer;
        moveShark();
        reduceSmell();
        spreadSmell();
        if(remain==1) {
            break;
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
