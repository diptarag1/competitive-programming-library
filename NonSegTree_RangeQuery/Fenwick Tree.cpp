struct BIT {
    vector<int> tree;
    BIT(vector<int>& v) {
        tree.resize(v.size());
	loop(i,1,v.size()) update(i, v[i]);
    }
    int query(int index) {
        int ans = 0;
        while (index > 0) {
            ans += tree[index];
            index -= index & (-index);
        }
        return ans;
    }
    void update(int index, int val) {
        while (index < tree.size()) {
            tree[index] += val;
            index += index & (-index);
        }
    }
};