#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<iomanip>
using namespace std;

int n,q,l,len;
int map[70][70];
int updatemap[70][70];
bool visited[70][70];

void input() {
    cin>>n>>q;
    len = pow(2,n);
    for(int i=0; i<len; i++) {
        for(int j=0; j<len; j++) {
            cin>>map[i][j];
        }
    }
}

bool checkRange(int x,int y) {
    return x>=0 && x<len && y>=0 && y<len;
}

void rotate(int size,int x,int y) {
    int tmp[size][size];

    int row;
    row = size-1+x;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            tmp[i][j] = map[row-j][i+y];
        }
    }

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            map[x+i][y+j] = tmp[i][j];
        }
    }
}

void splitMap() {
    int size = pow(2,l);
    for(int i=0; i<len; i+=size) {
        for(int j=0; j<len; j+=size) {
            rotate(size,i,j);
        }
    }
}

void decrease() {
    fill(&updatemap[0][0],&updatemap[69][70],0);
    for(int i=0; i<len; i++) {
        for(int j=0; j<len; j++) {
            int count = 0;
            for(int d=0; d<4; d++) {
                int nx = i + "2011"[d] - '1';
                int ny = j + "1120"[d] - '1';

                if(!checkRange(nx,ny)) {
                    continue;
                }
                if(map[nx][ny]>0) {
                    ++count;
                }
            }
            if(count<3) {
                updatemap[i][j] = -1;
            }
        }
    }

    for(int i=0; i<len; i++) {
        for(int j=0; j<len; j++) {
            map[i][j] += updatemap[i][j];
            if(map[i][j]<=0) {
                map[i][j]=0;
            }
        }
    }
}

void getSum() {
    int answer = 0;
    for(int i=0; i<len; i++) {
        for(int j=0; j<len; j++) {
            answer += map[i][j];
        }
    }
    cout<<answer<<'\n';
}

void getYard() {
    int answer = 0;
    fill(&visited[0][0],&visited[69][70],false);
    for(int i=0; i<len; i++) {
        for(int j=0; j<len; j++) {
            if(map[i][j]==0) {
                visited[i][j] = true;
                continue;
            }
            if(visited[i][j]) {
                continue;
            }
            int size = 0;
            queue<pair<int,int>> q;
            q.push({i,j});
            visited[i][j] = true;
            ++size;

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
                    visited[nx][ny] = true;
                    if(map[nx][ny]<=0) {
                        continue;
                    }
                    q.push({nx,ny});
                    ++size;
                }
            }

            answer = max(answer,size);
        }
    }
    cout<<answer;
}

void solve() {
    input();
    while(q--) {
        cin>>l;
        splitMap();
        decrease();
    }
    getSum();
    getYard();
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
