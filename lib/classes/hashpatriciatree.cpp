struct HashPatriciaTree{
    struct Node{
        bool is_elm = false;
        int ch = 0;
        int len = 0;
        int par = -1;
        int data_idx = -1;
        Hash hash;
    };

    static int fat(int l, int r){
        return r & (-1 << (31 - __builtin_clz(l ^ r)));
    };

    AVL_map<int,int> avl;
    vector<function<Hash(int)>> hash_func;
    vector<function<int(int)>> access_func;
    vector<Node> nodes;
    HashMap<uint64_t, int> hmap;
    vector<int> idxes;

    HashPatriciaTree() : nodes(1){
    }

    void make_fat(int x){
        int st = nodes[nodes[x].par].len;
        int en = nodes[x].len;
        int fa = fat(st, en);
        auto ha = hash_func[nodes[x].data_idx](fa);
        nodes[x].hash = ha;
        hmap.add(ha.concat(ha.l).h, x);
    }

    void make(int idx, int target, int len, int label){
        nodes.emplace_back();
        nodes.back().len = len;
        nodes.back().data_idx = idx;
        nodes.back().par = target;
        nodes[target].ch = avl.add(nodes[target].ch, label, nodes.size() - 1);
        make_fat(nodes.size() - 1);
    }

    void split(int idx, int target, int len, int match_len, int new_label, int root_label, int branch_label){
        int par = nodes[target].par;
        nodes.emplace_back();
        nodes.back().len = match_len;
        nodes.back().data_idx = idx;
        nodes.back().par = par;

        Hash ha = nodes[target].hash;
        hmap.erase(ha.concat(ha.l).h);

        nodes[par].ch = avl.add(nodes[par].ch, root_label, nodes.size() - 1);
        nodes.back().ch = avl.add(nodes.back().ch, branch_label, target);
        nodes[target].par = nodes.size() - 1;
        int target_siz = nodes.size() - 1;
        if(nodes.back().len != len)
            make(idx, nodes.size() - 1, len, new_label);
        make_fat(target);
        make_fat(target_siz);
    }

    // f(x): 長さxのprefixのハッシュを返す
    // g(x): x文字目を返す
    void insert(int m, function<Hash(int)> f, function<int(int)> g){
        hash_func.emplace_back(f);
        access_func.emplace_back(g);
        int len, x;
        tie(len, x) = match(m, f, g);
        assert(!(len || x) || (nodes[nodes[x].par].len < len && len <= nodes[x].len));
        if(len == nodes[x].len){
            if(len == m){
                idxes.emplace_back(x);
                nodes[x].data_idx = idxes.size() - 1;
                nodes[x].is_elm = true;
                return;
            }
            else
                make(idxes.size(), x, m, g(len));
        }
        else{
            split(idxes.size(), x, m, len, g(len), access_func[nodes[x].data_idx](nodes[nodes[x].par].len), access_func[nodes[x].data_idx](len));
        }
        idxes.emplace_back(nodes.size() - 1);
        nodes.back().is_elm = true;
    }

    int lcp(int ok, int ng, function<Hash(int)> f, function<Hash(int)> g){
        while(ng - ok > 1){
            int mid = (ok + ng) >> 1;
            (f(mid) == g(mid) ? ok : ng) = mid;
        }
        return ok;
    }

    // (マッチ長, ノード)
    pair<int,int> match(int m, function<Hash(int)> f, function<int(int)> g){
        int ok = 0, ng = m + 1;
        int x = 0;
        int ok_len = 0;
        while(ng - ok > 1){
            int mid = fat(ok + 1, ng - 1);
            Hash h = f(mid);
            int idx;
            bool fl;
            tie(idx, fl) = hmap.find(h.concat(h.l).h);
            if(fl){
                x = idx;
                ok_len = ok;
                ok = nodes[x].len;
            }
            else{
                ng = mid;
            }
        }
        int match_len;
        if(ok == 0){
            match_len = 0;
        }
        else{
            match_len = lcp(ok_len, min(m, nodes[x].len) + 1, f, hash_func[nodes[x].data_idx]);
            if(match_len < nodes[x].len){
                return {match_len, x};
            }
        }
        int label = g(ok);
        int ch;
        bool fl;
        tie(ch, fl) = avl.get(nodes[x].ch, label);
        if(!fl){
            assert(match_len <= m);
            return {match_len, x};
        }
        match_len = lcp(match_len, min(m, nodes[ch].len) + 1, f, hash_func[nodes[ch].data_idx]);
        assert(match_len <= m);
        return {match_len, ch};
    }
    template<typename T>
    static pair<function<Hash(int)>, function<int(int)>> build(T& s, vector<Hash>& v){
        auto f = [&v](int i){
            return v[i];
        };
        auto g = [&s](int i){
            return s[i];
        };
        return {f, g};
    }
    template<typename T>
    static pair<vector<function<Hash(int)>>, vector<function<int(int)>>> build_suffix(T& s, vector<Hash>& v){
        vector<function<Hash(int)>> fv;
        vector<function<int(int)>> gv;
        for(int j = 0; j < s.size(); ++j){
            auto f = [j, &v](int i){
                return v[i + j].sub(v[j]);
            };
            auto g = [j, &s](int i){
                return s[i + j];
            };
            fv.emplace_back(f);
            gv.emplace_back(g);
        }
        return {fv, gv};
    }
};
