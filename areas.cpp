#include <bits/stdc++.h>

using namespace std;

struct Point {
    long double x, y;

    Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }

    Point operator+(const Point &p) const { return {x + p.x, y + p.y}; }

    Point operator*(const long double d) const { return {x * d, y * d}; }

    long double operator*(const Point &p) const { return x * p.x + y * p.y; }

    long double operator^(const Point &p) const { return x * p.y - y * p.x; }
};

struct Fraction {
    long long a, b;

    Fraction(long long _a = 0, long long _b = 1) : a(_a), b(_b) {
        if (b < 0) {
            a = -a, b = -b;
        }
    }

    Fraction operator*(long long t) const {
        return {a * t, b};
    }

    Fraction operator+(const Fraction &f) const {
        return {a + f.a, b};
    }

    Fraction operator+(long long t) const {
        return {a + t * b, b};
    }

};

bool zin(const Point &a, const Point &c) {
    return (a.x - c.x) < c.y;
}

struct Plane {
    long long a, b, c;
    long double da, db, dc, dd;

    Plane(long long a = 0, long long b = 0, long long c = 0) : a(a), b(b), c(c) {
        dd = hypotl(a, b);
        da = a / dd;
        db = b / dd;
        dc = c / dd;
    }

    int half() const {
        return b > 0 || (b == 0 && a > 0) ? 1 : 2;
    }

    bool operator<(const Plane &p) const {
        if (half() != p.half()) {
            return half() < p.half();
        }
        long long cp = a * p.b - b * p.a;
        if (cp != 0) {
            return cp > 0;
        }
        return dc < p.dc;
    }

    bool operator==(const Plane &p) const {
        return a == p.a && b == p.b && c == p.c;
    }

    bool is_cross(const Plane &p1, const Plane &p2) const {
        Fraction x(p2.c * p1.b - p1.c * p2.b, p1.a * p2.b - p2.a * p1.b);
        Fraction y(p2.c * p1.a - p1.c * p2.a, p2.a * p1.b - p1.a * p2.b);
        Fraction res = x * a + y * b + c;
        return res.a > 0;
    }

    Point operator^(const Plane &p) const {
        return {(p.dc * db - dc * p.db) / (da * p.db - p.da * db),
                (p.dc * da - dc * p.da) / (p.da * db - da * p.db)};
    }
};

bool IsNOTPerpendicular(const Point &a, const Point &b, const Point &c) {
    double yDelta_a = b.y - a.y;
    double xDelta_a = b.x - a.x;
    double yDelta_b = c.y - b.y;
    double xDelta_b = c.x - b.x;

    if (fabs(xDelta_a) <= 0 && fabs(yDelta_b) <= 0) {
        return true;
    } else if (fabs(yDelta_a) <= 0) {
        return false;
    } else if (fabs(yDelta_b) <= 0) {
        return false;
    } else if (fabs(xDelta_a) <= 0) {
        return false;
    } else if (fabs(xDelta_b) <= 0) {
        return false;
    } else true;
}

bool in(const Point &a, const Point &c) {
    return (a.x - c.x) < c.y;
}

bool equal_planes(const Plane &p1, const Plane &p2) {
    long long dp = p1.a * p2.a + p1.b * p2.b;
    long long cp = p1.a * p2.b - p1.b * p2.a;
    return cp == 0 && dp > 0;
}

const long long C = 1000000000;
const int N = 1000000;

vector<Plane> planes;
vector<Plane> borders;
Plane inter[N];
vector<Point> polygon;

int main() {
    borders.push_back(Plane(1, 0, C));
    borders.push_back(Plane(-1, 0, C));
    borders.push_back(Plane(0, 1, C));
    borders.push_back(Plane(0, -1, C));

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        planes.push_back(Plane(a, b, c));
    }
    planes.insert(planes.end(), borders.begin(), borders.end());

    sort(planes.begin(), planes.end());

    n = unique(planes.begin(), planes.end(), equal_planes) - planes.begin();
    planes.resize(n);

    int l = 0, r = 0;

    for (auto &p : planes) {
        while (r - l > 1 && !p.is_cross(inter[r - 1], inter[r - 2])) {
            --r;
        }
        while (r - l > 1 && !p.is_cross(inter[l], inter[l + 1])) {
            ++l;
        }
        if (r - l > 0 && inter[r - 1].a * p.b - inter[r - 1].b * p.a <= 0) {
            cout << "0";
            return 0;
        }
        if (r - l < 2 || inter[l].is_cross(p, inter[r - 1]))
            inter[r++] = p;
    }

    inter[r] = inter[l];
    for (int i = l; i < r; i++) {
        polygon.push_back(inter[i] ^ inter[i + 1]);
    }

    for (int i = 0; i < polygon.size(); i++) {
        if (fabsl(polygon[i].x) > C / 2 || fabsl(polygon[i].y) > C / 2) {
            cout << "-1";
            return 0;
        }
    }

    int m = polygon.size();
    polygon.push_back(polygon[0]);
    long double S = 0;
    for (int i = 0; i < m; ++i) {
        S += polygon[i] ^ polygon[i + 1];
    }
    S = fabsl(S) / 2.0;
    cout.precision(20);
    cout << fixed << S;
    return 0;
}

