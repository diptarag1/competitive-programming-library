template<int n = 1000000>
struct lsieve {
    vector<int> sieve, primes;
    lsieve() {
        sieve.resize(n+1, 1);
        for(int i = 2; i <= n; ++i) {
            if(sieve[i]) primes.pb(i);
            for(int j = 0; j < primes.size() && i*primes[j] <= n; ++j) {
                sieve[i*primes[j]] = 0;
                if(i%primes[j]==0) break;
            }
        }
    }
};
