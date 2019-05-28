auto ncr = [&fact, &inv](int n, int r){
	if(n < 0 || r < 0 || n < r)
		return mint(0);
	return fact[n] * inv[r] inv[n - r];
};

