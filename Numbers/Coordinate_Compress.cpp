template<typename T>
int compress(vector<T>& a, vector<T>& d) {
    d = a;
    sort(d.begin(), d.end());
    d.resize(unique(d.begin(), d.end()) - d.begin());
    for (int i = 1; i < a.size(); ++i) {
        a[i] = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
    } 
    return d.size();
}
