template<int n = 100000000>
struct lsieve {
    vector<int> sieve, primes;
    lsieve() {
        sieve.resize(n+1, 1);
        for(int i = 2; i <= n; ++i) {
            if(sieve[i]) primes.pb(i);
            int k = i*primes[0]; int j = 0;
            while(1) {
                if(k >= n) break;
                sieve[k] = 0;
                if(i%primes[j]==0 || j >= primes.size() - 1) break;
                k = i*primes[++j];
            }
        }
    }
};
