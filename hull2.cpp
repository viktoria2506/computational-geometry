#include <bits/stdc++.h>

using namespace std;

struct point {
    long long x;
    long long y;
    point (long long nx = 0, long long ny = 0): x(nx), y(ny) {
    }
    bool operator< (const point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

bool clockwise (point a, point b, point c) {
    return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) < 0;
}

bool counter_clockwise (point a, point b, point c) {
    return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) > 0;

}

int main() {
    int N;
    cin >> N;
    vector<point> a(0);
    for (int i = 0; i < N; i++) {
        long long x, y;
        cin >> x >> y;
        a.emplace_back(x,y);
    }
    sort(a.begin(), a.end());
    point left = a[0];
    point right = a[N-1];
    vector <point> top(0);
    top.push_back(left);
    vector <point> lower(0);
    lower.push_back(left);
    for (int i = 1; i < N; i++) {
        if (i == N - 1 || counter_clockwise(left, a[i], right)) {
            while (!counter_clockwise(lower[lower.size() - 2], lower[lower.size() - 1], a[i]) && lower.size() >= 2 ) {
                lower.pop_back();
            }
            lower.push_back(a[i]);
        }
        if (i == N - 1 || clockwise(left, a[i], right)) {
            while (top.size() >= 2 && !clockwise(top[top.size() - 2], top[top.size() - 1], a[i])) {
                top.pop_back();
            }
            top.push_back(a[i]);
        }
    }
    vector<point> ans(0);
    for (auto i : top) {
        ans.push_back(i);
    }
    for (int i = lower.size() - 2; i > 0; --i) {
        ans.push_back(lower[i]);
    }
    cout << ans.size() << '\n';
    for (auto p : ans) {
        cout << p.x << ' ' << p.y << '\n';
    }
}
