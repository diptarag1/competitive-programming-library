//Data node
struct node{
    int l,r; mint a;
    node(int l=0, int r=0, mint aa=0) : l(l), r(r), a(aa) {}
    friend node merge(const node& n1, const node& n2) {
        return node(n1.l, n2.r, n1.a + n2.a);
    }
};

//Update node
struct lnode {
    mint mult, add;
    lnode(mint aa=1, mint bb=0) : mult(aa), add(bb) {}
    friend node merge1(const node& n1, const lnode& n2) {
        return node( n1.l, n1.r, n2.mult*n1.a + n2.add*(n1.r - n1.l + 1) );
    }
    friend lnode merge2(const lnode& n1, const lnode& n2) {
        return lnode( n1.mult*n2.mult, n1.add*n2.mult+n2.add ); 
    }
};


template<typename T, typename U> 
struct SegTree {
    int N, lg; vector<T> tree; vector<U> lazy;
    SegTree(int n, vector<T>& t, vector<U>& l) : tree(move(t)), lazy(move(l)), N(n) { 
        lg = 1; ll c = 1; 
        while(c < n) { c<<=1; lg++; } 
        for(int i = N-1; i > 0; i--) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
    }

    void modify(int pos, U val) {
        tree[pos] = merge1(tree[pos], val);
        if(pos < N) lazy[pos] = merge2(lazy[pos], val);
    }

    //Builds all parents of pos from bottom
    inline void build(int pos) {
        for(pos+=N, pos>>=1; pos; pos>>=1) { 
            tree[pos] = merge(tree[pos<<1], tree[pos<<1|1]); tree[pos] = merge1(tree[pos], lazy[pos]);
        }
    }

    //Pushes lazy of all parents of L from top
    void push(int l) {
        for(int s = lg; s > 0; --s) {
            int pos = l>>s;
            if(lazy[pos].mult != 1 || lazy[pos].add != 0) { 
                modify(pos<<1,lazy[pos]); 
                modify(pos<<1|1,lazy[pos]); 
                lazy[pos]= {1,0}; 
            }
        }
    }

    //Queries [L,R)
    T query(int l, int r) {
        push(l+N); push(r-1+N);
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

    //Updates [L,R)
    void update(int l, int r, U val) {
        push(l+N); push(r-1+N);
        int l0 = l, r0 = r;
        for(l+=N, r+=N; l < r; l>>=1, r>>=1) {
            if(l&1) { modify(l++,val); }
            if(r&1) { modify(--r,val); }
        } 
        build(l0); build(r0 - 1);
    }
};
