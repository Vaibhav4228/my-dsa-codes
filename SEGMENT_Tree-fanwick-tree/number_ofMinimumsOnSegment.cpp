//this question is give in codeforces
//questions - https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 2;
pair<int, int> tree[4 * N];
int a[N];

void build(int node, int st, int en) {
    if (st == en) {
        tree[node] = {a[st], 1};
        return;
    }
    int mid = (st + en) / 2;
    build(2 * node, st, mid);
    build(2 * node + 1, mid + 1, en);
    if (tree[2 * node].first < tree[2 * node + 1].first) {
        tree[node] = tree[2 * node];
    } else if (tree[2 * node + 1].first < tree[2 * node].first) {
        tree[node] = tree[2 * node + 1];
    } else {
        tree[node].first = tree[2 * node].first;
        tree[node].second = tree[2 * node].second + tree[2 * node + 1].second;
    }
}

pair<int, int> query(int node, int st, int en, int l, int r) {
    if (st > r || en < l) return {LLONG_MAX, 0}; // Return a default pair if out of range
    if (l <= st && en <= r) return tree[node];
    int mid = (st + en) / 2;
    auto q1 = query(2 * node, st, mid, l, r);
    auto q2 = query(2 * node + 1, mid + 1, en, l, r);
    if (q1.first <= q2.first) return q1; // Changed comparison to handle equal values
    return q2;
}

void update(int node, int st, int en, int idx, int val) {
    if (st == en) {
        a[idx] = val;
        tree[node] = {a[st], 1};
        return;
    }
    int mid = (st + en) / 2;
    if (idx <= mid) {
        update(2 * node, st, mid, idx, val);
    } else {
        update(2 * node + 1, mid + 1, en, idx, val);
    }
    if (tree[2 * node].first < tree[2 * node + 1].first) {
        tree[node] = tree[2 * node];
    } else if (tree[2 * node + 1].first < tree[2 * node].first) {
        tree[node] = tree[2 * node + 1];
    } else {
        tree[node].first = tree[2 * node].first;
        tree[node].second = tree[2 * node].second + tree[2 * node + 1].second;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build(1, 0, n - 1);
    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            int idx, val;
            cin >> idx >> val;
            update(1, 0, n - 1, idx, val);
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            auto ans = query(1, 0, n - 1, l, r - 1);
            cout << ans.first << " " << ans.second << endl;
        }
    }
    return 0;
}
