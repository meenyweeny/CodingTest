#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct fish {
    int x,y,dir;
};

const int n = 4;
const int dx[8] = {-1,-1,0,1,1,1,0,-1};
const int dy[8] = {0,-1,-1,-1,0,1,1,1};
const fish deadfish = {-1,-1,-1};
int board[4][4];
vector<fish> fishes;
pair<int,int> sharkpos;
int answer = 0;
int sharkdir;

void input() {
    int idx,dir;
    fishes.resize(17);
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin>>idx>>dir;
            --dir;
            fishes[idx] = {i,j,dir};
            board[i][j] = idx;
        }
    }
}

bool checkRange(int x,int y) {
    return x>=0 && x<n && y>=0 && y<n;
}

void run(vector<fish> fishlist, int tmp[4][4],
         pair<int,int> spos, int sdir, int eaten) {

    answer = max(answer,eaten);

    int map[4][4];
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            map[i][j] = tmp[i][j];
        }
    }

    // 물고기 이동
    for(int i=1; i<=16; i++) {
        if (fishlist[i].x == -1) { // 죽지 않은 물고기에 대해서만 이동 가능
            continue;
        }
        int nowFish = i; // 지금 물고기 번호
        int ndir = fishlist[i].dir; // 지금 물고기 방향
        int fx = fishlist[i].x;
        int fy = fishlist[i].y;
        while (1) {
            int nx = fx + dx[ndir];
            int ny = fy + dy[ndir];
            // 범위를 벗어나거나, 상어면 갈 수 없음
            if (!checkRange(nx, ny)){
                ++ndir;
                ndir %= 8;
                if (ndir == fishlist[i].dir) { // 이동할 수 있는 곳이 없음 (360도 돌았는데도)
                    break;
                }
                continue;
            }
            if (nx == spos.first && ny == spos.second) { // 상어
                ++ndir;
                ndir %= 8;
                if (ndir == fishlist[i].dir) { // 이동할 수 있는 곳이 없음 (360도 돌았는데도)
                    break;
                }
                continue;
            }
            if (map[nx][ny] == 0) { // 빈 칸이라 이동 가능
                // 그냥 그 곳으로 이동
                map[nx][ny] = nowFish;
                map[fx][fy] = 0;
                fishlist[nowFish].dir = ndir;
                fishlist[nowFish].x = nx;
                fishlist[nowFish].y = ny;
                break;
            } else { // 다른 고기랑 교환
                int otherFish = map[nx][ny];
                map[nx][ny] = nowFish;
                map[fx][fy] = otherFish;
                fishlist[nowFish].dir = ndir;
                fishlist[nowFish].x = nx;
                fishlist[nowFish].y = ny;
                fishlist[otherFish].x = fx;
                fishlist[otherFish].y = fy;
                break;
            }
        }
    }

    // 상어 이동
    int sx = spos.first;
    int sy = spos.second;
    int sd = sdir;
    while(1) {
        sx += dx[sd];
        sy += dy[sd];

        if(!checkRange(sx,sy)) { // 이제 더는 그 방향으로 가지 못함
            break;
        }
        if(map[sx][sy]==0) { // 빈 칸으로 갈 수 없음
            continue;
        }

        // 그 자리의 물고기를 먹음
        int nowFish = map[sx][sy];
        fish info = fishlist[nowFish];
        // 잡아먹기
        fishlist[nowFish] = deadfish;
        map[sx][sy] = 0;
        run(fishlist,map,{sx,sy},info.dir,eaten+nowFish);
        // 되돌려놓기
        fishlist[nowFish] = info;
        map[sx][sy] = nowFish;
    }
}

void solve() {
    input();
    int eat = board[0][0];
    // 초기 상어 조건
    board[0][0] = 0;

    sharkpos = {0,0};
    sharkdir = fishes[eat].dir;
    fishes[eat] = deadfish;
    run(fishes,board,sharkpos,sharkdir,eat);

    cout<<answer;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
