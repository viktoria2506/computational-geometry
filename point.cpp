#include <bits/stdc++.h>

using namespace std;

struct point {
    long long x, y;
};

long long sq(point &a, point &b, point &c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

bool border(point q, pair<point, point> p) {
    point p1 = p.first;
    point p2 = p.second;
    return sq(p1, p2, q) == 0;
}

int get(point q, pair<point, point> p) {
    point p1 = p.first;
    point p2 = p.second;
    int ans = 0;
    if (p1.y == p2.y) {
        ans = 0;
    }
    else if (q.y == max(p1.y, p2.y) && q.x < min(p1.x, p2.x)) {
        ans = 1;
    }
    else if (q.y == min(p1.y, p2.y)) {
        ans = 0;
    }
    else if (p1.y > p2.y) {
        swap(p1, p2);
    }
    if (q.y <= p1.y || q.y > p2.y) {
        ans = 0;
    }
    else if (sq(p1, p2, q) > 0) {
        ans = 1;
    }
    return ans;
}


int main() {
    int n;
    cin >> n;
    vector<point> points(n);

    point q;
    cin >> q.x >> q.y;

    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    vector<pair<point, point>> segments(n);
    for (int i = 0; i < n; ++i) {
        segments[i] = {points[i], points[(i + 1)%n]};
    }

    for (auto segment : segments) {
        if (border(q, segment)) {
            cout << "YES";
            return 0;
        }
    }

    int cnt = 0;
    for (auto segment : segments) {
        cnt += get(q, segment);
    }
    if (cnt & 1) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}

