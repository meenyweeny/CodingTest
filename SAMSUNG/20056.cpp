#include<iostream>
#include<vector>
using namespace std;

struct info {
	int x, y;
	int weight, dir, speed;
};

int n, m, k;
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };
vector<info> ball;
vector<info> tmp;
vector<int> map[52][52];

void input() {
	cin >> n >> m >> k;
	int r, c, wei, dir, speed;
	for (int i = 0; i < m; i++) {
		cin >> r >> c >> wei >> speed >> dir;
		--r;
		--c;
		ball.push_back({ r,c,wei,dir,speed });
	}
}

int getAnswer() {
	int answer = 0;
	int size = ball.size();
	for (int i = 0; i < size; i++) {
		answer += ball[i].weight;
	}
	return answer;
}

pair<int, int> getNextPos(int x, int y, int nd, int ns) {
	x += (dx[nd] * ns);
	y += (dy[nd] * ns);
	while (1) {
		if (x >= 0 && x < n) {
			break;
		}
		if (x >= n) {
			x -= n;
		} else {
			x += n;
		}
	}
	while (1) {
		if (y >= 0 && y < n) {
			break;
		}
		if (y >= n) {
			y -= n;
		} else {
			y += n;
		}
	}
	return { x,y };
}

void moveBall() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j].clear();
		}
	}
	tmp.clear();
	int size = ball.size();
	for (int i = 0; i < size; i++) {
		info now = ball[i];
		pair<int, int> next = getNextPos(now.x, now.y, now.dir, now.speed);
		map[next.first][next.second].push_back(i);
	}
}

void separateBall() {
	tmp.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int size = map[i][j].size();
			if (size == 0) {
				continue;
			}
			if (size == 1) {
				int index = map[i][j][0];
				tmp.push_back({ i,j,ball[index].weight, ball[index].dir, ball[index].speed});
				continue;
			}

			int odd, pos, weight, speed;
			odd = pos = weight = speed = 0;
			for (int q = 0; q < size; q++) {
				int index = map[i][j][q];
				odd += ((ball[index].dir % 2) == 1);
				pos += ((ball[index].dir % 2) == 0);
				weight += ball[index].weight;
				speed += ball[index].speed;
			}
			weight /= 5;
			speed /= size;
			if (weight == 0) {
				continue;
			}
			int newDir;
			if (odd == 0 || pos == 0) {
				newDir = 0;
			} else {
				newDir = 1;
			}
			for (int nxt = 0; nxt < 4; nxt++) {
				tmp.push_back({ i,j, weight, newDir, speed});
				newDir += 2;
			}
		}
	}

	ball.clear();
	ball = tmp;
	tmp.clear();
}

void solve() {
	input();
	while (k--) {
		moveBall();
		separateBall();
	}
	cout<<getAnswer();
}

int main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios_base::sync_with_stdio(false);

	solve();
	return 0;
}
