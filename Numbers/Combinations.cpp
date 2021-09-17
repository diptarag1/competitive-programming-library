template <int n = 1000000>
struct Factorial {
    vector<mint> f, invf;
    Factorial() { 
        f.resize(n); invf.resize(n);
        f[0] = 1; loop(i,1,n) f[i] = f[i-1] * i;
        invf[n-1] = f[n-1] ^ (MOD - 2); loopr(i,n-2,0) invf[i] = (i + 1) * invf[i+1];
    }
    mint ncr(ll a, ll b) {
        if(a < b) return 0;
        return (f[a] * invf[b] * invf[a-b]);
    }
    mint npr(ll a, ll b) {
        if(a < b) return 0;
        return (f[a] * invf[a-b]);
    }
};
