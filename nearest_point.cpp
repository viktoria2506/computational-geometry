#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
    int id;
};

bool compareY(const point& a, const point& b) {
    return a.y < b.y;
}

bool compareX(const point& a, const point& b) {
    return a.x < b.x;
}

struct qdtree {
    point *tree;
    int n;

    qdtree(point p[], int n): tree(new point[n]), n(n) {
        copy(p, p + n, tree);
        buildy(0, n);
    }
    void buildx(int l, int r) {
        if (l >= r) {
            return;
        }
        nth_element(tree + l, tree + (l + r) / 2, tree + r, compareX);
        buildy(l, (l + r) / 2);
        buildy((l + r) / 2 + 1, r);
    }

    void buildy(int l, int r) {
        if (l >= r) {
            return;
        }
        nth_element(tree + l, tree + (l + r) / 2, tree + r, compareY);
        buildx(l, (l + r) / 2);
        buildx((l + r) / 2 + 1, r);
    }

    priority_queue<pair<double, point*>> pq;

    void calcx(point p, int k, int l, int r) {
        if (l >= r) {
            return;
        }
        int mid = (l + r) / 2;
        double dy = p.y - tree[mid].y;
        double dx = p.x - tree[mid].x;
        double dist = dx * dx + dy * dy;

        if (pq.size() < k || dist < pq.top().first) {
            pq.push(make_pair(dist, &tree[mid]));
            if (pq.size() > k) {
                pq.pop();
            }
        }
        if (dx > 0) {
            calcy(p, k, mid + 1, r);
            if (dx * dx < pq.top().first || pq.size() < k) {
                calcy(p, k, l, mid);
            }
        } else {
            calcy(p, k, l, mid);
            if (dx * dx < pq.top().first || pq.size() < k) {
                calcy(p, k, mid + 1, r);
            }
        }
    }

    void calcy(point p, int k, int l, int r) {
        if (l >= r) {
            return;
        }
        int mid = (l + r) / 2;
        double dy = p.y - tree[mid].y;
        double dx = p.x - tree[mid].x;
        double dist = dx * dx + dy * dy;
        if (pq.size() < k || dist < pq.top().first) {
            pq.push(make_pair(dist, &tree[mid]));
            if (pq.size() > k) {
                pq.pop();
            }
        }
        if (dy > 0) {
            calcx(p, k, mid + 1, r);
            if (dy * dy < pq.top().first || pq.size() < k) {
                calcx(p, k, l, mid);
            }
        } else {
            calcx(p, k, l, mid);
            if (dy * dy < pq.top().first || pq.size() < k) {
                calcx(p, k, mid + 1, r);
            }
        }
    }

};

int main(){
    int n, m;
    cin >> n >> m;
    point p[n];
    for(int i = 0; i < n; i++){
        cin >> p[i].x >> p[i].y;
        p[i].id = i + 1;
    }

    qdtree x(p,n);
    for (int i = 0; i < m; ++i) {
        point t;
        cin >> t.x >> t.y;

        x.calcy(t, 1, 0, n);
        vector<point> ans;
        while (!x.pq.empty()) {
            ans.push_back(*x.pq.top().second);
            x.pq.pop();
        }
        reverse(ans.begin(), ans.end());

        for (auto &an : ans) {
            cout << an.id << '\n';
        }
    }
}
