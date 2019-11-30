auto eratosthenes = []{
	constexpr int N = 2e6;
	bitset<N> not_prime(3);
	for(int i = 2; i < N; ++i)
		if(!not_prime[i])
			for(int j = 2 * i; j < N; j += i)
				not_prime.set(j);
	return not_prime;
};

