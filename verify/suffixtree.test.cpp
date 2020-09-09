#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include <bits/stdc++.h>

using namespace std;


#include "../lib/classes/avl_map.cpp"
#include "../lib/classes/suffixtree.cpp"

template <typename T, typename U>
struct AVL_map{
    struct Node{
        int height;
        T key;
        U val;
        Node(T key, U val) : key(key), val(val), height(1){c[0] = 0; c[1] = 0;}
        int c[2];
    };

    vector<Node> nodes;
    stack<int> st;

    AVL_map(){
        nodes.emplace_back(T(), U());
        nodes[0].height = 0;
    }
    template <bool inv>
    int balance_factor(int x){return (nodes[nodes[x].c[0]].height - nodes[nodes[x].c[1]].height) * (inv ? -1 : 1);}
    void _update(int x){
        if(x == 0)
            return;
        nodes[x].height = max(nodes[nodes[x].c[0]].height, nodes[nodes[x].c[1]].height) + 1;
    }
    template <bool is_right>
    int rotate(int x){
        int y = nodes[x].c[1 ^ is_right];
        nodes[x].c[1 ^ is_right] = nodes[y].c[0 ^ is_right];
        nodes[y].c[0 ^ is_right] = x;
        _update(x);
        _update(y);
        return y;
    }
    template <bool inv>
    int _balance(int x){
        if(balance_factor<inv>(x) == 2){
            if(balance_factor<inv>(nodes[x].c[0 ^ inv]) < 0)
                nodes[x].c[0 ^ inv] = rotate<inv>(nodes[x].c[0 ^ inv]);
            x = rotate<1 ^ inv>(x);
        }
        return x;
    }
    int balance(int x){
        x = _balance<false>(x);
        x = _balance<true>(x);
        _update(x);
        return x;
    }
    int add(int x, T key, U val){
        if(x == 0){
            if(st.empty()){
                nodes.emplace_back(key, val);
                return nodes.size() - 1;
            }
            else{
                int y = st.top();
                st.pop();
                nodes[y] = Node(key, val);
                return y;
            }
        }
        else if(key == nodes[x].key)
            nodes[x].val = val;
        else if(key < nodes[x].key)
            nodes[x].c[0] = add(nodes[x].c[0], key, val);
        else
            nodes[x].c[1] = add(nodes[x].c[1], key, val);
        x = balance(x);
        return x;
    }
    // 子が片方しかない時にノードを削除する
    int _erase_top(int x, bool del){
        for(int i = 0; i < 2; ++i){
            if(nodes[x].c[i] == 0){
                int y = nodes[x].c[i ^ 1];
                if(del)
                    st.push(x);
                return y;
            }
        }
    }
    // 最小の要素をdstにコピーしてから削除する
    int _copy_erase(int x, int dst, bool del){
        if(nodes[x].c[0] == 0){
            nodes[dst].val = nodes[x].val;
            return _erase_top(x, del);
        }
        nodes[x].c[0] = _copy_erase(nodes[x].c[0], dst, del);
        x = balance(x);
        return x;
    }
    int erase(int x, T key, bool del = true){
        if(key < nodes[x].key)
            nodes[x].c[0] = erase(nodes[x].c[0], key, del);
        else if(nodes[x].key < key)
            nodes[x].c[1] = erase(nodes[x].c[1], key, del);
        else{
            if(nodes[x].c[0] == 0 || nodes[x].c[1] == 0)
                return _erase_top(x, del);
            nodes[x].c[1] = _copy_erase(nodes[x].c[1], x, del);
        }
        x = balance(x);
        return x;
    }
    pair<U, bool> get(int x, T key){
        if(x == 0)
            return {U(), false};
        else if(key == nodes[x].key)
            return {nodes[x].val, true};
        else if(key < nodes[x].key)
            return get(nodes[x].c[0], key);
        else
            return get(nodes[x].c[1], key);
    }
    vector<pair<T, U>> list(int x){
        if(x == 0)
            return vector<pair<T, U>>();
        vector<pair<T, U>> v;
        if(nodes[x].c[0]){
            auto res = list(nodes[x].c[0]);
            v.insert(v.end(), make_move_iterator(res.begin()), make_move_iterator(res.end()));
        }
        v.emplace_back(nodes[x].key, nodes[x].val);
        if(nodes[x].c[1]){
            auto res = list(nodes[x].c[1]);
            v.insert(v.end(), make_move_iterator(res.begin()), make_move_iterator(res.end()));
        }
        return v;
    }
};


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
    vector<int> sa, sa_inv;
    SuffixTree(string& _s) : n(_s.size() + 1), s(_s + "$"), nodes(_s.size() + 3), sa(n), sa_inv(n){
        nodes[n].slink = n;
        nodes[n].par = n + 1;
        nodes[n].par_len = 1;
        for(int i = n - 1; i >= 0; --i)
            add(i);
        int cnt = 0;
        make_sa(0, cnt);
    }
    void make_sa(int x, int& cnt){
        if(x < n){
            sa[cnt] = x;
            sa_inv[x] = cnt++;
        }
        for(auto p : avl.list(nodes[x].child))
            make_sa(p.second, cnt);
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


signed main(){
    string s, t;
    cin >> s >> t;
    SuffixTree st(s);
    vector<int> res;
    res.reserve(s.size());
    stack<int> sta;
    int node = st.match(t).first;
    sta.push(node);
    while(!sta.empty()){
        int x = sta.top();
        sta.pop();
        if(x == st.n)
            continue;
        if(x < st.n)
            res.emplace_back(x);
        for(auto p : st.avl.list(st.nodes[x].child)){
            sta.push(p.second);
        }
    }
    sort(res.begin(), res.end());
    for(auto x : res)
        printf("%d\n", x);
}


