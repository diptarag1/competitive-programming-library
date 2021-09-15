template<typename T>
struct BIT {
    vector<T> tree;
    BIT(int n) { tree.resize(n); }
    BIT(vector<T>& v) {
        tree.resize(v.size());
	loop(i,1,v.size()) update(i, v[i]);
    }
    T query(int index) {
        T ans = 0;
        while (index > 0) {
            ans += tree[index];
            index -= index & (-index);
        }
        return ans;
    }
    void update(int index, T val) {
        while (index < tree.size()) {
            tree[index] += val;
            index += index & (-index);
        }
    }
};
