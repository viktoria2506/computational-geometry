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

pair<long long, long long> sum(pair<long long, long long> a, pair<long long, long long> b) {
    return {a.first + b.first, a.second};
}

pair<long long, long long> sum(pair<long long, long long> a, long long b) {
    return {a.first + b * a.second, a.second};
}
pair<long long, long long> mult(pair<long long, long long> a, long long b) {
    return {a.first * b, a.second};
}

struct Plane {
    long long a, b, c;
    long double da, db, dc, dd;

    Plane(long long a = 0, long long b = 0,long long c = 0) : a(a), b(b), c(c) {
        dd = sqrt ((a*a)+(b*b));
        da = a / dd;
        db = b / dd;
        dc = c / dd;
    }

    bool operator<(const Plane &p) const {
        int a1 = 2;
        int a2 = 2;
        if ((b > 0 || (b == 0 && a > 0))) {
            a1 = 1;
        }
        if (p.b > 0 || (p.b == 0 && p.a > 0)) {
            a2 = 1;
        }
        if (a1 != a2) {
            return a1 < a2;
        }
        long long cp = a * p.b - b * p.a;
        if (cp != 0) {
            return cp > 0;
        }
        return dc < p.dc;
    }
    bool operator==(const Plane& p) const {
        return a == p.a && b == p.b && c == p.c;
    }

};

Point cross (Plane q, Plane p){
    return {(p.dc * q.db - q.dc * p.db) / (q.da * p.db - p.da * q.db),
            (p.dc * q.da - q.dc * p.da) / (p.da * q.db - q.da * p.db)};
}

bool in(const Point &a, const Point &c) {
    return (a.x - c.x) < c.y;
}

bool is_cross(const Plane &p, const Plane &p1, const Plane &p2) {
    pair <long long, long long> x(p2.c * p1.b - p1.c * p2.b, p1.a * p2.b - p2.a * p1.b);
    if (x.second < 0){
        x.second = -x.second;
        x.first = -x.first;
    }
    pair <long long, long long> y(p2.c * p1.a - p1.c * p2.a, p2.a * p1.b - p1.a * p2.b);
    if (y.second < 0){
        y.second = -y.second;
        y.first = -y.first;
    }
    pair <long long, long long> res;

    res = sum(sum(mult(x, p.a) , mult(y, p.b)),p.c);
    if (res.second < 0){
        res.second = -res.second;
        res.first = -res.first;
    }
    return res.first > 0;
}

const long long C = 1000000000;
const int N = 1000000;


vector<Plane> planes;
vector<Plane> borders;
Plane inter[N];
vector<Point> polygon;

int main() {
    borders.emplace_back(1, 0, C);
    borders.emplace_back(-1, 0, C);
    borders.emplace_back(0, 1, C);
    borders.emplace_back(0, -1, C);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        planes.emplace_back(a, b, c);
    }
    planes.insert(planes.end(), borders.begin(), borders.end());

    sort(planes.begin(), planes.end());

    n = unique(planes.begin(), planes.end(), [](Plane p1, Plane p2) {
        long long dp = p1.a * p2.a + p1.b * p2.b;
        long long cp = p1.a * p2.b - p1.b * p2.a;
        return cp == 0 && dp > 0;
    }) - planes.begin();
    planes.resize(n);

    int l = 0, r = 0;
    for (auto& p : planes) {
        while (r - l > 1 && !is_cross(p, inter[r - 1], inter[r - 2])) {
            --r;
        }
        while (r - l > 1 && !is_cross(p, inter[l], inter[l + 1])) {
            ++l;
        }

        if (r - l > 0 && inter[r - 1].a * p.b - inter[r - 1].b * p.a <= 0) {
            cout << "0";
            return 0;
        }
        if (r - l < 2 || is_cross(inter[l], p, inter[r - 1]))
            inter[r++] = p;
    }

    inter[r] = inter[l];
    for (int i = l; i < r; i++) {
        polygon.push_back(cross(inter[i], inter[i + 1]));
    }

    for (auto & i : polygon) {
        if (fabsl(i.x) > C / 2 || fabsl(i.y) > C / 2) {
            cout << "-1";
            return 0;
        }
    }

    int m = polygon.size();
    polygon.push_back(polygon[0]);

    long double S = 0;
    for (int i = 0; i < m; ++i) {
        S += (polygon[i].x * polygon[i + 1].y - polygon[i].y * polygon[i + 1].x);
    }
    S = fabsl(S) / 2.0;

    cout.precision(20);
    cout << fixed << S;

    return 0;
}

