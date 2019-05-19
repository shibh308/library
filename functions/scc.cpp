vector<int> scc(vector<vector<int>>& edges){
	int n = edges.size();
    vector<vector<int>> rev(n);

	for(int i = 0; i < n; ++i)
		for(auto& x : edges[i])
			rev[x].emplace_back(i);

    vector<i64> dfs_num(n, -1);
    vector<i64> flag(n, 0);
    int num = 0;
    function<void(int)> dfs = [&](int pos){
        flag[pos] = 1;
		for(auto& xx : edges[pos])
			if(!flag[xx]){
				dfs(xx);
        }
        dfs_num[pos] = num++;
    };

	for(int i = 0; i < n; ++i)
        if(!flag[i])
            dfs(i);

	vector<int> dfs_inv(n);
	for(int i = 0; i < n; ++i)
		dfs_inv[n - 1 - dfs_num[i]] = i;

    num = 0;

    vector<int> scc_vec(n, -1);

    function<void(int)> rdfs = [&](int pos){
        scc_vec[pos] = num;
        for(auto t : rev[pos])
            if(scc_vec[t] == -1)
                rdfs(t);
    };

	for(int i = 0; i < n; ++i)
        if(scc_vec[dfs_inv[i]] == -1){
            rdfs(dfs_inv[i]);
            ++num;
        }

	return scc_vec;
}
