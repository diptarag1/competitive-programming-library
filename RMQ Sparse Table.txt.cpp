ll euler[150000];
ll st[150000][18];

void rmqpre() {
    loop(i, 0, 150000) { st[i][0] = euler[i]; }
    loop(bit, 1, 18) {
        loop(i, 0, 150000) { if (i + (1 << (bit - 1)) >= 300000) break; st[i][bit] = min(st[i][bit - 1], st[i + (1 << (bit - 1))][bit - 1]); }
    }
}

ll getmin(int l, int r) {
    ll fl = 1, bit = 0; while ((fl << 1) <= r - l) { fl <<= 1; bit++; }
    ll ans = min(st[l][bit], st[r - fl + 1][bit]);
    return ans;
}