V scc(vector<V> edges){
	int n = edges.size();
    vector<V> rev(n);

    ll ans = 0;

    REP(i,n)
		FOREACH(xx,edges[i])
			rev[xx].pb(i);

    V dfs_num(n, -1);
    V flag(n, 0);
    ll num = 0;
    function<void(ll)> dfs = [&](ll pos){
        flag[pos] = 1;
		for(auto& xx : edges[pos])
			if(!flag[xx]){
				dfs(xx);
        }
        dfs_num[pos] = num++;
    };

    REP(i,n)
        if(!flag[i])
            dfs(i);

	V dfs_inv(n);
    REP(i,n)
		dfs_inv[n - 1 - dfs_num[i]] = i;

    num = 0;

    V scc_vec(n, -1);

    function<void(ll)> rdfs = [&](ll pos){
        scc_vec[pos] = num;
        for(auto t : rev[pos])
            if(scc_vec[t] == -1)
                rdfs(t);
    };

	REP(i, n)
        if(scc_vec[dfs_inv[i]] == -1){
            rdfs(dfs_inv[i]);
            ++num;
        }

	return scc_vec;
}
