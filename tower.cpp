#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
    point operator+(const point& p) const { return {x + p.x, y + p.y}; }
    point operator/(const double d) const { return {x / d, y / d}; }
    point rotate() const { return {y, -x}; }
    point operator-(const point& p) const { return {x - p.x, y - p.y}; }
};

double dist(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct circle {
    point O;
    double R;
};

circle points2circle(const point &a, const point &b) {
    circle ret;
    ret.R = dist(a, b) / 2.0;
    ret.O.x = (a.x + b.x) / 2.0;
    ret.O.y = (a.y + b.y) / 2.0;
    return ret;
}

const double EPS = 1e-7;

bool in(const point &a, const circle &c) {
    return dist(a, c.O) < c.R + EPS;
}

bool IsNOTPerpendicular(const point &a, const point &b, const point &c) {
    double yDelta_a = b.y - a.y;
    double xDelta_a = b.x - a.x;
    double yDelta_b = c.y - b.y;
    double xDelta_b = c.x - b.x;

    if (fabs(xDelta_a) <= EPS && fabs(yDelta_b) <= EPS) {
        return true;
    } else if (fabs(yDelta_a) <= EPS) {
        return false;
    } else if (fabs(yDelta_b) <= EPS) {
        return false;
    } else if (fabs(xDelta_a) <= EPS) {
        return false;
    } else if (fabs(xDelta_b) <= EPS) {
        return false;
    } else true;
}

point CalcCircle(point A, point B, point C, point D) {
    double a = A.y - B.y, b = B.x - A.x;
    double c = - a * A.x - b * A.y;
    double d = sqrt(a*a + b*b);
    a /= d, b /= d, c /= d;

    double a2 = C.y - D.y, b2 = D.x - C.x;
    double c2 = - a2 * C.x - b2 * C.y;
    double d2 = sqrt(a2 *a2 + b2*b2);
    a2 /= d2, b2 /= d2, c2 /= d2;

    return {(c2 * b - c * b2) / (a * b2 - a2 * b),
            (c2 * a - c * a2) / (a2 * b - a * b2)};
}

circle points3circle(point a, point b, point c) {
    point q1 = (a + b) / 2.0;
    point q2 = (a + c) / 2.0;
    point q3 = q1 + (b - a).rotate();
    point q4 = q2 + (c - a).rotate();
    circle ans;
    ans.O = CalcCircle(q1, q3, q2, q4);
    ans.R = dist(a , ans.O);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(20);
    cout << fixed;
    int n;
    cin >> n;
    vector<point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    if (n == 1) {
        cout << 0 << '\n' << points[0].x << ' ' << points[0].y << endl;
        return 0;
    }

    random_shuffle(points.begin(), points.end());
    circle D = points2circle(points[0], points[1]);
    for (int i = 2; i < n; ++i) {
        if (!in(points[i], D)) {
            point q = points[i];
            D = points2circle(points[0], q);

            for (int j = 1; j < i; ++j) {
                if (!in(points[j], D)) {
                    point q1 = points[j];
                    point q2 = q;
                    D = points2circle(q1, q2);
                    for (int k = 0; k < j; k++) {
                        if (!in(points[k], D)) {
                            D = points3circle(points[k], q1, q2);
                        }
                    }
                }
            }
        }
    }
    cout << fixed << setprecision(10);
    cout << D.R << '\n';
    cout << D.O.x << ' ' << D.O.y << '\n';

    return 0;
}
