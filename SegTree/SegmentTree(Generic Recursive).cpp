//Data node
struct node{
    ll val;
    node(ll a=0) :val(a) {}
    friend node merge(const node& n1, const node& n2) {
        return node(max(n1.val, n2.val));
    }
};

//Update node
struct lnode {
    ll val;
    lnode(ll a = 0) : val(a) {}
    friend node merge1(const node& n1, const lnode& n2) {
        return node( n1.val + n2.val );
    }
    friend lnode merge2(const lnode& n1, const lnode& n2) {
        return lnode( n1.val + n2.val ); 
    }
};

template<typename T, typename U>
struct SegTree {
    vector<T> tree; vector<U> lazy; int n = 0; T def = T();
    void init(vector<T>& a) {
        n = a.size(); tree.resize(2*n-1); lazy.resize(2 * n - 1); 
        loop(i, 0, n) { tree[n - 1 + i] = a[i]; } 
        loopr(i, n - 2, 0) { tree[i] = merge(tree[2 * i + 1], tree[2 * i + 2]); }
    }
    void lazyrelax(int node, int a, int b) {
            tree[node] = merge1(tree[node], lazy[node]);
            if (node < n - 1) { 
                lazy[2 * node + 1] = merge2(lazy[2*node+1], lazy[node]); 
                lazy[2 * node + 2] = merge2(lazy[2*node+2], lazy[node]); 
            } 
            lazy[node] = U(); 
    }
    T query(int a, int b, int l, int r, int node) {
        lazyrelax(node,a,b); 
        if (a >= l && b <= r) return tree[node];
        else if (a > r || b < l || a > b) { return def; }
        else { return merge(query(a, (a + b) / 2, l, r, 2 * node + 1), query((a + b) / 2 + 1, b, l, r, 2 * node + 2)); }
    }
    void update(int a, int b, int l, int r, int node, U val) {
        lazyrelax(node,a,b);
        if (a >= l && b <= r) { 
            tree[node] = merge1(tree[node], val); 
            if (node < n - 1) { lazy[2 * node + 1] = merge2(lazy[2*node+1],val); lazy[2 * node + 2] = merge2(lazy[2*node+2],val); } 
            return; 
        }
        else if (a > r || b < l || a > b) { return; }
        else { 
            update(a, (a + b) / 2, l, r, 2 * node + 1, val); 
            update((a + b) / 2 + 1, b, l, r, 2 * node + 2, val); 
            tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]); 
        }
    }
};
