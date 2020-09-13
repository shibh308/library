---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: verify/suffixtree.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/suffixtree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 14:27:28+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/avl_map.cpp.html">lib/classes/avl_map.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/classes/suffixtree.cpp.html">lib/classes/suffixtree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include <bits/stdc++.h>

using namespace std;


#include "../lib/classes/avl_map.cpp"
#include "../lib/classes/suffixtree.cpp"


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



```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/suffixtree.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include <bits/stdc++.h>

using namespace std;


#line 1 "lib/classes/avl_map.cpp"
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
        vector<pair<T, U>> v;
        stack<pair<int,bool>> sta;
        sta.emplace(x, false);
        bool add;
        while(!sta.empty()){
            tie(x, add) = sta.top();
            sta.pop();
            if(x == 0)
                continue;
            if(add)
                v.emplace_back(nodes[x].key, nodes[x].val);
            else{
                if(nodes[x].c[1])
                    sta.emplace(nodes[x].c[1], false);
                sta.emplace(x, true);
                if(nodes[x].c[0])
                    sta.emplace(nodes[x].c[0], false);
            }
        }
        return v;
    }
};
#line 1 "lib/classes/suffixtree.cpp"
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
        make_sa();
    }
    void make_sa(){
        stack<pair<int,bool>> sta;
        int cnt = 0;
        int lca = 0;
        sta.emplace(n, false);
        int x;
        bool is_lca;
        while(!sta.empty()){
            tie(x, is_lca) = sta.top();
            sta.pop();
            if(is_lca){
                lca = min(lca, x);
                continue;
            }
            if(x < n){
                sa[cnt] = x;
                if(cnt > 0)
                    lcp[cnt - 1] = lca;
                lca = nodes[x].dep;
                sa_inv[x] = cnt++;
            }
            auto chi = avl.list(nodes[x].child);
            for(int i = chi.size() - 1; i >= 0; --i){
                sta.emplace(nodes[x].dep, true);
                sta.emplace(chi[i].second, false);
            }
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
#line 10 "verify/suffixtree.test.cpp"


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



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

