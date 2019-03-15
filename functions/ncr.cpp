auto ncr = [&fact, &inv](int n, int r){
	return fact[n] * inv[r] % MOD * inv[n - r] % MOD;
};

