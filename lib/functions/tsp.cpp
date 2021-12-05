template<typename T>
vector<int> tsp(int n, vector<vector<T>> dist){
    // 始点=終点のTSP n <= 2 とかでバグりそうなので注意
    vector<int> v(n);
    vector<int> inv(n);
    // 適当に初期解を生成
    iota(v.begin(), v.end(), 0);
    T now_dist = 0;
    for(int i = 0; i < n; ++i){
        inv[v[i]] = i;
        now_dist += dist[v[i]][v[(i + 1) % n]];
    }
    // 前計算
    vector<vector<pair<T,int>>> near_vertexes(n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            near_vertexes[i].emplace_back(dist[i][j], j);
        }
        sort(near_vertexes[i].begin(), near_vertexes[i].end());
    }

    auto dist_check = [&](){
        auto di = dist[0][0];
        for(int i = 0; i < n; ++i){
            di += dist[v[i]][v[(i + 1) % n]];
        }
        assert(abs(now_dist - di) <= 1e-6);
    };

    auto update = [&](int i1, int i3){
        int i2 = (i1 + 1) % n;
        int i4 = (i3 + 1) % n;

        if(i1 == i3 || i2 == i3 || i1 == i4 || i2 == i4)
            return false;
        if(dist[v[i1]][v[i2]] + dist[v[i3]][v[i4]] <= dist[v[i1]][v[i3]] + dist[v[i2]][v[i4]])
            return false;

        auto improve = (dist[v[i1]][v[i2]] + dist[v[i3]][v[i4]]) - (dist[v[i1]][v[i3]] + dist[v[i2]][v[i4]]);
        now_dist -= improve;

        int d1 = (i2 < i3 ? i3 - i2 : i3 + n - i2);
        int d2 = (i4 < i1 ? i1 - i4 : i1 + n - i4);
        if(d1 >= d2){
            swap(i1, i3);
            swap(i2, i4);
        }

        int st = i2;
        int en = i2 < i3 ? i3 : i3 + n;
        while(st < en){
            inv[v[en % n]] = st % n;
            inv[v[st % n]] = en % n;
            swap(v[st % n], v[en % n]);
            ++st, --en;
        }
        // バグが怖い時用
        // dist_check();

        return true;
    };

    auto neighbors_search = [&](){
        for(int i = 0; i < n; ++i){
            int idx1 = i;
            int idx2 = (i + 1) % n;
            int v1 = v[idx1];
            int v2 = v[idx2];
            for(auto [d, v3] : near_vertexes[v1]){
                if(v3 == v2)
                    break;
                int idx3 = inv[v3];
                if(update(idx1, idx3)){
                    return true;
                }
            }
            for(auto [d, v4] : near_vertexes[v2]){
                if(v4 == v1)
                    break;
                int idx3 = (inv[v4] + n - 1) % n;
                if(update(idx1, idx3)){
                    return true;
                }
            }
        }
        return false;
    };
    auto double_bridge = [&](){
        vector<uint32_t> r{rnd() % n, rnd() % n, rnd() % n, rnd() % n};
        sort(r.begin(), r.end());
        if(r[0] == r[1] || r[1] == r[2] || r[2] == r[3]){
            return true;
        }
        // (r[3] + 1, r[0]) => (r[2] + 1, r[3]) => (r[1] + 1, r[2]) => (r[0] + 1, r[1])

        auto diff = dist[0][0];
        diff -= dist[v[r[0]]][v[r[0] + 1]];
        diff -= dist[v[r[1]]][v[r[1] + 1]];
        diff -= dist[v[r[2]]][v[r[2] + 1]];
        diff -= dist[v[r[3]]][v[(r[3] + 1) % n]];
        diff += dist[v[r[0]]][v[r[2] + 1]];
        diff += dist[v[r[3]]][v[r[1] + 1]];
        diff += dist[v[r[2]]][v[r[0] + 1]];
        diff += dist[v[r[1]]][v[(r[3] + 1) % n]];
        now_dist += diff;
        vector<int> nex;
        nex.reserve(n);
        for(int i = r[3] + 1; i < n; ++i)
            nex.emplace_back(v[i]);
        for(int i = 0; i <= r[0]; ++i)
            nex.emplace_back(v[i]);
        for(int i = r[2] + 1; i <= r[3]; ++i)
            nex.emplace_back(v[i]);
        for(int i = r[1] + 1; i <= r[2]; ++i)
            nex.emplace_back(v[i]);
        for(int i = r[0] + 1; i <= r[1]; ++i)
            nex.emplace_back(v[i]);
        v = move(nex);
        return false;
    };

    auto best = make_pair(now_dist, v);
    for(int i = 0; i < 1000; ++i){
        if(i){
            while(double_bridge());
        }
        while(neighbors_search());
        if(!chmin(best, make_pair(now_dist, v))){
            tie(now_dist, v) = best;
        }
    }
    for(int i = 0; i < n; ++i){
        if(v[i] == 0){
            vector<int> res;
            for(int j = 0; j < n; ++j){
                res.emplace_back(v[(i + j) % n]);
            }
            return res;
        }
    }
    // return now_dist;
    return v;
}

