#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int r,c,k;
int answer;
int map[102][102];
int cnt[103];
int row,col;
vector<pair<int,int>> v;

bool comp(pair<int,int> a, pair<int,int> b) {
    if(a.second == b.second) {
        return a.first < b.first;
    } else {
        return a.second < b.second;
    }
}

void input() {
    cin>>r>>c>>k;
    --r;
    --c;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cin>>map[i][j];
        }
    }
    row = col = 2;
}

void solve() {
    input();
    while(1) {
        if(map[r][c]==k) {
            break;
        }
        if(answer>=100) {
            answer = -1;
            break;
        }
        ++answer;



        if(row>=col) {

            int newCol = 0;

            for(int i=0; i<=row; i++) { // 모든 행에 대해
                for(int q=0; q<=100; q++) {
                    cnt[q] = 0;
                }
                for(int j=0; j<100; j++) { // 열의 각 숫자 셈
                    if(map[i][j]==0) {
                        continue;
                    }
                    ++cnt[map[i][j]];
                }

                v.clear();
                for(int j=1; j<=100; j++) { // 정렬을 위해 (수, 몇번) 담음
                    if(cnt[j]==0) {
                        continue;
                    }
                    v.push_back({j,cnt[j]});
                }

                sort(v.begin(), v.end(), comp); // 정렬

                for(int j=0; j<100; j++) { // 그 행 일단 다 0으로 만듦
                    map[i][j] = 0;
                }

                int idx = 0;
                for(auto now:v) { // 새로 채움. 채우다가 100 넘으면 끝
                    if(idx >= 100) break;
                    map[i][idx] = now.first;
                    newCol = max(newCol, idx); // 최대 열 개수 구하기 위한 갱신
                    ++idx;
                    if(idx >= 100) break;
                    map[i][idx] = now.second;
                    newCol = max(newCol, idx);
                    ++idx;
                }
            }
            col = newCol;
        } else {
            int newRow = 0;
            for(int i=0; i<=col; i++) {
                for(int q=0; q<=100; q++) {
                    cnt[q] = 0;
                }
                for(int j=0; j<100; j++) { //개수 셈
                    if(map[j][i]==0) {
                        continue;
                    }
                    ++cnt[map[j][i]];
                }

                v.clear();
                for(int j=1; j<=100; j++) {
                    if(cnt[j]==0) {
                        continue;
                    }
                    v.push_back({j,cnt[j]});
                }

                sort(v.begin(), v.end(), comp);

                for(int j=0; j<100; j++) { // 그 열 다 0으로 만듦
                    map[j][i] = 0;
                }

                int idx = 0;
                int size = v.size();
                for(int j=0; j<size; j++) {
                    pair<int,int> now = v[j];
                    if(idx >= 100) break;
                    map[idx][i] = now.first;
                    newRow = max(newRow, idx);
                    ++idx;
                    if(idx >= 100) break;
                    map[idx][i] = now.second;
                    newRow = max(newRow, idx);
                    ++idx;
                }
            }
            row = newRow;
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
