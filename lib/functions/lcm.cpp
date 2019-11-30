auto lcm = [gcd](i64 x, i64 y){
	return x * y / gcd(x, y);
};

