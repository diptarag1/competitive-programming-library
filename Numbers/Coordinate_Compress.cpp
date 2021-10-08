template<typename T> 
int compress(vector<T> a, map<T, int>& id, int start = 0) {
    sort(a.begin(), a.end());
    int curid = start; id[a[0]] = curid++;
    loop(i,1,a.size()) {
        if(a[i] != a[i-1]) id[a[i]] = curid++;
    }
    return curid;
}
