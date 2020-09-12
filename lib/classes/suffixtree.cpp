struct SuffixTree{
    // Weinerでの構築 [0,n)が葉 nが根 [n+1,)が内部節点 番兵'$'
    struct Node{
        int pos = -1, par = -1, par_len = -1, dep = 0, slink = -1;
        int child = 0, plink = 0;
    };
    AVL_map<char,int> avl;
    int n;
    string s;
    vector<Node> nodes;
    vector<int> sa, sa_inv, lcp;
    SuffixTree(string& _s) : n(_s.size() + 1), s(_s + "$"), nodes(_s.size() + 3), sa(n), sa_inv(n), lcp(n){
        nodes[n].slink = n;
        nodes[n].par = n + 1;
        nodes[n].par_len = 1;
        for(int i = n - 1; i >= 0; --i)
            add(i);
        int cnt = 0;
        int lca = 0;
        make_sa(n, cnt, lca);
    }
    void make_sa(int x, int& cnt, int& lca){
        if(x < n){
            sa[cnt] = x;
            if(cnt > 0)
                lcp[cnt - 1] = lca;
            lca = nodes[x].dep;
            sa_inv[x] = cnt++;
        }
        for(auto p : avl.list(nodes[x].child)){
            lca = min(lca, nodes[x].dep);
            make_sa(p.second, cnt, lca);
        }
    }
    int child(int x, char c){
        auto res = avl.get(nodes[x].child, c);
        if(res.second)
            return res.first;
        else
            return -1;
    }
    int plink(int x, char c){
        if(x == n + 1)
            return n;
        auto res = avl.get(nodes[x].plink, c);
        if(res.second)
            return res.first;
        else
            return -1;
    }
    void attach(int par, int ch, char c, int len){
        nodes[par].child = avl.add(nodes[par].child, c, ch);
        nodes[ch].par_len = len;
        nodes[ch].par = par;
        nodes[ch].dep = nodes[par].dep + len;
    }
    void add(int i){
        int old = i + 1;
        vector<int> path(1, old);
        int vlen = s.size() - i;
        while(plink(old, s[i]) == -1){
            vlen -= nodes[old].par_len;
            old = nodes[old].par;
            path.emplace_back(old);
        }
        int now = plink(old, s[i]);
        int ch = child(now, s[i + nodes[now].dep]);
        int old_idx = path.size() - 1;
        if(ch != -1){
            int idx = nodes.size();
            nodes.emplace_back();
            int pos;
            for(pos = nodes[ch].pos - nodes[ch].par_len; s[pos] == s[i + vlen]; pos += nodes[old].par_len){
                old = path[--old_idx];
                vlen += nodes[old].par_len;
            }
            nodes[idx].pos = pos;
            attach(now, idx, s[nodes[ch].pos - nodes[ch].par_len], nodes[ch].par_len - (nodes[ch].pos - pos));
            attach(idx, ch, s[pos], nodes[ch].pos - pos);
            now = idx;
            nodes[old].plink = avl.add(nodes[old].plink, s[i], idx);
            nodes[idx].slink = old;
        }
        old = path.front();
        nodes[old].plink = avl.add(nodes[old].plink, s[i], i);
        nodes[i].slink = old;
        attach(now, i, s[i + nodes[now].dep], s.size() - (i + nodes[now].dep));
        nodes[i].pos = n;
    }
    void print(int st = -1, string t = ""){
        if(st == -1)
            st = n;
        if(st < n){
            cout << st << ": " << t << endl;
        }
        else{
            cout << "-" << ": " << t << endl;
        }
        for(auto p : avl.list(nodes[st].child)){
            int ch = p.second;
            t += s.substr(nodes[ch].pos - nodes[ch].par_len, nodes[ch].par_len);
            print(ch, t);
            t.erase(prev(t.end(), nodes[ch].par_len), t.end());
        }
    }
    // 途中でマッチした場合は (マッチした辺の子, 子側からの距離) を返す
    // ノードでマッチした場合は (マッチしたノード, 0) になる
    // マッチしなかったら (n, 0) を返す
    pair<int,int> match(string t){
        int i = 0;
        int x = n;
        auto res = avl.list(nodes[x].child);

        while(i != t.size()){
            int ch = child(x, t[i]);
            if(ch == -1)
                return {-1, -1};
            for(int j = 0; j < nodes[ch].par_len; ++i, ++j){
                if(i == t.size()){
                    return {ch, nodes[ch].par_len - j};
                }
                int k = nodes[ch].pos - nodes[ch].par_len + j;
                if(s[k] != t[i])
                    return {n, -1};
            }
            x = ch;
        }
        return {x, 0};
    }
};
