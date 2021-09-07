int blocksize;

struct Mo {
    public:
    int maxno = 1e6 + 10;

    int answer;
    vector<int> cnt;
    vector<int> arr;

    void include(int index) {
        cnt[arr[index]]++;
        if(cnt[arr[index]] == 1) answer++;
    }
    void exclude(int index) {
        cnt[arr[index]]--;
        if(cnt[arr[index]] == 0) answer--;
    }

    Mo(vector<int>& a) {
        answer = 0;
        loop(i,0,a.size()) arr.pb(a[i]);
        loop(i,0,maxno) cnt.pb(0);
    }

    int query() {
        return answer;
    }
};

bool querysort(const tuple<int,int,int>& a, const tuple<int,int,int>& b) {
    int ablock = get<0>(a) / blocksize;
    int bblock = get<0>(b) / blocksize;
    if(ablock == bblock) {
        if(get<1>(a) < get<1>(b)) return true;
        else return false;
    }
    else {
        if(ablock < bblock) return true;
        else return false;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    /* code */
    int n; cin >> n;
    vector<int> a(n);
    loop(i,0,n) cin >> a[i];
    int q; cin >> q;
    vector<tuple<int,int,int>> queries(q);
    loop(i,0,q) {
        int l, r; cin >> l >> r;
        queries[i] = {l-1,r-1, i};
    }
    blocksize = (int) sqrt(n);
    sort(queries.begin(), queries.end(), querysort);
    Mo mo(a);

    vector<int> ans(q);

    int l = 0, r = 0;
    mo.include(0);
    loop(i,0,q) {
        int nextl = get<0>(queries[i]);
        int nextr = get<1>(queries[i]);

        if(l <= nextl && r <= nextr) {
            while(r < nextr) { mo.include(r+1); r++; }
            while(l < nextl) { mo.exclude(l); l++; }
        }
        else if(l > nextl && r > nextr) {
            while(l > nextl) { mo.include(l-1); l--; }
            while(r > nextr) { mo.exclude(r); r--; }
        }
        else {
            while(l < nextl) { mo.exclude(l); l++; }
            while(l > nextl) { mo.include(l-1); l--; }
            while(r < nextr) { mo.include(r+1); r++; }
            while(r > nextr) { mo.exclude(r); r--; }
        }

        ans[get<2>(queries[i])] = mo.query();
    }

    loop(i,0,q) cout << ans[i] << "\n";
    /* end code */
}