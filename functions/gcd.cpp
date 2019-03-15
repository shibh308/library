auto gcd = [](i64 x, i64 y){
	while(y){
		i64 z = x % y;
		x = y;
		y = z;
	}
	return x;
};

