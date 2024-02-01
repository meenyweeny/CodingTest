#include<iostream>
#include<queue>
using namespace std;

const char blue = 'B';
const int mapsize = 1e2 + 1;
int n;
bool visited[mapsize][mapsize];
char map[mapsize][mapsize];

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        cin >> map[i][j];
    }
}

bool check_range(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

void redbfs(int x,int y,char c) {
    queue<pair<int, int>> q;
    q.push({ x,y });
    visited[x][y] = true;
    while (!q.empty()) {
        int fx = q.front().first;
        int fy = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = fx + "2011"[i] - '1';
            int ny = fy + "1120"[i] - '1';

            if (!check_range(nx, ny)) {
                continue;
            }
            if (c == blue && map[nx][ny] != blue) {
                continue;
            }
            if (c == 'R' || c == 'G') {
                if (map[nx][ny] == blue) {
                    continue;
                }
            }
            if (visited[nx][ny]) {
                continue;
            }
            visited[nx][ny] = true;
            q.push({ nx,ny });
        }
    }
}

void plainbfs(int x, int y, char c) {
    queue<pair<int, int>> q;
    q.push({ x,y });
    visited[x][y] = true;
    while (!q.empty()) {
        int fx = q.front().first;
        int fy = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = fx + "2011"[i] - '1';
            int ny = fy + "1120"[i] - '1';
            
            if (!check_range(nx, ny)) {
                continue;
            }
            if (map[nx][ny] != c) {
                continue;
            }
            if (visited[nx][ny]) {
                continue;
            }
            visited[nx][ny] = true;
            q.push({ nx,ny });
        }
    }
}

void solve() {
    input();
    int plain, red;
    plain = red = 0;
    fill(&visited[0][0], &visited[mapsize - 1][mapsize], false);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        if (visited[i][j]) {
            continue;
        }
        ++plain;
        plainbfs(i,j,map[i][j]);
    }
    fill(&visited[0][0], &visited[mapsize - 1][mapsize], false);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        if (visited[i][j]) {
            continue;
        }
        ++red;
        redbfs(i,j,map[i][j]);
    }
    cout << plain << ' ' << red;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
