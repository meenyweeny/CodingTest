#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

const int black = -1;
const int rainbow = 101;
const int emp = 0;
int map[22][22];
int tmp[22][22];
bool visited[22][22];
int n,m;
long long answer;
pair<int,int> group;

void input() {
    cin>>n>>m;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin>>map[i][j];
            if(map[i][j]==0) {
                map[i][j] = rainbow;
            }
        }
    }
}

bool checkRange(int x,int y) {
    return x>=0 && x<n && y>=0 && y<n;
}

void findGroup() {
    group = {-1,-1}; // init
    int groupSize = -1;
    int rainbowCount = -1;
    fill(&visited[0][0],&visited[21][22],false);

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {

            if(map[i][j]==black || map[i][j]==rainbow || map[i][j] == emp) {
                continue;
            }
            if(visited[i][j]) {
                continue;
            }
            for(int i=0; i<n; i++) {
                for(int j=0; j<n; j++) {
                    if(map[i][j]==rainbow) {
                        visited[i][j] = false;
                    }
                }
            }

            int now = map[i][j];
            queue<pair<int,int>> q;
            q.push({i,j});
            int size = 1;
            int rainsize = 0;
            visited[i][j] = true;

            while(!q.empty()) {
                int fx = q.front().first;
                int fy = q.front().second;
                q.pop();

                for(int d=0; d<4; d++) {
                    int nx = fx + "2011"[d] - '1';
                    int ny = fy + "1120"[d] - '1';
                    if(!checkRange(nx,ny)) {
                        continue;
                    }
                    if(visited[nx][ny]) {
                        continue;
                    }
                    if(map[nx][ny]==now || map[nx][ny]==rainbow) {
                        ++size;
                        visited[nx][ny] = true;
                        q.push({nx,ny});
                        if(map[nx][ny]==rainbow) {
                            ++rainsize;
                        }
                    }
                }
            }
            if(size>=2) {
                if (size > groupSize) {
                    groupSize = size;
                    rainbowCount = rainsize;
                    group = {i, j};
                } else if (size == groupSize) {
                    if (rainbowCount < rainsize) {
                        rainbowCount = rainsize;
                        group = {i, j};
                    } else if(rainbowCount==rainsize) {
                        if(group.first < i) {
                            group = {i,j};
                        } else if(group.second<j) {
                            group = {i,j};
                        }
                    }
                }
            }
        }
    }
    if(groupSize<2) {
        group = {-1,-1};
    }
}

void remove() {
    int removed = 1;
    int block = map[group.first][group.second];
    queue<pair<int,int>> q;
    q.push({group.first, group.second});
    map[group.first][group.second] = emp;

    while(!q.empty()) {
        int fx = q.front().first;
        int fy = q.front().second;
        q.pop();

        for(int i=0; i<4; i++) {
            int nx = fx + "2011"[i] - '1';
            int ny = fy + "1120"[i] - '1';
            if(!checkRange(nx,ny)) {
                continue;
            }
            if(map[nx][ny] == emp || map[nx][ny] == black) {
                continue;
            }
            if(map[nx][ny]==block || map[nx][ny]==rainbow) {
                q.push({nx,ny});
                map[nx][ny] = emp;
                ++removed;
            }
        }
    }
    int add = (removed*removed);
    answer += add;
}

void gravity() {
    for(int j=0; j<n; j++) {
        for(int i=n-1; i>=0; i--) {
            int now = map[i][j];
            if(now==black || now==emp) {
                continue;
            }
            int row = i;
            while(1) {
                if(row>=n-1) {
                    break;
                }
                if(map[row+1][j] == emp) {
                    map[row][j] = emp;
                    ++row;
                    map[row][j] = now;
                } else {
                    break;
                }
            }
        }
    }
}

void turn() {
    fill(&tmp[0][0],&tmp[21][22],0);
    int len = n-1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            tmp[i][j] = map[j][len];
        }
        --len;
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            map[i][j] = tmp[i][j];
        }
    }
}

void solve() {
    input();
    while(1) {
        findGroup();
        if(group.first == -1 && group.second == -1) {
            break;
        }
        remove();
        gravity();
        turn();
        gravity();
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
