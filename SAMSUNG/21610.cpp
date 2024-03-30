#include<iostream>
#include<vector>
using namespace std;

struct pos {
    int x,y;
};

int n,m,d,s;
int map[52][52];
bool visited[52][52];
vector<pos> cloud;
vector<int> water;
int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dy[8] = {-1,-1,0,1,1,1,0,-1};
int wx[4] = {-1,-1,1,1};
int wy[4] = {-1,1,-1,1};

void input() {
    cin>>n>>m;
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) cin>>map[i][j];
}

pos getPosition(int x,int y) {
    if(x>=n) {
        while(1) {
            if(x>=0 && x<n) {
                break;
            }
            x-=n;
        }
    } else if(x<0) {
        while(1) {
            if(x>=0 && x<n) {
                break;
            }
            x+=n;
        }
    }

    if(y>=n) {
        while(1) {
            if(y>=0 && y<n) {
                break;
            }
            y-=n;
        }
    } else if(y<0) {
        while(1) {
            if(y>=0 && y<n) {
                break;
            }
            y+=n;
        }
    }

    return {x,y};
}

bool checkRange(int x,int y) {
    return x>=0 && x<n && y>=0 && y<n;
}

void makeCloud() {
    cloud.clear();
    water.clear();
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(map[i][j]>=2) {
                if(visited[i][j]) {
                    continue;
                }
                map[i][j]-=2;
                cloud.push_back({i,j});
            }
        }
    }
}

void solve() {
    input();
    cloud.push_back({n-2,0});
    cloud.push_back({n-2,1});
    cloud.push_back({n-1,0});
    cloud.push_back({n-1,1});
    while(m--) {
        cin>>d>>s;
        --d;

        // 모든 구름 이동
        int nx = dx[d] * s;
        int ny = dy[d] * s;
        int size = cloud.size();
        for(int i=0; i<size; i++) {
            cloud[i].x += nx;
            cloud[i].y += ny;
            cloud[i] = getPosition(cloud[i].x,cloud[i].y);
        }

        // 구름 비 내리기
        size = cloud.size();
        for(int i=0; i<size; i++) {
            ++map[cloud[i].x][cloud[i].y];
        }

        // 구름이 모두 사라짐
        for(int i=0; i<n; i++) for(int j=0; j<n; j++) visited[i][j] = false;
        size = cloud.size();
        for(int i=0; i<size; i++) {
            visited[cloud[i].x][cloud[i].y] = true;
        }

        // 대각선으로 거리가 1인 칸에 물이 있는 바구니의 수만큼 물 양 증가
        size = cloud.size();
        for(int i=0; i<size; i++) {
            int add = 0;
            for(int j=0; j<4; j++) {
                int kx = cloud[i].x + wx[j];
                int ky = cloud[i].y + wy[j];
                if(checkRange(kx,ky)) {
                    if(map[kx][ky]>0) {
                        ++add;
                    }
                }
            }
            water.push_back(add);
        }

        for(int i=0; i<water.size(); i++) {
            map[cloud[i].x][cloud[i].y] += water[i];
        }

        // 바구니에 저장된 물이 2 이상인 칸에 구름 생기고 물 2 줄어듦
        makeCloud();
    }

    int answer = 0;
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) answer += map[i][j];
    cout<<answer;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
