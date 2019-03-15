auto calc_fact = [mpow]{
	constexpr int N = 1e7;
	constexpr int MOD = 1e9 + 7;
	vector<i64> fact(N + 1, 1);
	vector<i64> inv(N + 1, 1);
	for(int i = 1; i < N; ++i){
		fact[i + 1] = fact[i] * (i + 1) % MOD;
		inv[i + 1] = mpow(fact[i + 1], MOD - 2);
	}
	return make_pair(fact, inv);
};
vector<i64> fact, inv;
tie(fact, inv) = calc_fact();

