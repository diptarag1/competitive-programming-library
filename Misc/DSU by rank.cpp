struct dsu {
    vector<int> p,sum,minn,maxx,r;
    dsu(int n) {
        loop(i,0,n+1) {
            p.pb(i); sum.pb(i); minn.pb(i); maxx.pb(i); r.pb(0);
        }
    }
    int get(int a) {
        return (p[a] = (p[a]==a)?a:get(p[a]));
    }
    void uni(int a, int b) {
        a = get(a); b = get(b);
        if(a==b) return;
        if(r[a]==r[b]) r[a]++;
        if(r[a] < r[b]) swap(a,b);
        p[b] = a;
        sum[a] += sum[b];
        minn[a] = min(minn[a], minn[b]);
        maxx[a] = max(maxx[a],maxx[b]);
    }
};