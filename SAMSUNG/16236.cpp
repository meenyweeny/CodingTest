#include<iostream>
#include<queue>
using namespace std;

int map[22][22];
bool visited[22][22];
int n;
pair<int,int> shark;
int eaten;
int sharkSize = 2;
int answer;

void input() {
    cin>>n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin>>map[i][j];
            if(map[i][j]==9) {
                map[i][j] = 0;
                shark = {i,j};
            }
        }
    }
}

bool checkRange(int x,int y) {
    return x>=0 && x<n && y>=0 && y<n;
}

pair<int,int> findFish() {
    fill(&visited[0][0],&visited[21][22],false);
    queue<pair<pair<int,int>,int>> q;
    q.push({shark,0});
    visited[shark.first][shark.second] = true;
    int dist = 2e9;
    pair<int,int> fish = {100,100};
    while(!q.empty()) {
        int fx = q.front().first.first;
        int fy = q.front().first.second;
        int count = q.front().second;
        q.pop();

        for(int i=0; i<4; i++) {
            int nx = fx + "2011"[i] - '1';
            int ny = fy + "1120"[i] - '1';
            if(!checkRange(nx,ny)) {
                continue;
            }
            if(visited[nx][ny]) {
                continue;
            }
            if(map[nx][ny]>sharkSize) {
                continue;
            }

            if(map[nx][ny]!=0 && map[nx][ny]<sharkSize) {
                // 가능성 고기
                if(dist>(count+1)) {
                    dist = count + 1;
                    fish = {nx,ny};
                } else if(dist==count+1) {
                    if(fish.first>nx) {
                        fish = {nx,ny};
                    } else if(fish.first==nx) {
                        if(fish.second>ny) {
                            fish = {nx,ny};
                        }
                    }
                }
            }

            q.push({{nx,ny},count+1});
            visited[nx][ny] = true;
        }
    }
    if(dist>=2e9) {
        return {-1,-1};
    }

    answer += dist;
    map[fish.first][fish.second] = 0;
    shark = fish;
    ++eaten;
    if(eaten==sharkSize) {
        ++sharkSize;
        eaten = 0;
    }

    return fish;
}

void solve() {
    input();
    while(1) {
        pair<int,int> go = findFish();
        if(go.first==-1 && go.second==-1) {
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
