struct Polygon {
    int n;
    vector<pt> pol;
    Polygon(vector<pt> poly = {}) : pol(poly) {
        n = pol.size();
    }

    bool inside(pt p, bool strict = true) { //O(log(n)) convex
        int a = 1, b = n - 1, r = !strict;
        if (n < 3) return r && onSegment(pol[0], pol.back(), p);
        if (sgn(pol[0].cross(pol[a], pol[b])) > 0) swap(a, b);
        if (sgn(pol[0].cross(pol[a], p)) >= r || sgn(pol[0].cross(pol[b], p)) <= -r)
            return false;
        while (abs(a - b) > 1) {
            int c = (a + b) / 2;
            (sgn(pol[0].cross(pol[c], p)) > 0 ? b : a) = c;
        }
        return sgn(pol[a].cross(pol[b], p)) < r;
    }

    bool inPolygon(pt a, bool strict = true) { // O(N) could be non-convex
		int cnt = 0, n = pol.size();
		for(int i=0;i<n;++i) {
			pt q = pol[(i + 1) % n];
			if (onSegment(pol[i], q, a)) return !strict;
			//or: if (segDist(p[i], q, a) <= eps) return !strict;
			cnt ^= ((a.y<pol[i].y) - (a.y<q.y)) * a.cross(pol[i], q) > 0;
		}
		return cnt;
	}
};