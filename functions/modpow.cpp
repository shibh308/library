auto mpow = [](auto x, i64 y){
	auto z = x;
	decltype(x) val = y & 1 ? x : decltype(x)(1);
	while(z *= z, y >>= 1)
		if(y & 1)
			val *= z;
	return val;
};

