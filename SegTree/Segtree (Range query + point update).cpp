struct node{
    ll left, right, pref, suf, store;
    node(int a=0, int b=0,int c=0, int d=0, ll e=0) : left(a), right(b), pref(c), suf(d), store(e) {}
    friend node merge(const node n1, const node n2) {
        ll store = n1.store + n2.store + (n1.right - max(n1.left-1,n1.suf)) * (min(n2.right,n2.pref) - n2.left + 1);
        return node(n1.left,n2.right,min(n2.pref, n1.pref),max(n1.suf, n2.suf),store);
    }
};


template<typename T> 
struct SegTree {
    int N, lg; vector<T> tree;
    SegTree(int n, vector<T>& t) : tree(move(t)), N(n) { 
        lg = 1; ll c = 1; 
        while(c < n) { c<<=1; lg++; } 
        for(int i = N-1; i > 0; i--) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
    }

    inline void turnon(int pos) { 
        tree[pos+N] = {pos, pos, pos, pos, 1};
        pos+=N;
        for(pos>>=1; pos; pos>>=1) tree[pos] = merge(tree[pos<<1], tree[pos<<1|1]);
    }
    
    inline void turnoff(int pos) {
        tree[pos+N] = {pos, pos, N, -1, 1};
        pos+=N; 
        for(pos>>=1; pos; pos>>=1) tree[pos] = merge(tree[pos<<1], tree[pos<<1|1]);
    }

    //Queries [L,R)
    T query(int l, int r) {
        l += N; r += N;
        T res1 = tree[l++];
        if(l == r) return res1;
        T res2 = tree[--r];
        for(; l < r; l>>=1, r>>=1) {
            if(l&1) res1 = merge(res1, tree[l++]);
            if(r&1) res2 = merge(tree[--r], res2);
        } 
        return merge(res1, res2);
    }
};
