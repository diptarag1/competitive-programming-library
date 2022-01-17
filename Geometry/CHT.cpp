struct line {
    long long m, c;
    long long eval(long long x) { return m * x + c; }
    long double intersectX(line l) { return (long double) (c - l.c) / (l.m - m); }
};

vector<int> init(int N) {
    vector<int> ints(N);
    iota(ints.begin(), ints.end(),0);
    return ints;
}

struct CHT {
    static vector<int> ints;
    deque<line> dq;
    CHT() { dq.push_back({0,0}); }
    int query(int x) { //returns index of line in dq with maximum evaluation
        return *lower_bound(ints.begin(), ints.begin() + dq.size() - 1, x, [&](int idx, int xx) { return dq[idx].intersectX(dq[idx + 1]) < xx; });
    }
    void insert(line cur) { //insert works when slopes are in descending order
        while (dq.size() >= 2 && cur.intersectX(dq[0]) >= dq[0].intersectX(dq[1])) dq.pop_front();
        dq.push_front(cur);
    }
};
vector<int> CHT::ints = init(3e5);

//if slopes are in ascending order, m -> -m, queryX -> -queryX
//if min is needed, slope -> m -> -m, c -> -c
	
