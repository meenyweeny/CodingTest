#include<iostream>
#include<vector>
using namespace std;

const int a[2][4][2] = {{{0,0},{0,1},{0,2},{0,3}},
             {{0,0},{1,0},{2,0},{3,0}}};
const int b[1][4][2] = {{{0,0},{0,1},{1,0},{1,1}}};
const int c[8][4][2] = {{{0,0},{1,0},{2,0},{2,1}},
                        {{0,0},{0,1},{0,2},{1,0}},
                        {{0,0},{0,1},{1,1},{2,1}},
                        {{-1,2},{0,0},{0,1},{0,2}},
                        {{0,0},{1,0},{2,0},{2,-1}},
                        {{0,0},{0,1},{0,2},{1,2}},
                        {{0,0},{0,1},{1,0},{2,0}},
                        {{0,0},{1,0},{1,1},{1,2}}};
const int d[4][4][2] = {{{0,0},{1,0},{1,1},{2,1}},
                        {{0,0},{0,1},{-1,1},{-1,2}},
                        {{0,0},{1,0},{-1,1},{0,1}},
                        {{0,0},{0,1},{1,1},{1,2}}};
const int e[4][4][2] = {{{0,0},{0,1},{0,2},{1,1}},
                        {{0,0},{-1,1},{0,1},{1,1}},
                        {{0,0},{0,1},{0,2},{-1,1}},
                        {{0,0},{1,0},{2,0},{1,1}}};
int n,m;
int map[502][502];

void input() {
    cin>>n>>m;
    for(int i=0; i<n; i++) for(int j=0; j<m; j++) cin>>map[i][j];
}

bool checkRange(int x,int y) {
    return x>=0 && x<n && y>=0 && y<m;
}

void solve() {
    input();
    int answer = 0;
    //a
    for(int x=0; x<n; x++) {
        for(int y=0; y<m; y++) {
            for(int i=0; i<2; i++) {
                int sum = 0;
                for(int j=0; j<4; j++) {
                    int nx = x + a[i][j][0];
                    int ny = y + a[i][j][1];
                    if(!checkRange(nx,ny)) {
                        sum = -2e9;
                        break;
                    } else {
                        sum += map[nx][ny];
                    }
                }
                answer = max(answer,sum);
            }
        }
    }
    //c
    for(int x=0; x<n; x++) {
        for(int y=0; y<m; y++) {
            for(int i=0; i<8; i++) {
                int sum = 0;
                for(int j=0; j<4; j++) {
                    int nx = x + c[i][j][0];
                    int ny = y + c[i][j][1];
                    if(!checkRange(nx,ny)) {
                        sum = -2e9;
                        break;
                    } else {
                        sum += map[nx][ny];
                    }
                }
                answer = max(answer,sum);
            }
        }
    }
    //b
    for(int x=0; x<n; x++) {
        for(int y=0; y<m; y++) {
            for(int i=0; i<1; i++) {
                int sum = 0;
                for(int j=0; j<4; j++) {
                    int nx = x + b[i][j][0];
                    int ny = y + b[i][j][1];
                    if(!checkRange(nx,ny)) {
                        sum = -2e9;
                        break;
                    } else {
                        sum += map[nx][ny];
                    }
                }
                answer = max(answer,sum);
            }
        }
    }
    //d
    for(int x=0; x<n; x++) {
        for(int y=0; y<m; y++) {
            for(int i=0; i<4; i++) {
                int sum = 0;
                for(int j=0; j<4; j++) {
                    int nx = x + d[i][j][0];
                    int ny = y + d[i][j][1];
                    if(!checkRange(nx,ny)) {
                        sum = -2e9;
                        break;
                    } else {
                        sum += map[nx][ny];
                    }
                }
                answer = max(answer,sum);
            }
        }
    }
    //e
    for(int x=0; x<n; x++) {
        for(int y=0; y<m; y++) {
            for(int i=0; i<4; i++) {
                int sum = 0;
                for(int j=0; j<4; j++) {
                    int nx = x + e[i][j][0];
                    int ny = y + e[i][j][1];
                    if(!checkRange(nx,ny)) {
                        sum = -2e9;
                        break;
                    } else {
                        sum += map[nx][ny];
                    }
                }
                answer = max(answer,sum);
            }
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
