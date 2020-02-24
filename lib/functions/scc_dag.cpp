struct Result{
    int dag_size;
    vector<vector<int>> dag_graph;
    // 元のグラフでi番目の頂点が何番目の強連結成分に含まれるか
    vector<int> elements;
    // i番目の強連結成分に含まれる頂点のリスト
    vector<vector<int>> tps_list;
    // トポソしてi番目にくる頂点のindex
    vector<int> tps_order;
    // DAGのi番目の頂点をトポソした時の番号
    vector<int> tps_index;
};

Result scc_dag(vector<vector<int>>& edges){
    int n = edges.size();
    vector<int> scc_vec = scc(edges);
    int m = *max_element(scc_vec.begin(), scc_vec.end()) + 1;
    vector<vector<int>> dag_graph(m);

    queue<int> tps_que;
    vector<int> in_count(m, 0);
    vector<int> tps(m, -1);
    vector<int> tps_idx(m);
    for(int i = 0; i < n; ++i){
        for(auto j : edges[i]){
            if(scc_vec[i] == scc_vec[j])
                continue;
            dag_graph[scc_vec[i]].push_back(scc_vec[j]);
            ++in_count[scc_vec[j]];
        }
    }
    for(int i = 0; i < m; ++i)
        if(in_count[i] == 0)
            tps_que.push(i);
    int cnt = 0;
    while(!tps_que.empty()){
        int x = tps_que.front();
        tps_idx[x] = cnt;
        tps[cnt++] = x;
        tps_que.pop();
        for(auto y : dag_graph[x])
            if(--in_count[y] == 0)
                tps_que.push(y);
    }
    assert(cnt == m);

    vector<vector<int>> tps_list(m);
    for(int i = 0; i < n; ++i)
        tps_list[scc_vec[i]].push_back(i);

    Result res;
    res.dag_size = m;
    res.elements = move(scc_vec);
    res.tps_index = move(tps_idx);
    res.tps_order = move(tps);
    res.tps_list = move(tps_list);
    res.dag_graph = move(dag_graph);
    return res;
}

