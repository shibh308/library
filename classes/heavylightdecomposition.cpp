class HeavyLightDecomposition{
public:
    int n;
    vector<V> g;
    V rev, in, out, nxt, rin, size, depth;

    HeavyLightDecomposition(vector<V>& inp) :
        n(inp.size()),
        g(n),
        rev(n, 0),
        in(n, 0),
        out(n, 0),
        nxt(n, 0),
        rin(n, 0),
        size(n, 0),
        depth(n, -1)
    {

        function<void(int, int)> dfs_ed = [&](int pos, int dep){
            depth[pos]=dep;
            for(auto ed : inp[pos])
                if(depth[ed] == -1){
                    g[pos].pb(ed);
                    rev[ed] = pos;
                    dfs_ed(ed, dep + 1);
                }
        };
        dfs_ed(0, 0);

        function<void(int)> dfs_sz = [&](int v){
            size[v] = 1;
            for(auto &u: g[v]){
                dfs_sz(u);
                size[v] += size[u];
                if(size[u] > size[g[v][0]])
                    swap(u, g[v][0]);
            }
        };
        dfs_sz(0);

        int t = 0;

        function<void(int)> dfs_hld = [&](int v){
            in[v] = t++;
            rin[in[v]] = v;
            for(auto u: g[v]){
                nxt[u] = (u == g[v][0] ? nxt[v] : u);
                dfs_hld(u);
            }
            out[v] = t;
        };
        dfs_hld(0);
    }

    P subtree(int x){
        return make_pair(in[x], out[x]);
    }

    V subtree_path(int x){
        return V(next(rin.begin(), in[x]), next(rin.begin(), out[x]));
    }

    P subsegment(int x){
        return make_pair(in[nxt[x]], in[x] + 1);
    }

    V subsegment_path(int x){
        return V(next(rin.begin(), in[nxt[x]]), next(rin.begin(), in[x] + 1));
    }

    vector<P> root_path_query(int x){
        vector<P> ret;
        ret.emplace_back(subsegment(x));
        while(ret.back().first)
            ret.emplace_back(subsegment(rev[rin[ret.back().first]]));

        return ret;
    }

    int lca(int x, int y){

        int sx = rin[subsegment(x).first];
        int sy = rin[subsegment(y).first];
        while(sx != sy){
            if(depth[sx] > depth[sy])
                x = rev[sx];
            else
                y = rev[sy];
            sx = rin[subsegment(x).first];
            sy = rin[subsegment(y).first];
        }

        return depth[x] < depth[y] ? x : y;
    }
 
    pair<vector<P>,vector<P>> two_point_path(ll x, ll y){
        ll z = lca(x, y);
        P z_par = subsegment(z);
 
        vector<P> ret_x;
        ret_x.emplace_back(subsegment(x));

        while(ret_x.back().first != z_par.first)
            ret_x.emplace_back(subsegment(rev[rin[ret_x.back().first]]));

        ret_x.back().first = in[z];
 
        vector<P> ret_y;
        ret_y.emplace_back(subsegment(y));

        while(ret_y.back().first != z_par.first)
            ret_y.emplace_back(subsegment(rev[rin[ret_y.back().first]]));

        ret_y.back().first = in[z] + 1;

        return mp(ret_x, ret_y);
    }
 

};

