#include <bits/stdc++.h>

using namespace std;

struct point {
    long long x, y;
    int id;
};

bool comp_x(point &a, point &q) {
    return a.x < q.x || (a.x == q.x && a.y < q.y);
}

bool comp_y(const point &a, const point &b) {
    return a.y > b.y;
}

long long dist(const point &a, const point &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

long long sq(point &a, point &b, point &c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

long long mindist;
int ansa, ansb;


void upd_ans(const point &a, const point &b) {
    long long ndist = dist(a, b);
    if (ndist < mindist) {
        mindist = ndist;
        ansa = a.id;
        ansb = b.id;
    }
}

void check(vector<point> &l, vector<point> &r, long long nearX) {
    int cur = 0;
    for (int i = 0; i < l.size(); ++i) {
        point p = l[i];
        if ((p.x - nearX) * (p.x - nearX) < mindist) {
            while (cur < r.size() && r[cur].y > p.y) {
                ++cur;
            }
            int up = cur;
            while (up < r.size() && (p.y - r[up].y) * (p.y - r[up].y) < mindist) {
                ++up;
            }
            for (int j = cur; j < up; ++j) {
                upd_ans(p, r[j]);
            }
        }
    }
}


void rec(vector<point> &points) {
    int n = points.size();

    if (n == 1) {
        return;
    }

    int m = n / 2;
    vector<point> left(m), right(n - m);
    for (int i = 0; i < m; ++i) {
        left[i] = points[i];
    }
    for (int i = 0; i < n - m; ++i) {
        right[i] = points[m + i];
    }

    long long p1 = right.front().x;
    long long p2 = left.back().x;

    rec(left);
    rec(right);

    check(left, right, p1);
    check(right, left, p2);

    merge(left.begin(), left.end(), right.begin(), right.end(), points.begin(), &comp_y);
}

int main() {
    int n;
    cin >> n;

    vector<point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
        points[i].id = i;
    }

    sort(points.begin(), points.end(), comp_x);

    mindist = LLONG_MAX;
    rec(points);

    for (int i = 0; i < n; ++i) {
        if (points[i].id == ansa || points[i].id == ansb) {
            cout << points[i].x << ' ' << points[i].y << ' ';
        }
    }

    return 0;
}

