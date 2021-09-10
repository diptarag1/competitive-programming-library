int lg = 20;
int N = 1<<(lg-1);

struct node{
    ll a;
    node(ll aa=0) : a(aa) {}
};
struct lnode {
    ll mult, add;
    lnode(ll aa=1, ll bb=0) : mult(aa), add(bb) {}
};

node merge(const node& n1, const node& n2) {
    return node(addm(n1.a, n2.a));
}
node merge1(const node& n1, const lnode& n2, int siz) {
    return node( addm(multm(n2.mult,n1.a),multm(n2.add,siz)) );
}
lnode merge2(const lnode& n1, const lnode& n2) {
    return lnode( multm(n1.mult,n2.mult), addm(multm(n1.add,n2.mult),n2.add) ); 
}

template<typename T, typename U>
void modify(int pos, vector<T>& tree, vector<U>& lazy, U val) {
    int siz = 1<<(lg-1-__lg(pos));
    tree[pos] = merge1(tree[pos], val,siz);
    if(pos < N) lazy[pos] = merge2(lazy[pos], val);
}

//Initialzies tree
template<typename T>
inline void init(vector<T>& tree) {
    for(int i = N-1; i > 0; i--) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
}

//Builds all parents of pos from bottom
template<typename T, typename U>
inline void build(int pos, vector<T>& tree, vector<U>& lazy) {
    for(pos+=N, pos>>=1; pos; pos>>=1) { 
        int siz = 1<<(lg-1-__lg(pos)); 
        tree[pos] = merge(tree[pos<<1], tree[pos<<1|1]); tree[pos] = merge1(tree[pos], lazy[pos], siz);
    }
}

//Pushes lazy of all parents of L from top
template<typename T, typename U>
void push(int l, vector<T>& tree, vector<U>& lazy) {
    for(int s = lg; s > 0; --s) {
        int pos = l>>s;
        if(lazy[pos].mult != 1 || lazy[pos].add) { 
            modify(pos<<1,tree,lazy,lazy[pos]); 
            modify(pos<<1|1,tree,lazy,lazy[pos]); 
            lazy[pos]= {1,0}; 
        }
    }
}

//Queries [L,R)
template<typename T, typename U>
T query(int l, int r, vector<T>& tree, vector<U>& lazy) {
    push(l+N,tree,lazy); push(r-1+N,tree,lazy);
    T res;
    for(l+=N, r+=N; l < r; l>>=1, r>>=1) {
        if(l&1) res = merge(res, tree[l++]);
        if(r&1) res = merge(res, tree[--r]);
    } 
    return res;
}

//Updates [L,R)
template<typename T, typename U>
void update(int l, int r, U val, vector<T>& tree, vector<U>& lazy) {
    push(l+N,tree,lazy); push(r-1+N,tree,lazy);
    int l0 = l, r0 = r;
    for(l+=N, r+=N; l < r; l>>=1, r>>=1) {
        if(l&1) { modify(l++,tree,lazy,val); }
        if(r&1) { modify(--r,tree,lazy,val); }
    } 
    build(l0,tree,lazy); build(r0 - 1,tree,lazy);
}