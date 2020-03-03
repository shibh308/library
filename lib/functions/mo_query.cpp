template <typename ResultType>
vector<ResultType> mo_query(Mo& mo, vector<pair<int,int>>& queries, function<ResultType(int)> get_func, int packet=512){
    int q = queries.size();
    vector<tuple<int,int,int>> sort_queries;
    for(int i = 0; i < q; ++i)
        sort_queries.emplace_back(queries[i].first / packet, queries[i].second, i);
    sort(sort_queries.begin(), sort_queries.end());
    vector<ResultType> ans(q);
    for(auto& query : sort_queries){
        int idx = get<2>(query);
        mo.move(queries[idx].first, queries[idx].second);
        ans[idx] = get_func(idx);
    }
    return ans;
}

