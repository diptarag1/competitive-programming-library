struct SegTree {
    vector<int> tree; int n = 0; int def = 0; vector<int> lazy;
    int f(int a, int b) { return a + b; }
    void init(vector<int>& a) {
        n = a.size(); 
        tree.resize(2*n-1); lazy.resize(2 * n - 1); loop(i, 0, n) { tree[n - 1 + i] = a[i]; }
        loopr(i, n - 2, 0) { tree[i] = f(tree[2 * i + 1], tree[2 * i + 2]); }
    }
    void lazyrelax(int node, int a, int b) {
        if (lazy[node] != 0) { 
            tree[node] = ((b - a + 1)*((1ll<<31) - 1) - tree[node]);
            if (node < n - 1) { 
                lazy[2 * node + 1] ^= 1; lazy[2 * node + 2] ^= 1;
            } 
            lazy[node] = 0; 
        }
    }
    int query(int a, int b, int l, int r, int node) {
        if(a > b) return def;
        //cout << a << " " << b << "\n";
        lazyrelax(node,a,b);
        if (a >= l && b <= r) return tree[node];
        else if (a > r || b < l) { return def; }
        else { return f(query(a, (a + b) / 2, l, r, 2 * node + 1), query((a + b) / 2 + 1, b, l, r, 2 * node + 2)); }
    }
    void update(int a, int b, int l, int r, int node) {
        if(a > b) return;
        lazyrelax(node,a,b);
        if (a >= l && b <= r) { tree[node] = ((b - a + 1)*((1ll<<31) - 1) - tree[node]); if (node < n - 1) { lazy[2 * node + 1] ^= 1; lazy[2 * node + 2] ^= 1; } return; }
        else if (a > r || b < l) { return; }
        else { update(a, (a + b) / 2, l, r, 2 * node + 1); update((a + b) / 2 + 1, b, l, r, 2 * node + 2); tree[node] = f(tree[2 * node + 1], tree[2 * node + 2]); }
    }
};


/*	
	Query -> s.query(0,N-1,left,right,0);
	Update -> s.update(0,N-1,left,right,0,val);
*/


vector<int> parent, depth, heavy, head, pos;
int N = 131072;
int cur_pos;
SegTree seg;
vector<int> val(N), hold(N);
vector<vector<int>> g(N);

int dfs(int v) {
    int size = 1;
    int max_c_size = 0;
    for (int c : g[v]) {
        if (c != parent[v]) {
            parent[c] = v;
            depth[c] = depth[v] + 1;
            int c_size = dfs(c);
            size += c_size;
            if (c_size > max_c_size)
			{ max_c_size = c_size; heavy[v] = c; }
        }
    }
    return size;
}

void decompose(int v, int h) {
    head[v] = h, hold[cur_pos] = val[v];
    pos[v] = cur_pos++;
    if (heavy[v] != -1) decompose(heavy[v], h);
    for (int c : g[v]) {
        if (c == parent[v] || c == heavy[v]) continue;
        decompose(c, c);
    }
}

int query(int a, int b) {
    int res = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        int cur_sum = seg.query(0,N-1,pos[head[b]], pos[b],0);
        res += cur_sum;
    }
    if (depth[a] > depth[b])
        swap(a, b);
    int last_sum = seg.query(0,N-1,pos[a], pos[b],0);
    res += last_sum;
    return res;
}

void update(int a, int b) {
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        seg.update(0,N-1,pos[head[b]], pos[b],0);
    }
    if (depth[a] > depth[b])
        swap(a, b);
    seg.update(0,N-1,pos[a], pos[b],0);
}

void init() {
    parent.clear(); parent.resize(N);
    depth.clear(); depth.resize(N);
    heavy.clear(); heavy.resize(N, -1);
    head.clear(); head.resize(N);
    pos.clear(); pos.resize(N);
    cur_pos = 0;

    dfs(0);
    decompose(0, 0);
}



void testcases() {
    int n,q; cin>>n>>q;
    loop(i,0,n-1) {
        int x,y; cin>>x>>y;
        x--; y--;
        g[x].pb(y); g[y].pb(x);
    }
    loop(i,0,n) cin>>val[i];

    init();

    seg.init(hold);
    
    while(q--) {
        int type,a,b; cin>>type>>a>>b; a--; b--;
        if(type == 1) {
            update(a,b);
        }
        else {
            cout << query(a,b) << "\n";
        }
    }
    
}     
 
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    /* code */ 
    int t; 
    // cin >> t;
    t = 1;
    loop(i,0,t) testcases();
    /* end code */
}