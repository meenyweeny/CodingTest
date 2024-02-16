#include<iostream>
using namespace std;

const int nodesize = 1e6 + 1;
int n, m, k;
long long tree[nodesize << 2];
int unit;

void get_unit() {
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
    get_unit();
    for (int i = 0; i < n; i++) {
        cin >> tree[unit + i];
    }
}

void build() {
    for (int i = unit - 1; i >= 1; i--) {
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
}

void update(int index, long long value) {
    --index;
    index += unit;
    long long gap = value - tree[index];
    while (index > 0) {
        tree[index] += gap;
        index /= 2;
    }
}

long long query(int start, int end) {
    long long sum = 0;
    --start; --end; start += unit; end += unit;
    while (start <= end) {
        if (start % 2) {
            sum += tree[start];
            ++start;
        }
        if (!(end % 2)) {
            sum += tree[end];
            --end;
        }
        start /= 2;
        end /= 2;
    }
    return sum;
}

void solve() {
    input();
    build();
    m += k;
    int cmd;
    long long a, b;
    while (m--) {
        cin >> cmd;
        cin >> a >> b;
        if (cmd == 1) {
            update(a, b);
        } else {
            cout << query(a, b) << '\n';
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
