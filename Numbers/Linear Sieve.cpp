template<int n = 100000000>
struct lsieve {
    vector<int> sieve, primes, phi;
    lsieve() {
        sieve.resize(n+1, 1);
        phi.resize(n+1); phi[1] = 1;
        for(int i = 2; i <= n; ++i) {
            if(sieve[i]) { 
                primes.pb(i);
                phi[i] = -1;
            }
            for (int j = 0; j < primes.size() && i * primes[j] <= n; ++j) {
                sieve[i * primes[j]] = 0;
                if(i%primes[j]==0) {
                    phi[i * primes[j]] = 0; //change according to function
                    break;
                }
                phi[i * primes[j]] = phi[i] * phi[primes[j]]; 
            }
        }
    }
};
