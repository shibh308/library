#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1585"

#include <bits/stdc++.h>

using namespace std;

using i64 = int64_t;

#include "../lib/classes/rollinghashmonoid.cpp"
#include "../lib/classes/hashmap.cpp"
#include "../lib/classes/avl_map.cpp"
#include "../lib/classes/hashpatriciatree.cpp"
#include "../lib/classes/bitvector.cpp"
#include "../lib/classes/waveletmatrix.cpp"


signed main(){
    HashPatriciaTree tree;
    string s;
    int q;
    cin >> s >> q;

    int n = s.size();
    vector<Hash> sh = Hash::make(s);
    auto s_res = HashPatriciaTree::build_suffix(s, sh);
    for(int i = 0; i < n; ++i){
        tree.insert(n - i, s_res.first[i], s_res.second[i]);
    }

    vector<int> v;
    int k = tree.nodes.size();
    vector<int> in(k), out(k);
    function<void(int)> f = [&](int x){
        in[x] = v.size();
        v.emplace_back(tree.nodes[x].is_elm ? tree.nodes[x].data_idx : n);
        for(auto p : tree.avl.list(tree.nodes[x].ch)){
            f(p.second);
        }
        out[x] = v.size();
    };
    f(0);

    WaveletMatrix<int, 20> wm(v);

    for(int i = 0; i < q; ++i){
        int l, r;
        string t;
        cin >> l >> r >> t;
        ++r;
        auto h = Hash::make(t);
        auto res = HashPatriciaTree::build(t, h);
        int len, node;
        tie(len, node) = tree.match(t.size(), res.first, res.second);
        if(len < t.size()){
            cout << 0 << endl;
            continue;
        }
        int in_x = in[node];
        int out_x = out[node];

        int left = l;
        int right = max(left, min(int(v.size()), r + 1 - int(t.size())));
        if(right <= left)
            cout << 0 << endl;
        else
            cout << wm.count_range(in_x, out_x, left, right) << endl;
    }
}

