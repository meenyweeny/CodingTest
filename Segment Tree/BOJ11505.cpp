#include<iostream>
using namespace std;

const int mod = 1e9 + 7;
const int nodesize = 1e6 + 1;
unsigned long long tree[nodesize << 2];
int n, m, k;
int unit;

void getUnit() {
    unit = 2;
    while (1) {
        if (unit >= n) {
            break;
        }
        unit *= 2;
    }
}

void input() {
    cin >> n >> m >> k;
    getUnit();
    fill(tree, tree + (nodesize << 2), 1);
    for (int i = 0; i < n; i++) {
        cin >> tree[i+unit];
    }
}

void buildTree() {
    for (int i = unit - 1; i > 0; i--) {
        tree[i] = (tree[i * 2] * tree[i * 2 + 1]);
        tree[i] %= mod;
    }
}

void update(int index, int value) {
    --index; index += unit;
    unsigned long long before = tree[index];
    tree[index] = value;
    index /= 2;
    while (index > 0) {
        tree[index] = tree[index * 2] * tree[index * 2 + 1];
        tree[index] %= mod;
        index /= 2;
    }
}

unsigned long long query(int start, int end) {
    unsigned long long answer = 1;
    if (start > end) swap(start, end);
    start--; end--; start += unit; end += unit;
    while (start <= end) {
        if (start % 2) {
            answer *= tree[start];
            answer %= mod;
            ++start;
        }
        if (!(end % 2)) {
            answer *= tree[end];
            answer %= mod;
            --end;
        }
        start /= 2;
        end /= 2;
    }
    return answer;
}

void solve() {
    input();
    buildTree();
    int cmd, b, c;
    m += k;
    while (m--) {
        cin >> cmd >> b >> c;
        if (cmd == 1) {
            update(b, c);
        } else {
            cout << query(b, c) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
