struct node {
    int val;
    node(int a=INF) : val(a) {}
    friend node operator + (node a, node b) { return min(a.val,b.val); }
};

template<typename T>
struct RMQ {
    vector<vector<T>> st; int N, lg;
    RMQ(int n, vector<T>& a) { 
        lg = 1; N = 1; 
        while(N < n) { N<<=1; lg++; } 
        st.resize(lg, vector<T>(N));
        loop(i,0,n) st[0][i] = a[i]; 
        loop(bit, 1, lg) {
            loop(i, 0, N) { 
                if (i + (1 << (bit - 1)) >= N) break; 
                st[bit][i] = st[bit - 1][i] + st[bit - 1][i + (1 << (bit - 1))]; 
            }
        }
    }
    T getmin(int l, int r) {
        int bit = __lg(r-l+1); int fl = 1<<bit;
        T ans = st[bit][l] + st[bit][r - fl + 1];
        return ans;
    }
};
