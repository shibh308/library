auto mpow = [&](mint x, i64 y){
	mint z = x;
	mint val = y & 1 ? x : mint(1);
	while(z *= z, y >>= 1)
		if(y & 1)
			val *= z;
	return val;
};

