int lg = 19;
int N = 1<<(lg-1);

struct node{
    ll a;
    node(ll aa=0) : a(aa) {}
};
struct lnode {
    ll a;
    lnode(ll aa=0) : a(aa) {}
};

node merge(const node& n1, const node& n2) {
    return node(max(n1.a, n2.a));
}
template<typename T, typename U, typename V>
void modify(int pos, vector<T>& tree, vector<U>& lazy, V val) {
    tree[pos].a += val;
    if(pos < N) lazy[pos].a += val;
}

template<typename T>
inline void init(vector<T>& tree) {
    for(int i = N-1; i >= 0; i--) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
}

template<typename T>
inline void build(int pos, vector<T>& tree) {
    for(pos+=N, pos>>=1; pos; pos>>=1) tree[pos] = merge(tree[pos<<1], tree[pos<<1|1]) + lazy[pos].a;
}

template<typename T, typename U>
void push(int l, vector<T>& tree, vector<U>& lazy) {
    for(int s = lg; s > 0; --s) {
        int pos = l>>s;
        if(lazy[pos].a != 0) { 
            modify(pos<<1,tree,lazy,lazy[pos].a); 
            modify(pos<<1|1,tree,lazy,lazy[pos].a); 
            lazy[pos]= {0}; 
        }
    }
}

//Queries [L,R)
template<typename T, typename U>
T query(int l, int r, vector<T>& tree, vector<U>& lazy) {
    push(l+N,tree,lazy); push(r-1+N,tree,lazy);
    T res(0);
    for(l+=N, r+=N; l < r; l>>=1, r>>=1) {
        if(l&1) res = merge(res, tree[l++]);
        if(r&1) res = merge(res, tree[--r]);
    } 
    return res;
}

//Updates [L,R)
template<typename T, typename U>
void update(int l, int r, int val, vector<T>& tree, vector<U>& lazy) {
    int l0 = l, r0 = r;
    for(l+=N, r+=N; l < r; l>>=1, r>>=1) {
        if(l&1) { modify(l++,tree,lazy,val); }
        if(r&1) { modify(--r,tree,lazy,val); }
    } 
    build(l0,tree); build(r0 - 1,tree);
}