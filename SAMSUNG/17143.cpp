#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct info {
    int x,y;
    int speed, dir, size;
    bool alive;
};

const int emp = -1;
int r,c,m,pos;
int answer;
int map[102][102];
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,1,-1};
vector<int> movemap[102][102];
vector<info> shark;

void input() {
    fill(&map[0][0], &map[101][102], emp);
    cin>>r>>c>>m;
    int x,y,speed,dir,size;
    for(int i=0; i<m; i++) {
        cin>>x>>y>>speed>>dir>>size;
        --x;
        --y;
        --dir;
        map[x][y] = i;
        shark.push_back({x,y,speed,dir,size,true});
    }
}

int switchDirection(int dir) {
    if(dir==0) return 1;
    else if(dir==1) return 0;
    else if(dir==2) return 3;
    else return 2;
}

void catchShark() {
    int index = -1;
    for(int i=0; i<r; i++) {
        if(map[i][pos]!=emp) {
            index = map[i][pos];
            break;
        }
    }
    if(index!=-1) {
        shark[index].alive = false;
        map[shark[index].x][shark[index].y] = emp;
        shark[index].x = shark[index].y = -1;
        answer += shark[index].size;
    }
}

pair<pair<int,int>,int> getNextPos(int x,int y,int speed,int dir) {
    if(dir==0 ||dir==1) {
        int iter = (speed) % (r*2-2);
        while(1) {
            if(iter==0) break;
            int mx = x + dx[dir];
            if(mx>=r || mx<0) {
                dir = switchDirection(dir);
            } else {
                --iter;
                x += dx[dir];
            }
        }
    } else {
        int iter = (speed) % (c*2-2);
        while(1) {
            if(iter==0) break;
            int my = y + dy[dir];
            if(my>=c || my<0) {
                dir = switchDirection(dir);
            } else {
                --iter;
                y += dy[dir];
            }
        }
    }
    return {{x,y},dir};
}

void moveShark() {
    int len = shark.size();
    for(int i=0; i<len; i++) {
        if(!shark[i].alive) {
            continue;
        }
        pair<pair<int,int>,int> nextinfo = getNextPos(shark[i].x,shark[i].y,shark[i].speed, shark[i].dir);
        shark[i].x = nextinfo.first.first;
        shark[i].y = nextinfo.first.second;
        shark[i].dir = nextinfo.second;
        movemap[nextinfo.first.first][nextinfo.first.second].push_back(i);
    }
}

void refillMap() {
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            if(movemap[i][j].empty()) {
                map[i][j] = emp;
            } else if(movemap[i][j].size()==1) {
                map[i][j] = movemap[i][j].front();
            } else {
                int bigindex = movemap[i][j].front();
                int bigsize = shark[bigindex].size;
                for(int q=1; q<movemap[i][j].size(); q++) {
                    if(bigsize<shark[movemap[i][j][q]].size) {
                        bigsize = shark[movemap[i][j][q]].size;
                        bigindex = movemap[i][j][q];
                    }
                }

                for(int q=0; q<movemap[i][j].size(); q++) {
                    int nowindex = movemap[i][j][q];
                    if(nowindex!=bigindex) {
                        shark[nowindex].x = shark[nowindex].y = -1;
                        shark[nowindex].alive = false;
                    }
                }

                map[i][j] = bigindex;
            }
        }
    }

    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            movemap[i][j].clear();
        }
    }
}

void solve() {
    input();
    while(pos<c) {
        catchShark();
        moveShark();
        refillMap();
        ++pos;
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
