struct line {
    long long m, c;
    long long eval(long long x) { return m * x + c; }
    long double intersectX(line l) { return (long double) (c - l.c) / (l.m - m); }
};

vector<ll> ints(1e5+1);
deque<line> dq;
auto cmp = [](int idx, int x) { return dq[idx].intersectX(dq[idx + 1]) < x; };

int query(int x) { //returns index of line in dq with maximum evaluation
    return *lower_bound(ints.begin(), ints.begin() + dq.size() - 1, x, cmp);
}

void insert(line cur) { //insert works when slopes are in descending order
    while (dq.size() >= 2 && cur.intersectX(dq[0]) >= dq[0].intersectX(dq[1])) dq.pop_front();
    dq.push_front(cur);
}

//if slopes are in ascending order, m -> -m, queryX -> -queryX
//if min is needed, slope -> m -> -m, c -> -c
