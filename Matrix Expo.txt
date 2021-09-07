struct Matrix {
    vector<vector<int>> mat;
    int n, m;
    Matrix(int a, int b) {
        n = a;
        m = b;
        mat.resize(a);
        loop(i, 0, a) mat[i].resize(b);
    }
    Matrix operator *(Matrix op) {
        Matrix ans(n, op.m);
        loop(i, 0, n) {
            loop(j, 0, op.m) {
                loop(k, 0, m) { ans.mat[i][j] += (mat[i][k] * op.mat[k][j])%MOD; ans.mat[i][j]%=MOD; }
            }
        }
        return ans;
    }
    Matrix exp(int b) {
        Matrix ans(n, m);
        Matrix a(n, m);
        loop(i, 0, n) { loop(j, 0, m) a.mat[i][j] = mat[i][j]; }
        loop(i, 0, n) { ans.mat[i][i] = 1; }
        for (; b; b >>= 1) { if (b & 1)ans = ans * a; a = a * a; }
        return ans;
    }
};