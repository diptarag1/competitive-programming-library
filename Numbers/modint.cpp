template <ll mod = MOD>
struct modint {
    ll val;
    modint() : val(0) {}
    modint(ll a) : val(a) { val += mod; if(val >= mod) val -= mod; }
    void operator = (modint a) { val = a.val; }
    bool operator == (modint a) { return val == a.val; } 
    bool operator != (modint a) { return val != a.val; }
    inline modint& operator += (modint a) { val = val + a.val; if(val >= mod) val-=mod; return *this; }
    inline modint& operator -= (modint a) { val = val - a.val + mod; if(val >= mod) val -= mod; return *this; }
    inline modint& operator *= (modint a) { val = (val*a.val)%mod; return *this; }
    friend modint operator + (modint a, modint b) { return (a += b); }
    friend modint operator - (modint a, modint b) { return (a -= b); } 
    friend modint operator * (modint a, modint b) { return (a *= b); }
    friend modint operator ^ (modint a, ll b) { modint res = 1; for (; b; b >>= 1) { if (b & 1)res*=a; a*=a; } return res; }
    friend modint operator / (modint num, modint den) { den = den ^ (mod-2); return (num*den); }
    friend ostream & operator << (ostream &out, modint a) { out << a.val; return out; }
    friend istream & operator >> (istream &in, modint& a) { in >> a.val; return in; }
};

using mint = modint<MOD>;
