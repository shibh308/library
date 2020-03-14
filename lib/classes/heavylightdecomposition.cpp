struct HeavyLightDecomposition{
    int n;
    vector<int> size, par, in, in_rev, heavy_root, depth, heavy_depth, out;
    vector<vector<int>> childs;
    HeavyLightDecomposition(vector<vector<int>>& edges, int root = 0) : n(edges.size()), size(n, 1), par(n, -2), depth(n, 0), childs(n), in(n), in_rev(n), heavy_root(n), heavy_depth(n, 0), out(n){
        function<void(int)> swap_dfs = [&](int x){
            int size_max = 0;
            int max_idx = 0;
            for(int i = 0; i < edges[x].size(); ++i){
                int y = edges[x][i];
                if(par[y] == -2){
                    par[y] = x;
                    depth[y] = depth[x] + 1;
                    childs[x].push_back(y);
                    swap_dfs(y);
                    size[x] += size[y];
                    if(chmax(size_max, size[y])){
                        max_idx = childs[x].size() - 1;
                    }
                }
            }
            if(max_idx){
                swap(childs[x][0], childs[x][max_idx]);
            }
        };
        par[root] = -1;
        swap_dfs(root);

        int cnt = 0;
        function<void(int,int)> dfs = [&](int x, int segment_root){
            heavy_root[x] = segment_root;
            in_rev[cnt] = x;
            in[x] = cnt++;
            for(int i = 0; i < childs[x].size(); ++i){
                int y = childs[x][i];
                if(i == 0){
                    dfs(y, segment_root);
                }
                else{
                    heavy_depth[y] = heavy_depth[segment_root] + 1;
                    dfs(y, y);
                }
            }
            out[x] = cnt;
        };
        dfs(root, root);
    }
    int lca(int x, int y){
        while(heavy_root[x] != heavy_root[y]){
            if(heavy_depth[heavy_root[x]] > heavy_depth[heavy_root[y]])
                swap(x, y);
            y = par[heavy_root[y]];
        }
        return depth[x] < depth[y] ? x : y;
    }
    // x以下の部分木を返す
    pair<int,int> subtree(int x){
        return make_pair(in[x], out[x]);
    }
    // x-zのパスとy-zのパスを返す(両方とも根側に進むので注意)
    // それぞれのHeavy-Pathは根側の方がindexが小さいので注意(可換クエリ処理で気をつける)
    pair<vector<pair<int,int>>, vector<pair<int,int>>> two_point_path(int x, int y){
        vector<pair<int,int>> xz, yz;
        int z = lca(x, y);
        while(heavy_root[x] != heavy_root[z]){
            xz.emplace_back(in[heavy_root[x]], in[x] + 1);
            x = par[heavy_root[x]];
        }
        while(heavy_root[y] != heavy_root[z]){
            yz.emplace_back(in[heavy_root[y]], in[y] + 1);
            y = par[heavy_root[y]];
        }
        // 辺属性にしたい場合はここをin[z] + 1, in[x] + 1にする
        xz.emplace_back(in[z], in[x] + 1);
        yz.emplace_back(in[z] + 1, in[y] + 1);
        return make_pair(xz, yz);
    }
    // 頂点xがEuler-Tour上で何番目に位置するかを返す
    // in[元の頂点index] = 内部でのindex
    // in_rev[内部でのindex] = 元の頂点index
    int get_idx(int x){
        return in[x];
    }
    // xが属するHeavy-Pathの深さを返す
    int get_heavy_depth(int x){
        return heavy_depth[heavy_root[x]];
    }
};

