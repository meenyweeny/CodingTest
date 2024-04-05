#include<iostream>
#include<vector>
using namespace std;

struct info {
    int dx,dy;
    int per;
};

const int mapsize = 502;
int board[mapsize][mapsize];
int n;
vector<info> spreadinfo[4];
int dir = 0;
pair<int,int> now;
int answer;

bool checkRange(int x,int y) {
    return x>=0 && x<n && y>=0 && y<n;
}

void setting() {
    spreadinfo[0].push_back({0,-1,0}); //y
    spreadinfo[0].push_back({0,-2,0}); //a
    spreadinfo[0].push_back({-1,0,1});
    spreadinfo[0].push_back({1,0,1});
    spreadinfo[0].push_back({-2,-1,2});
    spreadinfo[0].push_back({2,-1,2});
    spreadinfo[0].push_back({-1,-1,7});
    spreadinfo[0].push_back({1,-1,7});
    spreadinfo[0].push_back({-1,-2,10});
    spreadinfo[0].push_back({1,-2,10});
    spreadinfo[0].push_back({0,-3,5});

    spreadinfo[1].push_back({1,0,1});
    spreadinfo[1].push_back({2,0,1});
    spreadinfo[1].push_back({0,-1,1});
    spreadinfo[1].push_back({0,1,1});
    spreadinfo[1].push_back({1,-2,2});
    spreadinfo[1].push_back({1,2,2});
    spreadinfo[1].push_back({1,-1,7});
    spreadinfo[1].push_back({1,1,7});
    spreadinfo[1].push_back({2,-1,10});
    spreadinfo[1].push_back({2,1,10});
    spreadinfo[1].push_back({3,0,5});

    spreadinfo[2].push_back({0,1,1});
    spreadinfo[2].push_back({0,2,1});
    spreadinfo[2].push_back({-1,0,1});
    spreadinfo[2].push_back({1,0,1});
    spreadinfo[2].push_back({-2,1,2});
    spreadinfo[2].push_back({2,1,2});
    spreadinfo[2].push_back({-1,1,7});
    spreadinfo[2].push_back({1,1,7});
    spreadinfo[2].push_back({-1,2,10});
    spreadinfo[2].push_back({1,2,10});
    spreadinfo[2].push_back({0,3,5});

    spreadinfo[3].push_back({-1,0,1});
    spreadinfo[3].push_back({-2,0,1});
    spreadinfo[3].push_back({0,-1,1});
    spreadinfo[3].push_back({0,1,1});
    spreadinfo[3].push_back({-1,1,7});
    spreadinfo[3].push_back({-1,-1,7});
    spreadinfo[3].push_back({-1,-2,2});
    spreadinfo[3].push_back({-1,2,2});
    spreadinfo[3].push_back({-2,-1,10});
    spreadinfo[3].push_back({-2,1,10});
    spreadinfo[3].push_back({-3,0,5});
}
void input() {
    cin>>n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin>>board[i][j];
        }
    }
}

void solve() {
    input();
    setting();

    now = {n/2,n/2};

    int during = 1; // 그 방향으로 몇 칸 이동해야 하는지
    int count = 0; // 그 방향으로 몇 칸을 이동했는지
    int hop = 0;
    while(1) {
        if(now.first == 0 && now.second == 0) {
            break;
        }
        const pair<int,int> nxt = {now.first + spreadinfo[dir][0].dx,
                                   now.second + spreadinfo[dir][0].dy};
        const pair<int,int> goal = {now.first + spreadinfo[dir][1].dx,
                                    now.second+spreadinfo[dir][1].dy};
        int sum = 0;
        int origin = board[nxt.first][nxt.second];
        int size = spreadinfo[dir].size();
        for(int i=2; i<size; i++) {
            int nx = now.first + spreadinfo[dir][i].dx;
            int ny = now.second + spreadinfo[dir][i].dy;
            int percent = spreadinfo[dir][i].per;

            int move = origin * 0.01 * percent;
            sum += move;
            if(checkRange(nx,ny)) {
                board[nx][ny] += move;
            } else {
                answer += move;
            }
        }
        board[nxt.first][nxt.second] = 0;
        if(checkRange(goal.first, goal.second)) {
            board[goal.first][goal.second] += (origin-sum);
        } else {
            answer += (origin-sum);
        }

        now = nxt;
        ++count;
        if(count==during) {
            count = 0;
            ++dir;
            dir%=4;
            ++hop;
            if(hop==2) {
                hop = 0;
                ++during;
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
