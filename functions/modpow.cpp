auto mpow = [&](i64 x, i64 y){
	i64 z = x;
	i64 val = y & 1 ? x : 1L;
	while(z = z * z % MOD, y >>= 1)
		if(y & 1)
			val = val * z % MOD;
	return val;
};

