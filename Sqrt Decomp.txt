int n, sq;
int a[500000];
vector<vector<ll>> sqrtd(10000);
int lazyadd[10000];
int lazymul[10000];

void build(int block) {
    int index = sq * block; sqrtd[block].clear();
    while (index < min(n,(block + 1) * sq)) { sqrtd[block].pb(a[index++]); }
    sort(sqrtd[block].begin(), sqrtd[block].end());
}

void update(ll start, ll end, ll add, ll mul) {
    int block = start / sq;
    //cout << 'c' << start << " " << end << " "<< (block + 1) * sq - 1 << "\n";
    if (start > end) return; 
    if ((start == block * sq) && (end >= (block + 1) * sq - 1)) { lazyadd[block] += add; lazymul[block] *= mul; lazyadd[block] *= mul; start = (block + 1) * sq; }
    else {
        loop(i, block * sq, min(n, (block + 1) * sq)) { a[i] = a[i] * lazymul[block] + lazyadd[block]; }
        lazymul[block] = 1; lazyadd[block] = 0;
        if (end >= (block + 1) * sq) { loop(i, start, (block + 1) * sq) { a[i] += add; a[i] *= mul; } start = (block + 1) * sq; build(block); }
        else { loop(i, start, end + 1) { a[i] += add; a[i] *= mul; } build(block); return; }
    }
    update(start, end, add, mul);
}

int search(int block, ll num) {
    int low = 0; int high = sqrtd[block].size();
    while (high > low) {
        int mid = (low + high) / 2; ll a = sqrtd[block][mid] * lazymul[block] + lazyadd[block];
        if (a == num) return 1;
        if (a > num) high = mid - 1;
        if (a < num) low = mid + 1;
    }
    if (low < sqrtd[block].size() && sqrtd[block][low] * lazymul[block] + lazyadd[block] == num) return 1;
    if (high < sqrtd[block].size() && sqrtd[block][high] * lazymul[block] + lazyadd[block] == num) return 1;
    return 0;
}

int query_first(ll num) {
    int b = 0;
    while (b <= sq) { if (search(b, num)) break; b++; }
    if (b == sq + 1) return -1;
    loop(i, b * sq, min(n, (b + 1) * sq)) { a[i] = a[i] * lazymul[b] + lazyadd[b]; }
    lazymul[b] = 1; lazyadd[b] = 0;
    build(b);
    loop(i, b* sq, min(n, (b + 1)* sq)) { if (a[i] == num) return i; }
}

int query_last(ll num) {
    int b = sq;
    while (b >= 0) { if (search(b, num)) break; b--; }
    if (b == -1) return -1;
    loop(i, b * sq, min(n, (b + 1) * sq)) { a[i] = a[i] * lazymul[b] + lazyadd[b]; }
    lazymul[b] = 1; lazyadd[b] = 0;
    build(b);
    loopr(i, min(n, (b + 1)* sq) - 1, b*sq) { if (a[i] == num) return i; }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /* code */
    cin >> n;
    loop(i, 0, 10000) { lazyadd[i] = 0; lazymul[i] = 1; }
    sq = 0; while ((sq + 1) * (sq + 1) <= n) { sq++; }
    loop(i, 0, n) cin >> a[i]; int index = 0;
    loop(i, 0, sq + 1) { build(i); }
    int q; cin >> q;
    while (q--) {
        
        int type; cin >> type;
        if (type == 1) {
            ll a, b, c; cin >> a >> b >> c;
            update(a - 1, b - 1, c, 1);
        }
        if (type == 2) {
            ll a, b, c; cin >> a >> b >> c;
            update(a - 1, b - 1, 0, c);
        }
        if (type == 3) {
            ll a; cin >> a;
            int x = query_first(a); int y = query_last(a);
            //cout << x << " " << y << "\n";
            if (x == -1) cout << -1 << "\n";
            else cout << (y - x + 1) << "\n";
        }
    }
    /* end code */
}