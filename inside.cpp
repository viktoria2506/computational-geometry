#include <bits/stdc++.h>

using namespace std;

struct point {
    long long x, y;
};

long long sq(point &a, point &b, point &c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

long long dist(point &a, point &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
    int n;
    cin >> n;
    vector<point> points(n);

    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    int j = 0;
    int zero_id = 0;

    while (sq(points[j], points[j + 1], points[j + 2]) == 0) {
        ++j;
    }
    if (sq(points[j], points[j + 1], points[j + 2]) < 0) {
        reverse(points.begin(), points.end());
    }


    for (int i = 0; i < n; ++i) {
        if (points[i].x < points[zero_id].x || (points[i].x == points[zero_id].x && points[i].y < points[zero_id].y)) {
            zero_id = i;
        }
    }

    rotate(points.begin(), points.begin() + zero_id, points.end());

    point zero = points[0];

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        point q;
        cin >> q.x >> q.y;
        string ans = "OUTSIDE";
        if (q.x >= zero.x) {
            if (q.x == zero.x && q.y == zero.y) {
                ans = "BORDER";
            } else if (sq(zero, points[n - 1], q) <= 0 && sq(zero, points[1], q) >= 0) {
                int p1;
                int l = 1;
                int r = n - 1;
                while (true) {
                    if (l == r) {
                        p1 = l;
                        break;
                    }
                    if (l + 1 == r) {
                        if (sq(zero, points[r], q) >= 0) {
                            p1 = r;
                        } else {
                            p1 = l;
                        }
                        break;
                    }
                    int mid = (l + r) / 2;
                    if (sq(zero, points[mid], q) >= 0) {
                        l = mid;
                    } else {
                        r = mid;
                    }
                }

                if (sq(zero, points[p1], q) == 0) {
                    long long d1 = dist(zero, points[p1]);
                    long long d2 = dist(zero, q);
                    if (d1 == d2) {
                        ans = "BORDER";
                    } else if (d2 > d1) {
                    } else if (p1 == 1 || p1 == n - 1) {
                        ans = "BORDER";
                    } else {
                        ans = "INSIDE";
                    }
                } else if (sq(points[p1], points[p1 + 1], q) > 0) {
                    ans = "INSIDE";
                } else if (sq(points[p1], points[p1 + 1], q) == 0) {
                    ans = "BORDER";
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}


