template <typename T = mint>
auto mpow = [](T x, i64 y){
	T z = x;
	T val = y & 1 ? x : T(1);
	while(z *= z, y >>= 1)
		if(y & 1)
			val *= z;
	return val;
};

