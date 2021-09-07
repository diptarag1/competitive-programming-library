int N = 131072;

struct SegTree {
    vector<int> tree; int n = 0; int def = 0; vector<int> lazy;
    int f(int a, int b) { return a + b; }
    void init(vector<int>& a) {
        n = a.size(); tree.clear(); lazy.clear();
        tree.resize(2*n-1); lazy.resize(2 * n - 1); loop(i, 0, n) { tree[n - 1 + i] = a[i]; }
        loopr(i, n - 2, 0) { tree[i] = f(tree[2 * i + 1], tree[2 * i + 2]); }
    }
    void lazyrelax(int node, int a, int b) {
        if (lazy[node] != 0) { 
            tree[node] += (b - a + 1)*lazy[node];
            if (node < n - 1) { 
                lazy[2 * node + 1] += lazy[node]; lazy[2 * node + 2] += lazy[node];
            } 
            lazy[node] = 0; 
        }
    }
    int query(int a, int b, int l, int r, int node) {
        //cout << a << " " << b << "\n";
        lazyrelax(node,a,b); 
        if (a >= l && b <= r) return tree[node];
        else if (a > r || b < l || a > b) { return def; }
        else { return f(query(a, (a + b) / 2, l, r, 2 * node + 1), query((a + b) / 2 + 1, b, l, r, 2 * node + 2)); }
    }
    void update(int a, int b, int l, int r, int node, int val) {
        lazyrelax(node,a,b);
        if (a >= l && b <= r) { tree[node] += (b - a + 1)*val; if (node < n - 1) { lazy[2 * node + 1] += val; lazy[2 * node + 2] += val; } return; }
        else if (a > r || b < l || a > b) { return; }
        else { update(a, (a + b) / 2, l, r, 2 * node + 1, val); update((a + b) / 2 + 1, b, l, r, 2 * node + 2, val); tree[node] = f(tree[2 * node + 1], tree[2 * node + 2]); }
    }
};


/*	
	Query -> s.query(0,N-1,left,right,0);
	Update -> s.update(0,N-1,left,right,0,val);
*/