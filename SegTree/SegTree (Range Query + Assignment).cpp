//Data node
struct node{
    int val;
    node(int val=0) : val(val) {}
    friend node merge(const node& n1, const node& n2) {
        return node(min(n1.val, n2.val));
    }
};

//Update node
struct lnode {
    int add;
    lnode(int aa=0) : add(aa) {}
    friend node merge1(const node& n1, const lnode& n2) {
        return node( n1.val + n2.add );
    }
    friend lnode merge2(const lnode& n1, const lnode& n2) {
        return lnode( n1.add + n2.add ); 
    }
    bool operator != (const lnode& a) {
        return add != a.add;
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
            tree[pos] = merge(tree[pos<<1], tree[pos<<1|1]); 
            if(lazy[pos] != U()) { tree[pos] = merge1(tree[pos], lazy[pos]); lazy[pos] = U(); }
        }
    }

    //Pushes lazy of all parents of L from top
    void push(int l) {
        for(int s = lg; s > 0; --s) {
            int pos = l>>s;
            if(lazy[pos] != U()) { 
                modify(pos<<1,lazy[pos]); 
                modify(pos<<1|1,lazy[pos]); 
                lazy[pos]= U(); 
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

/* Make
	int N = 1; while(N < n) N<<=1;
	vector<node> tree(2*N+1); vector<lnode> lazy(2*N+1);
	loop(i,0,n) tree[i+N] = a[i];
	SegTree seg(N, tree, lazy);
*/
