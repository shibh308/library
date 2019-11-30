struct LowLink{
    vector<vector<int>>& edges;
    // 関節点
    vector<int> art;
    vector<pair<int,int>> bridge;

    vector<int> used, ord, low;
    int k;

    void dfs(int idx, int par){
        ord[idx] = k++;
        low[idx] = ord[idx];
        bool is_art = false;
        int cnt = 0;
        for(auto& to : edges[idx]){
            if(ord[to] == -1){
                ++cnt;
                dfs(to, idx);
                low[idx] = min(low[idx], low[to]);
                is_art |= par != -1 && low[to] >= ord[idx];
                if(ord[idx] < low[to])
                    bridge.emplace_back(idx, to);
            }else if(to != par)
                low[idx] = min(low[idx], ord[to]);
        }
        is_art |= (par == -1 && cnt > 1);
        if(is_art)
            art.emplace_back(idx);
    }

    LowLink(vector<vector<int>>& edges) :
        edges(edges),
        ord(edges.size(), -1),
        low(edges.size(), 0),
        k(0)
    {
        for(int i = 0; i < edges.size(); ++i)
            if(ord[i] == -1)
                dfs(i, -1);
        for(auto& b : bridge)
            b = make_pair(min(b.first, b.second), max(b.first, b.second));
        sort(art.begin(), art.end());
        sort(bridge.begin(), bridge.end());
    }
};

