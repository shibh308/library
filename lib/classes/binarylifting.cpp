struct BinaryLifting{
    int n;
    vector<vector<int>> next;
    vector<int> depth;

    BinaryLifting(vector<vector<int>>& edges, int root = 0) : n(edges.size()), depth(n, -1){
        vector<int> par(n, -1);
        function<void(int)> dfs = [&](int x){
            for(auto y : edges[x])
                if(depth[y] == -1){
                    depth[y] = depth[x] + 1;
                    par[y] = x;
                    dfs(y);
                }
        };
        depth[root] = 0;
        dfs(0);

        next.push_back(move(par));
        for(int k = 0;; ++k){
            bool fl = false;
            next.emplace_back(n, -1);
            for(int i = 0; i < n; ++i){
                next[k + 1][i] = (next[k][i] == -1 ? -1 : next[k][next[k][i]]);
                if(next[k + 1][i] != -1)
                    fl = true;
            }
            if(!fl)
                break;
        }
    }
    // kth_next(x, 0) => x
    int kth_next(int x, int k){
        for(int i = 0; i < next.size() && k; ++i){
            if(k & (1 << i)){
                x = next[i][x];
                if(x == -1)
                    break;
            }
        }
        return x;
    }

    int lca(int x, int y){
        int min_depth = min(depth[x], depth[y]);
        x = kth_next(x, depth[x] - min_depth);
        y = kth_next(y, depth[y] - min_depth);
        if(x == y)
            return x;
        for(int i = next.size() - 1; i >= 0; --i)
            if(next[i][x] != next[i][y]){
                x = next[i][x];
                y = next[i][y];
            }
        return next[0][x];
    }
};

