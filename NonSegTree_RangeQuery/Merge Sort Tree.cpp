int N = 131072;
 
struct SegTree { 
    vvi tree; int n = 0; int def = 0;
    void m(vector<int>& ans, vector<int>& a, vector<int>& b) { 
        int ai = 0, bi = 0;
        while (ai < a.size() || bi < b.size()) {
            if (ai == a.size()) ans.pb(b[bi++]);
            else if (bi == b.size()) ans.pb(a[ai++]);
            else if (a[ai] < b[bi]) ans.pb(a[ai++]);
            else ans.pb(b[bi++]);
        }
    }
    void init(vi& a) {
        n = a.size(); tree.clear(); tree.resize(2*n - 1);  loop(i, 0, n) {  tree[n - 1 + i] = {a[i]}; }
        loopr(i, n - 2, 0) { m(tree[i], tree[2 * i + 1], tree[2 * i + 2]); }
    }
    int query(int a, int b, int l, int r, int node, int val) {
        if (a >= l && b <= r) {
            int ind = lower_bound(tree[node].begin(), tree[node].end(), val) - tree[node].begin();
            return ind;
        }
        else if (a > r || b < l || a > b) { return 0; }
        else { return query(a, (a + b) / 2, l, r, 2 * node + 1, val) + query((a + b) / 2 + 1, b, l, r, 2 * node + 2, val); }
    }
};
