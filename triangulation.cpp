
#include <bits/stdc++.h>

using namespace std;

struct point {
    long long x, y;
    int id;
};

struct triangle {
    point A, B, C;
};

long long sq(const point &a, const point &b, const point &c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

vector<triangle> triangulation(vector<point> points) {
    vector<triangle> ret;
    int pos = 0;
    point l, r, m;

    while (points.size() > 3) {
        if (pos == 0) {
            l = points[points.size() - 1];
        }
        else {
            l = points[pos-1];
        }

        if (pos == points.size() - 1) {
            r = points[0];
        }
        else {
            r = points[pos+1];
        }
        m = points[pos];

        if (sq(l, m, r) > 0) {
            triangle cur;
            cur.A = l;
            cur.B = m;
            cur.C = r;

            bool ok = true;
            for (int i = 0; i < points.size(); i++) {
                if (points[i].x == l.x && points[i].y == l.y) continue;
                if (points[i].x == m.x && points[i].y == m.y) continue;
                if (points[i].x == r.x && points[i].y == r.y) continue;

                if (sq(cur.A, cur.B, points[i]) > 0 && sq(cur.B, cur.C, points[i]) > 0 && sq(cur.C, cur.A, points[i]) >= 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ret.push_back(cur);
                if (pos > 0) {
                    points.erase(points.begin() + pos);
                    --pos;
                } else {
                    points.erase(points.begin() + pos);
                    pos = points.size() - 1;
                }
            } else {
                pos = (pos + 1) % points.size();
            }
        } else {
            pos = (pos + 1) % points.size();
        }
    }
    triangle X {points[0], points[1], points[2]};
    ret.push_back(X);
    return ret;
}

int main() {
    int n;
    cin >> n;
    vector<point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
        points[i].id = i + 1;
    }
    vector<triangle> ans = triangulation(points);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].A.id << ' ' << ans[i].B.id << ' ' << ans[i].C.id << '\n';
    }

    return 0;
}
