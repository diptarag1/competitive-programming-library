const int N = 1048576/2;

struct node{
    ll a;
    node(ll aa=0) : a(aa) {}
};
node merge(const node& n1, const node& n2) {
    return node(n1.a + n2.a);
}
template<typename T, typename U>
void modify(T& n1, const U& n2) {
    n1.a += n2;
}

template<typename T>
inline void build(vector<T>& tree) {
    int n = tree.size()>>1;
    for(int i = n-1; i >= 0; i--) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
}

//queries [L,R)
template<typename T>
T query(int l, int r, vector<T>& tree) {
    int n = tree.size()>>1;
    T res1 = tree[l+n]; l++;
    if(l == r) return res1;
    T res2 = tree[(--r)+n];  
    for(l+=n, r+=n; l < r; l>>=1, r>>=1) {
        if(l&1) res1 = merge(res1, tree[l++]);
        if(r&1) res2 = merge(tree[--r], res2);
    } 
    return merge(res1, res2);
}

template<typename T>
void update(int pos, int val, vector<T>& tree) {
    int n = tree.size()>>1; pos+=n; modify(tree[pos], val);
    for(pos>>=1; pos; pos>>=1) tree[pos] = merge(tree[pos<<1], tree[pos<<1|1]);
}