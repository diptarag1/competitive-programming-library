int N = 1e8;
vector<int> sieve(N+1, 1), primes;
void primepre() {
	for(int i = 2; i <= N; ++i) {
		if(sieve[i]) primes.pb(i);
		for(int j = 0; j < primes.size() && i*primes[j] <= N; ++j) {
			sieve[i*primes[j]] = 0;
			if(i%primes[j]==0) break;
		}
	}
}