auto divisor = [](i64 x){
	int sq = sqrt(x) + 1;
	vector<int> ret;
	for(i64 i = 1; i < sq; ++i)
		if(!(x % i)){
			ret.emplace_back(i);
			if(i * i != x)
				ret.emplace_back(x / i);
		}
	sort(ret.begin(), ret.end());
	return ret;
};

