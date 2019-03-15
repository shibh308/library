auto factoring = [](i64 x){
	int sq = sqrt(x) + 1;
	vector<int> ret;
	if(x == 1){
		ret.emplace_back(1);
		return ret;
	}
	for(i64 i = 2; i < sq; ++i)
		while(x % i == 0){
			ret.emplace_back(i);
			x /= i;
		}
	if(x != 1)
		ret.emplace_back(x);
	return ret;
};

