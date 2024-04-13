#include<iostream>
#include<algorithm>
#include<deque>
#include<iomanip>
#include<cmath>
using namespace std;

const int inf = 2e9;
const int dx[2] = {1,0};
const int dy[2] = {0,1};
int n,k;
int answer = 0;
int adjust[101][101];
deque<deque<int>> bowl;
deque<deque<int>> tmpbowl;

void init() {
    answer = 0;
    bowl.clear();
}

void input() {
    cin>>n>>k;
    int tmp;
    deque<int> inp;
    for(int i=0; i<n; i++) {
        cin>>tmp;
        inp.push_back(tmp);
    }
    bowl.push_back(inp);
}

void pushFish() { // 물고기 수가 가장 적은 어항들에 물고기를 한 마리 넣음
    int minFish = inf;
    for(int i=0; i<n; i++) {
        minFish = min(minFish, bowl[0][i]);
    }
    for(int i=0; i<n; i++) {
        if(bowl[0][i]==minFish) {
            ++bowl[0][i];
        }
    }
}

void flyOneFish() { // 딱 하나의 어항만 위에 올리기
    deque<int> dfly;
    dfly.push_back(bowl[0][0]);
    bowl[0].pop_front();
    bowl.push_front(dfly);
}

bool flyFish() { // 2개 이상 쌓여있는 어항을 모두 공중부양 시키고 회전
    int size = bowl.front().size(); // 몇칸?
    int height = bowl.size(); // 몇줄?

    if(bowl.back().size()-size < height) { // 공중부양하고 밑에가 더 적으면 안되니까 사이즈 비교
        return false;
    }

    deque<int> dtmp;
    deque<deque<int>> up;
    while(size--) {
        dtmp.clear();
        for(int i=0; i<height; i++) {
            dtmp.push_front(bowl[i].front());
            bowl[i].pop_front();
        }
        up.push_back(dtmp);
    }

    for(int i=0; i<up.size(); i++) {
        tmpbowl.push_back(up[i]);
    }
    for(int i=0; i<bowl.size(); i++) {
        if(bowl[i].empty()) {
            continue;
        }
        tmpbowl.push_back(bowl[i]);
    }
    bowl = tmpbowl;
    tmpbowl.clear();
    return true;
}

bool checkRange(int x,int y,int line) {
    return x>=0 && x<bowl.size() && y>=0 && y<bowl[line].size();
}

void adjustFish() { // 물고기 수 조절
    fill(&adjust[0][0],&adjust[100][101],0);
    int xidx, yidx;
    xidx = 0;
    for(auto bo:bowl) {
        yidx = 0;

        for(auto b:bo) { // 각자 아래, 오른쪽을 봄
            for(int i=0; i<2; i++) {
                int nx = xidx + dx[i];
                int ny = yidx + dy[i];

                if(!checkRange(nx,ny,xidx)) {
                    continue;
                }
                int origin = bowl[xidx][yidx];
                int diff = bowl[nx][ny];
                int d = abs(origin-diff)/5;
                if(d==0) {
                    continue;
                }
                if(origin>diff) {
                    adjust[xidx][yidx] -= d;
                    adjust[nx][ny] += d;
                } else {
                    adjust[xidx][yidx] += d;
                    adjust[nx][ny] -= d;
                }
            }
            ++yidx;
        }

        ++xidx;
    }

    // 적용
    for(int i=0; i<bowl.size(); i++) {
        for(int j=0; j<bowl[i].size(); j++) {
            bowl[i][j] += adjust[i][j];
        }
    }
}

void putdownFish() { // 다시 바닥에 일렬로 내려놓음
    deque<int> tmpdq;
    int loop = bowl.back().size(); // 맨 밑이 제일 사이즈 클 것임
    for(int i=0; i<loop; i++) {
        for(int j=bowl.size()-1; j>=0; j--) {
            if(bowl[j].size()-1>=i) {
                tmpdq.push_back(bowl[j][i]);
            }
        }
    }
    bowl.clear();
    bowl.push_back(tmpdq);
}

void reflyFish() { // n/2개를 공중부양시켜 180도 회전시킨 다음 위에 올려놓기
    int length = bowl.front().size();
    length /= 2;
    tmpbowl.clear();
    int start = bowl.size();
    deque<int> tdq;
    for(int i=start-1; i>=0; i--) {
        for(int j=length-1; j>=0; j--) {
            tdq.push_back(bowl[i][j]);
        }
        for(int j=0; j<length; j++) {
            bowl[i].pop_front();
        }
        tmpbowl.push_back(tdq);
        tdq.clear();
    }
    for(auto bo:bowl) {
        tmpbowl.push_back(bo);
    }
    bowl.clear();
    bowl = tmpbowl;
    tmpbowl.clear();
}

int getGap() { // 가장 많이 들어있는 어항과 가장 적게 들어있는 어항의 물고기 수 차이를 리턴
    int maxFish = 0;
    int minFish = inf;
    for(auto bo:bowl) {
        for(auto b:bo) {
            maxFish = max(maxFish,b);
            minFish = min(minFish,b);
        }
    }
    return abs(maxFish-minFish);
}

void solve() {
    init();
    input();

    while(1) {
        ++answer;
        pushFish();
        flyOneFish();
        while(1) {
            if(!flyFish()) { // 2개 이상 쌓여있는 어항을 모두 공중부양 후 돌림
                break;
            }
        }
        adjustFish();
        putdownFish();
        reflyFish();
        reflyFish();
        adjustFish();
        putdownFish();
        if(getGap()<=k) {
            cout<<answer;
            break;
        }
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    solve();
    return 0;
}
