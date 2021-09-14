template<typename T>
struct Matrix {
    int rows, cols;
    vector<vector<T>> matrix;
    Matrix(int rows, int cols, int def = 0) : rows(rows), cols(cols) {
        matrix = vector<vector<T>>(rows, vector<T>(cols));
        if(def) loop(i,0,rows) matrix[i][i] = def;
    }
    Matrix(vector<vector<T>>&& a) : matrix(a) { rows = matrix.size(); cols = matrix[0].size(); }
    Matrix(Matrix&& a) : matrix(move(a.matrix)) { rows = matrix.size(); cols = matrix[0].size(); }
    void operator = (Matrix&& a) { matrix = move(a.matrix); rows = matrix.size(); cols = matrix[0].size(); }
    friend Matrix operator * (Matrix<T>& a, Matrix<T>& b) {
        assert(a.cols == b.rows);
        Matrix<T> ans(a.rows, b.cols);
        loop(i,0,a.rows) loop(j,0,b.cols) loop(k,0,a.cols) ans.matrix[i][j] += a.matrix[i][k]*b.matrix[k][j];
        return ans;
    }
    friend Matrix operator ^ (Matrix<T>& aa, ll b) {
        Matrix<T> res(aa.rows, aa.cols, 1); 
        Matrix<T> a = move(aa);
        for (; b; b >>= 1) 
        { if (b & 1) res = res * a; a = a * a; }
        return res;
    }
};
