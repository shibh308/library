struct EulerTour{
    int n;
    vector<int> in, out;
    EulerTour(vector<vector<int>>& edges, int par = 0) : n(edges.size()), in(n, -1), out(n, -1){
        int cnt = 0;
        function<void(int)> f = [&](int x){
            in[x] = cnt++;
            for(auto y : edges[x]){
                if(in[y] == -1)
                    f(y);
            }
            out[x] = cnt;
        };
        f(par);
    }
    int get_pos(int x){
        return in[x];
    }
    // 自身を含みたくない場合は(in[x] + 1, out[x])
    pair<int,int> get_subtree(int x){
        return make_pair(in[x], out[x]);
    }
}

