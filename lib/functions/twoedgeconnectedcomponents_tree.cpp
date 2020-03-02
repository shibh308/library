struct Result{
    int group_cnt;
    vector<int> group;
    vector<vector<int>> group_elm_list;
    // 同じ二重辺連結成分の辺をグループごとに列挙する, 片方向のみ(辺数倍化しない)
    vector<vector<pair<int,int>>> same_group_edges;
    // 橋, 片方向のみ
    vector<pair<int,int>> bridges;
    // 関節点
    vector<int> arts;
    vector<vector<int>> tree_graph;
    vector<int> par;
    vector<vector<int>> childs;
};

Result two_edge_connected_components_tree(vector<vector<int>>& edges){
    int n = edges.size();
    LowLink ll(edges);
    vector<vector<int>> not_bridge_graph(n);
    for(int i = 0; i < n; ++i)
        for(auto j : edges[i]){
            pair<int,int> min_max = minmax(i, j);
            auto iter = lower_bound(ll.bridge.begin(), ll.bridge.end(), min_max);
            if(iter == ll.bridge.end() || *iter != min_max)
                not_bridge_graph[i].push_back(j);
        }

    vector<int> group(n, -1);
    function<void(int)> group_dfs = [&](int x){
        for(auto y : not_bridge_graph[x])
            if(group[y] == -1){
                group[y] = group[x];
                group_dfs(y);
            }
    };
    int group_cnt = 0;
    for(int i = 0; i < n; ++i)
        if(group[i] == -1){
            group[i] = group_cnt++;
            group_dfs(i);
        }
    vector<vector<int>> group_elm_list(group_cnt);
    for(int i = 0; i < n; ++i)
        group_elm_list[group[i]].push_back(i);

    vector<vector<pair<int,int>>> same_group_edges(group_cnt);
    vector<vector<int>> tree_edges(group_cnt);
    vector<int> par(group_cnt, -1);
    vector<vector<int>> childs(group_cnt);

    for(int i = 0; i < n; ++i)
        for(auto j : edges[i])
            if(group[i] == group[j] && i < j)
                same_group_edges[group[i]].emplace_back(i, j);

    for(auto& p : ll.bridge){
        tree_edges[group[p.first]].push_back(group[p.second]);
        tree_edges[group[p.second]].push_back(group[p.first]);
    }
    vector<bool> flag(n, false);
    function<void(int)> tree_dfs = [&](int x){
        for(auto y : tree_edges[x])
            if(!flag[y]){
                flag[y] = true;
                par[y] = x;
                childs[x].push_back(y);
                tree_dfs(y);
            }
    };
    flag[0] = true;
    tree_dfs(0);

    Result res;
    res.group_cnt = group_cnt;
    res.group_elm_list = move(group_elm_list);
    res.same_group_edges = move(same_group_edges);
    res.bridges = move(ll.bridge);
    res.arts = move(ll.art);
    res.group = move(group);
    res.tree_graph = move(tree_edges);
    res.par = move(par);
    res.childs = move(childs);
    return res;
}

