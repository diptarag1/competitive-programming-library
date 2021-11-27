int calc_harmonic_sum(int n, int k) { //n/1 + n/2 + .. n/k in O(sqrt(N))
    int i = 1, ni; int ans = 0;
    int cnt = 0;
    while (i <= n) {
        ni = n / (n/i) + 1;
        ans += (n/i) * (min(k+1, ni) - i);
        if(ni > k) break;
        i = ni;
        cnt++;
    }
    return ans;
}
