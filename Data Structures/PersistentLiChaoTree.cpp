const int N = 1e5 + 7;
struct Line {
    ll k, d;
    ll eval(ll x) {return k * x + d; }
};

struct PersistentLiChaoTree {
    struct LiChaoNode {
        Line line;
        int l, r;
        LiChaoNode() {
            LiChaoNode({Line({0, numeric_limits<long long>::max() / 2})});
        }
        LiChaoNode(Line line) : line(line), l(0), r(0) {}
    } t[50 * N];

    int T = 1;
    int L, R;
    vector<int> roots = {1};
    static const int inf = 1e9;
    PersistentLiChaoTree(int L = -inf, int R = inf) : L(L), R(R) {}

    void add(Line line) {
        roots.push_back(upd(roots.back(), line, L, R));
    }
    ll query(int x, int i = -1) {
        if(i == -1) i = sz(roots) - 1;
        return Query(roots[i], x, L, R);
    }
    void undo() {
        roots.pop_back();
    }

    int upd(int pre, Line nw, int l, int r) {
        int m = (l+r)>>1;
        int id = ++T;
        t[id].line = t[pre].line;
        Line &line = t[id].line;

        bool lef = nw.eval(l) < line.eval(l);
        bool mid = nw.eval(m) < line.eval(m);
        if(mid) swap(line, nw);
        if(l == r) return id;
        if(lef != mid) {
            if(!t[pre].l) t[id].l = ++T, t[T] = LiChaoNode(nw);
            else t[id].l = upd(t[pre].l, nw, l, m);
            t[id].r = t[pre].r;
        } else {
            if(!t[pre].r) t[id].r = ++T, t[T] = LiChaoNode(nw);
            else t[id].r = upd(t[pre].r, nw, m + 1, r);
            t[id].l = t[pre].l;
        }
        return id;
    }

    ll Query(int cur, int x, int l, int r) {
        ll val = t[cur].line.eval(x);
        int m = (l + r) / 2;
        if(l < r) {
            if(x <= m && t[cur].l) val = min(val, Query(t[cur].l, x, l, m));
            if(x > m && t[cur].r) val = min(val, Query(t[cur].r, x, m + 1, r));
        }
        return val;
    }
};

PersistentLiChaoTree lc(0);