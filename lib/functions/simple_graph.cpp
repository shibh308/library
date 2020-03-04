template <typename T = pair<int,int>>
vector<vector<int>> simple_graph(vector<vector<T>>& edges, function<int(T)> f = [](auto x){return x.first;}){
    vector<vector<int>> simple_edges(edges.size());
    for(int i = 0; i < edges.size(); ++i)
        for(auto& x : edges[i])
            simple_edges[i].push_back(f(x));
    return simple_edges;
}

