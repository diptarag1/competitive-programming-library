const int root = 565042129;
const int root_1 = 950391366;
const int root_pw = 1 << 20;

//MOD 998244353
void fft(vector<mint> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        mint wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = wlen * wlen;

        for (int i = 0; i < n; i += len) {
            mint w = 1;
            for (int j = 0; j < len / 2; j++) {
                mint u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w = w * wlen;
            }
        }
    }

    if (invert) {
        mint n_1 = mint(1) / n;
        for (mint & x : a)
            x = x * n_1;
    }
}

//result stored in a
void multiply(vector<mint> & a, vector<mint> const& b) {
    int n = 1; vector<mint> fb = b;
    while (n < a.size() + b.size()) n <<= 1;
    a.resize(n);
    fb.resize(n);

    fft(a, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        a[i] *= fb[i];
    fft(a, true);
    
}
