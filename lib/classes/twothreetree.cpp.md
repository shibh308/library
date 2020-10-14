---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/twothreetree.test.cpp
    title: verify/twothreetree.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/twothreetree.cpp\"\ntemplate <typename T>\n\
    struct TwoThreeTree{\n    struct Node;\n    using Index = typename MemoryPool<Node>::Index;\n\
    \    struct Node{\n        int siz;\n        bool leaf;\n        T mi;\n     \
    \   vector<T> v;\n        vector<Index> c;\n        Node(T val) : siz(1), leaf(true),\
    \ v(1, val), c(0), mi(val){}\n        Node() : siz(0), leaf(false), v(0), c(0){}\n\
    \    };\n    MemoryPool<Node> pool;\n    static constexpr Index nil = {-1};\n\
    \    Index root;\n    TwoThreeTree(){root = nil;}\n\n    int size(){return root\
    \ == nil ? 0 : pool[root].siz;}\n\n    Index insert(T x, Index idx){\n       \
    \ Node& node = pool[idx];\n        if(node.leaf){\n            // \u8449\u306F\
    \u7121\u8996\u3059\u308B\u305F\u3081\n            int ins = 0;\n            for(;\
    \ node.v[ins] <= x && ins < node.v.size(); ++ins);\n            for(; ins < node.v.size();\
    \ ++ins)\n                swap(x, node.v[ins]);\n            node.v.emplace_back(x);\n\
    \            node.mi = node.v[0];\n        }\n        else{\n            int ins\
    \ = 0;\n            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);\n \
    \           Index ret = insert(x, node.c[ins]);\n            if(ret != nil){\n\
    \                T key = pool[ret].mi;\n                for(; ins < node.v.size();\
    \ ++ins){\n                    swap(key, node.v[ins]);\n                    swap(ret,\
    \ node.c[ins + 1]);\n                }\n                node.v.emplace_back(key);\n\
    \                node.c.emplace_back(ret);\n            }\n            node.mi\
    \ = pool[node.c[0]].mi;\n        }\n        ++node.siz;\n        if(node.v.size()\
    \ > 2){\n            assert(node.v.size() == 3);\n            assert(node.leaf\
    \ || node.c.size() == 4);\n            Index new_idx = pool.alloc();\n       \
    \     auto& new_node = pool[new_idx];\n            new_node.c.clear();\n     \
    \       new_node.c.shrink_to_fit();\n            assert(new_node.c.empty());\n\
    \            new_node.leaf = node.leaf;\n            if(node.leaf){\n        \
    \        new_node.v = {node.v[2]};\n                new_node.mi = node.v[2];\n\
    \                node.v.pop_back();\n                new_node.siz = 1;\n     \
    \           --node.siz;\n            }\n            else{\n                node.v\
    \ = {node.v[0]};\n                new_node.v = {node.v[2]};\n                new_node.c\
    \ = {node.c[2], node.c[3]};\n                new_node.mi = pool[node.c[2]].mi;\n\
    \                node.c = {node.c[0], node.c[1]};\n\n                new_node.siz\
    \ = pool[new_node.c[0]].siz + pool[new_node.c[1]].siz;\n                node.siz\
    \ -= new_node.siz;\n            }\n            assert(!node.leaf || node.c.empty());\n\
    \            return new_idx;\n        }\n        return nil;\n    }\n\n    void\
    \ insert(T x){\n        if(root == nil){\n            root = pool.alloc();\n \
    \           pool[root] = Node(x);\n            assert(pool[root].c.empty());\n\
    \        }\n        else{\n            Index res = insert(x, root);\n        \
    \    if(res != nil){\n                Index new_idx = pool.alloc();\n        \
    \        auto& new_node = pool[new_idx];\n                new_node.leaf = false;\n\
    \                new_node.v = {pool[res].mi};\n                new_node.c = {root,\
    \ res};\n                new_node.mi = pool[root].mi;\n                new_node.siz\
    \ = pool[root].siz + pool[res].siz;\n                assert(new_node.v.size()\
    \ == 1);\n                assert(new_node.c.size() == 2);\n                root\
    \ = new_idx;\n            }\n        }\n        Index idx = root;\n        while(!pool[idx].leaf)\n\
    \            idx = pool[idx].c[0];\n    }\n\n    // (\u524A\u9664\u3067\u304D\u305F\
    \u304B, \u8A72\u5F53\u30CE\u30FC\u30C9\u304C\u524A\u9664\u3055\u308C\u305F\u304B\
    )\n    short erase(T x, Index idx){\n        Node& node = pool[idx];\n       \
    \ if(node.leaf){\n            if(node.v.size() == 1){\n                if(node.v[0]\
    \ != x)\n                    return 0;\n                return 2;\n          \
    \  }\n            else{\n                assert(node.v.size() == 2);\n       \
    \         bool fl = (node.v[1] == x);\n                if(node.v[fl] != x)\n \
    \                   return 0;\n                node.v = {node.v[fl ^ 1]};\n  \
    \              node.mi = node.v[0];\n                --node.siz;\n           \
    \     return 1;\n            }\n        }\n        else{\n            int ins\
    \ = 0;\n            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);\n \
    \           short res = erase(x, node.c[ins]);\n            node.mi = pool[node.c[0]].mi;\n\
    \            if(res)\n                --node.siz;\n            if(res == 3){\n\
    \                // \u5B50\u306F\u307E\u3060\u524A\u9664\u3055\u308C\u3066\u306A\
    \u3044\u306E\u3067, \u5144\u5F1F\u3067\u4F75\u5408\u3059\u308B\u51E6\u7406\u3092\
    \u66F8\u304F\n                assert(node.c.size() == 2 || node.c.size() == 3);\n\
    \                // \u5144\u5F1F\u304B\u3089\u30CE\u30FC\u30C9\u3092\u53D6\u3063\
    \u3066\u304F\u308B\n                if(ins + 1 < node.c.size() && pool[node.c[ins\
    \ + 1]].v.size() == 2){\n                    // \u53F3\u3068\u30DE\u30FC\u30B8\
    \n                    Node& target = pool[node.c[ins]];\n                    Node&\
    \ bro = pool[node.c[ins + 1]];\n                    assert(target.v.size() ==\
    \ 1);\n                    // target.v = {target.v[0]};\n                    target.v\
    \ = {pool[bro.c[0]].mi};\n                    bro.v = {bro.v[1]};\n          \
    \          bro.siz -= pool[bro.c[0]].siz;\n                    target.siz += pool[bro.c[0]].siz;\n\
    \                    target.c = {target.c[0], bro.c[0]};\n                   \
    \ bro.c = {bro.c[1], bro.c[2]};\n                    node.v[ins] = bro.mi = pool[bro.c[0]].mi;\n\
    \                }\n                else if(ins && pool[node.c[ins - 1]].v.size()\
    \ == 2){\n                    // \u5DE6\u3068\u30DE\u30FC\u30B8\n            \
    \        Node& bro = pool[node.c[ins - 1]];\n                    Node& target\
    \ = pool[node.c[ins]];\n                    bro.siz -= pool[bro.c[2]].siz;\n \
    \                   target.siz += pool[bro.c[2]].siz;\n                    target.c\
    \ = {bro.c[2], target.c[0]};\n                    target.v[0] = pool[target.c[1]].mi;\n\
    \                    bro.v.pop_back();\n                    bro.c.pop_back();\n\
    \                    node.v[ins - 1] = target.mi = pool[target.c[0]].mi;\n   \
    \             }\n                else{\n                    // \u89AA\u306E\u30CE\
    \u30FC\u30C9\u304C2\u3064\u306A\u306E\u3067\u524A\u9664\u3057\u3066\u89E3\u6C7A\
    \u3059\u308B\u30D1\u30BF\u30FC\u30F3\n                    if(node.v.size() ==\
    \ 2){\n                        // \u30DE\u30FC\u30B8\u3057\u305F\u5F8C\u306B\u89E3\
    \u6C7A\u3059\u308B\u30D1\u30BF\u30FC\u30F3\n                        if(ins + 1\
    \ < node.v.size()){\n                            // \u53F3\u3068\u30DE\u30FC\u30B8\
    \u3057\u3066\u89E3\u6C7A\u3055\u305B\u308B\n                            Node&\
    \ target = pool[node.c[ins]];\n                            Node& bro = pool[node.c[ins\
    \ + 1]];\n                            assert(target.v.size() == 1 && target.c.size()\
    \ == 1);\n                            if(!(bro.v.size() == 1 && bro.c.size() ==\
    \ 2)){\n                                print();\n                           \
    \ }\n                            assert(bro.v.size() == 1 && bro.c.size() == 2);\n\
    \                            target.siz += bro.siz;\n                        \
    \    target.v = {pool[bro.c[0]].mi, pool[bro.c[1]].mi};\n                    \
    \        target.c = {target.c[0], bro.c[0], bro.c[1]};\n                     \
    \   }\n                        else{\n                            --ins;\n   \
    \                         Node& target = pool[node.c[ins + 1]];\n            \
    \                Node& bro = pool[node.c[ins]];\n                            assert(target.v.size()\
    \ == 1 && target.c.size() == 1);\n                            assert(bro.v.size()\
    \ == 1 && bro.c.size() == 2);\n                            bro.siz += target.siz;\n\
    \                            bro.v = {pool[bro.c[1]].mi, pool[target.c[0]].mi};\n\
    \                            bro.c.emplace_back(target.c[0]);\n              \
    \          }\n                        ++ins;\n                        for(; ins\
    \ < node.v.size(); ++ins){\n                            if(ins + 1 != node.v.size())\n\
    \                                swap(node.v[ins], node.v[ins + 1]);\n       \
    \                     swap(node.c[ins], node.c[ins + 1]);\n                  \
    \      }\n                        pool.free(node.c.back());\n                \
    \        node.v.pop_back();\n                        node.c.pop_back();\n    \
    \                    assert(node.v.size() == 1);\n                    }\n    \
    \                else{\n                        // 2\u3064\u3092\u30DE\u30FC\u30B8\
    \u3059\u308B\u30D1\u30BF\u30FC\u30F3\n                        Node& l = pool[node.c[0]];\n\
    \                        Node& r = pool[node.c[1]];\n                        assert(l.c.size()\
    \ + r.c.size() == 3);\n                        l.c.insert(l.c.end(), r.c.begin(),\
    \ r.c.end());\n                        assert(l.c.size() == 3);\n            \
    \            l.siz += r.siz;\n                        l.v = {pool[l.c[1]].mi,\
    \ pool[l.c[2]].mi};\n                        pool.free(node.c[1]);\n         \
    \               node.c.pop_back();\n                        assert(node.c.size()\
    \ == 1);\n                        node.v = {pool[l.c[1]].mi};\n              \
    \          node.mi = l.mi;\n                        node.siz = l.siz;\n      \
    \                  return 3;\n                    }\n                }\n     \
    \           node.v[0] = pool[node.c[1]].mi;\n                node.mi = pool[node.c[0]].mi;\n\
    \                return 1;\n            }\n            else if(res == 2){\n  \
    \              if(node.v.size() == 2){\n                    pool.free(node.c[ins]);\n\
    \                    for(; ins < node.v.size(); ++ins){\n                    \
    \    if(ins + 1 != node.v.size())\n                            swap(node.v[ins],\
    \ node.v[ins + 1]);\n                        swap(node.c[ins], node.c[ins + 1]);\n\
    \                    }\n                    node.v.pop_back();\n             \
    \       node.c.pop_back();\n                    node.mi = pool[node.c[0]].mi;\n\
    \                    return 1;\n                }\n                else{\n   \
    \                 assert(node.v.size() == 1);\n                    assert(node.c.size()\
    \ == 2);\n                    // \u5144\u5F1F\u30CE\u30FC\u30C9\u5206\u306E\u51E6\
    \u7406\u3092\u89AA\u306B\u4EFB\u305B\u308B\u3088\u3046\u306B\u3059\u308B\n   \
    \                 Node& ch = pool[node.c[ins ^ 1]];\n                    if(ch.v.size()\
    \ == 2){\n                        vector<int> vs = ch.v;\n                   \
    \     vector<Index> cs = ch.c;\n                        pool[node.c[0]].siz =\
    \ pool[node.c[1]].siz = 1;\n                        pool[node.c[0]].v = {vs[0]};\n\
    \                        pool[node.c[1]].v = {vs[1]};\n                      \
    \  pool[node.c[0]].mi = pool[node.c[0]].v[0];\n                        node.v[0]\
    \ = pool[node.c[1]].mi = pool[node.c[1]].v[0];\n                        node.siz\
    \ = 2;\n                        node.mi = pool[node.c[0]].mi;\n              \
    \          return 1;\n                    }\n                    node.c = {node.c[ins\
    \ ^ 1]};\n                    assert(ch.v.size() == 1);\n                    node.v\
    \ = {ch.mi};\n                    node.mi = ch.mi;\n                    node.siz\
    \ = ch.siz;\n                    assert(node.c.size() == 1);\n               \
    \     return 3;\n                }\n            }\n            if(ins)\n     \
    \           node.v[ins - 1] = pool[node.c[ins]].mi;\n            return res;\n\
    \        }\n    }\n\n    bool erase(T x){\n        if(root == nil)\n         \
    \   return false;\n        int res = erase(x, root);\n        if(res == 2)\n \
    \           root = nil;\n        if(res == 3){\n            // \u89AA\u3092\u898B\
    \u308B\u51E6\u7406\u3067\u8A70\u307E\u3063\u3066\u308B(\u9AD8\u3055\u304C\u6E1B\
    \u308B)\n            assert(pool[root].v.size() == 1);\n            assert(pool[root].c.size()\
    \ == 1);\n            Index new_root = pool[root].c[0];\n            pool.free(root);\n\
    \            root = new_root;\n        }\n        return res;\n    }\n\n    pair<T,\
    \ bool> lower_bound(T x, Index idx = nil){\n        if(idx == nil)\n         \
    \   idx = root;\n        if(root == nil)\n            return make_pair(T(), false);\n\
    \        bool fl = false;\n        T nex_val;\n        while(1){\n           \
    \ Node& node = pool[idx];\n            int ins = 0;\n            if(node.leaf){\n\
    \                for(; node.v[ins] < x && ins < node.v.size(); ++ins);\n     \
    \           assert(node.c.empty());\n                if(ins == node.v.size())\n\
    \                    return make_pair(fl ? nex_val : T(), fl);\n             \
    \   return make_pair(pool[idx].v[ins], true);\n            }\n            for(;\
    \ node.v[ins] <= x && ins < node.v.size(); ++ins);\n            idx = node.c[ins];\n\
    \            if(ins + 1 < node.c.size()){\n                fl = true;\n      \
    \          nex_val = pool[node.c[ins + 1]].mi;\n            }\n        }\n   \
    \ }\n\n    void print(Index idx = nil, int cnt = 0){\n        if(idx == nil)\n\
    \            idx = root;\n        if(idx == nil){\n            cout << \"nil(0)[0]\"\
    \ << endl;\n            return;\n        }\n        string cs = \"\";\n      \
    \  for(int i = 0; i < cnt; ++i)\n            cs += ' ';\n        auto& node =\
    \ pool[idx];\n        // cout << cs << \"idx: \" << idx << \" val: \" << node.v[0]\
    \ <<  \" / leaf: \" << node.leaf << endl;\n        for(int i = 0; i < max(node.v.size(),\
    \ node.c.size()); ++i){\n            if(!node.leaf){\n                if(i < node.c.size()){\n\
    \                    print(node.c[i], cnt + 8);\n                }\n         \
    \   }\n            if(i < node.v.size()){\n                if(i == 0){\n     \
    \               cout << cs << \" \" << node.v[i] << \" (\" << node.mi << \"){\"\
    \ << node.siz << \"}[\" << idx.idx << \"]\";\n                    if(node.leaf){\n\
    \                        cout << \"[\";\n                        for(int i = 0;\
    \ i < node.c.size(); ++i){\n                            cout << node.c[i].idx;\n\
    \                            if(i)\n                                cout << \"\
    /\";\n                        }\n                        cout << \"]\" << endl;\n\
    \                    }\n                    else\n                        cout\
    \ << endl;\n                }\n                else\n                    cout\
    \ << cs << \" \" << node.v[i] << endl;\n            }\n        }\n    }\n};\n\n"
  code: "template <typename T>\nstruct TwoThreeTree{\n    struct Node;\n    using\
    \ Index = typename MemoryPool<Node>::Index;\n    struct Node{\n        int siz;\n\
    \        bool leaf;\n        T mi;\n        vector<T> v;\n        vector<Index>\
    \ c;\n        Node(T val) : siz(1), leaf(true), v(1, val), c(0), mi(val){}\n \
    \       Node() : siz(0), leaf(false), v(0), c(0){}\n    };\n    MemoryPool<Node>\
    \ pool;\n    static constexpr Index nil = {-1};\n    Index root;\n    TwoThreeTree(){root\
    \ = nil;}\n\n    int size(){return root == nil ? 0 : pool[root].siz;}\n\n    Index\
    \ insert(T x, Index idx){\n        Node& node = pool[idx];\n        if(node.leaf){\n\
    \            // \u8449\u306F\u7121\u8996\u3059\u308B\u305F\u3081\n           \
    \ int ins = 0;\n            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);\n\
    \            for(; ins < node.v.size(); ++ins)\n                swap(x, node.v[ins]);\n\
    \            node.v.emplace_back(x);\n            node.mi = node.v[0];\n     \
    \   }\n        else{\n            int ins = 0;\n            for(; node.v[ins]\
    \ <= x && ins < node.v.size(); ++ins);\n            Index ret = insert(x, node.c[ins]);\n\
    \            if(ret != nil){\n                T key = pool[ret].mi;\n        \
    \        for(; ins < node.v.size(); ++ins){\n                    swap(key, node.v[ins]);\n\
    \                    swap(ret, node.c[ins + 1]);\n                }\n        \
    \        node.v.emplace_back(key);\n                node.c.emplace_back(ret);\n\
    \            }\n            node.mi = pool[node.c[0]].mi;\n        }\n       \
    \ ++node.siz;\n        if(node.v.size() > 2){\n            assert(node.v.size()\
    \ == 3);\n            assert(node.leaf || node.c.size() == 4);\n            Index\
    \ new_idx = pool.alloc();\n            auto& new_node = pool[new_idx];\n     \
    \       new_node.c.clear();\n            new_node.c.shrink_to_fit();\n       \
    \     assert(new_node.c.empty());\n            new_node.leaf = node.leaf;\n  \
    \          if(node.leaf){\n                new_node.v = {node.v[2]};\n       \
    \         new_node.mi = node.v[2];\n                node.v.pop_back();\n     \
    \           new_node.siz = 1;\n                --node.siz;\n            }\n  \
    \          else{\n                node.v = {node.v[0]};\n                new_node.v\
    \ = {node.v[2]};\n                new_node.c = {node.c[2], node.c[3]};\n     \
    \           new_node.mi = pool[node.c[2]].mi;\n                node.c = {node.c[0],\
    \ node.c[1]};\n\n                new_node.siz = pool[new_node.c[0]].siz + pool[new_node.c[1]].siz;\n\
    \                node.siz -= new_node.siz;\n            }\n            assert(!node.leaf\
    \ || node.c.empty());\n            return new_idx;\n        }\n        return\
    \ nil;\n    }\n\n    void insert(T x){\n        if(root == nil){\n           \
    \ root = pool.alloc();\n            pool[root] = Node(x);\n            assert(pool[root].c.empty());\n\
    \        }\n        else{\n            Index res = insert(x, root);\n        \
    \    if(res != nil){\n                Index new_idx = pool.alloc();\n        \
    \        auto& new_node = pool[new_idx];\n                new_node.leaf = false;\n\
    \                new_node.v = {pool[res].mi};\n                new_node.c = {root,\
    \ res};\n                new_node.mi = pool[root].mi;\n                new_node.siz\
    \ = pool[root].siz + pool[res].siz;\n                assert(new_node.v.size()\
    \ == 1);\n                assert(new_node.c.size() == 2);\n                root\
    \ = new_idx;\n            }\n        }\n        Index idx = root;\n        while(!pool[idx].leaf)\n\
    \            idx = pool[idx].c[0];\n    }\n\n    // (\u524A\u9664\u3067\u304D\u305F\
    \u304B, \u8A72\u5F53\u30CE\u30FC\u30C9\u304C\u524A\u9664\u3055\u308C\u305F\u304B\
    )\n    short erase(T x, Index idx){\n        Node& node = pool[idx];\n       \
    \ if(node.leaf){\n            if(node.v.size() == 1){\n                if(node.v[0]\
    \ != x)\n                    return 0;\n                return 2;\n          \
    \  }\n            else{\n                assert(node.v.size() == 2);\n       \
    \         bool fl = (node.v[1] == x);\n                if(node.v[fl] != x)\n \
    \                   return 0;\n                node.v = {node.v[fl ^ 1]};\n  \
    \              node.mi = node.v[0];\n                --node.siz;\n           \
    \     return 1;\n            }\n        }\n        else{\n            int ins\
    \ = 0;\n            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);\n \
    \           short res = erase(x, node.c[ins]);\n            node.mi = pool[node.c[0]].mi;\n\
    \            if(res)\n                --node.siz;\n            if(res == 3){\n\
    \                // \u5B50\u306F\u307E\u3060\u524A\u9664\u3055\u308C\u3066\u306A\
    \u3044\u306E\u3067, \u5144\u5F1F\u3067\u4F75\u5408\u3059\u308B\u51E6\u7406\u3092\
    \u66F8\u304F\n                assert(node.c.size() == 2 || node.c.size() == 3);\n\
    \                // \u5144\u5F1F\u304B\u3089\u30CE\u30FC\u30C9\u3092\u53D6\u3063\
    \u3066\u304F\u308B\n                if(ins + 1 < node.c.size() && pool[node.c[ins\
    \ + 1]].v.size() == 2){\n                    // \u53F3\u3068\u30DE\u30FC\u30B8\
    \n                    Node& target = pool[node.c[ins]];\n                    Node&\
    \ bro = pool[node.c[ins + 1]];\n                    assert(target.v.size() ==\
    \ 1);\n                    // target.v = {target.v[0]};\n                    target.v\
    \ = {pool[bro.c[0]].mi};\n                    bro.v = {bro.v[1]};\n          \
    \          bro.siz -= pool[bro.c[0]].siz;\n                    target.siz += pool[bro.c[0]].siz;\n\
    \                    target.c = {target.c[0], bro.c[0]};\n                   \
    \ bro.c = {bro.c[1], bro.c[2]};\n                    node.v[ins] = bro.mi = pool[bro.c[0]].mi;\n\
    \                }\n                else if(ins && pool[node.c[ins - 1]].v.size()\
    \ == 2){\n                    // \u5DE6\u3068\u30DE\u30FC\u30B8\n            \
    \        Node& bro = pool[node.c[ins - 1]];\n                    Node& target\
    \ = pool[node.c[ins]];\n                    bro.siz -= pool[bro.c[2]].siz;\n \
    \                   target.siz += pool[bro.c[2]].siz;\n                    target.c\
    \ = {bro.c[2], target.c[0]};\n                    target.v[0] = pool[target.c[1]].mi;\n\
    \                    bro.v.pop_back();\n                    bro.c.pop_back();\n\
    \                    node.v[ins - 1] = target.mi = pool[target.c[0]].mi;\n   \
    \             }\n                else{\n                    // \u89AA\u306E\u30CE\
    \u30FC\u30C9\u304C2\u3064\u306A\u306E\u3067\u524A\u9664\u3057\u3066\u89E3\u6C7A\
    \u3059\u308B\u30D1\u30BF\u30FC\u30F3\n                    if(node.v.size() ==\
    \ 2){\n                        // \u30DE\u30FC\u30B8\u3057\u305F\u5F8C\u306B\u89E3\
    \u6C7A\u3059\u308B\u30D1\u30BF\u30FC\u30F3\n                        if(ins + 1\
    \ < node.v.size()){\n                            // \u53F3\u3068\u30DE\u30FC\u30B8\
    \u3057\u3066\u89E3\u6C7A\u3055\u305B\u308B\n                            Node&\
    \ target = pool[node.c[ins]];\n                            Node& bro = pool[node.c[ins\
    \ + 1]];\n                            assert(target.v.size() == 1 && target.c.size()\
    \ == 1);\n                            if(!(bro.v.size() == 1 && bro.c.size() ==\
    \ 2)){\n                                print();\n                           \
    \ }\n                            assert(bro.v.size() == 1 && bro.c.size() == 2);\n\
    \                            target.siz += bro.siz;\n                        \
    \    target.v = {pool[bro.c[0]].mi, pool[bro.c[1]].mi};\n                    \
    \        target.c = {target.c[0], bro.c[0], bro.c[1]};\n                     \
    \   }\n                        else{\n                            --ins;\n   \
    \                         Node& target = pool[node.c[ins + 1]];\n            \
    \                Node& bro = pool[node.c[ins]];\n                            assert(target.v.size()\
    \ == 1 && target.c.size() == 1);\n                            assert(bro.v.size()\
    \ == 1 && bro.c.size() == 2);\n                            bro.siz += target.siz;\n\
    \                            bro.v = {pool[bro.c[1]].mi, pool[target.c[0]].mi};\n\
    \                            bro.c.emplace_back(target.c[0]);\n              \
    \          }\n                        ++ins;\n                        for(; ins\
    \ < node.v.size(); ++ins){\n                            if(ins + 1 != node.v.size())\n\
    \                                swap(node.v[ins], node.v[ins + 1]);\n       \
    \                     swap(node.c[ins], node.c[ins + 1]);\n                  \
    \      }\n                        pool.free(node.c.back());\n                \
    \        node.v.pop_back();\n                        node.c.pop_back();\n    \
    \                    assert(node.v.size() == 1);\n                    }\n    \
    \                else{\n                        // 2\u3064\u3092\u30DE\u30FC\u30B8\
    \u3059\u308B\u30D1\u30BF\u30FC\u30F3\n                        Node& l = pool[node.c[0]];\n\
    \                        Node& r = pool[node.c[1]];\n                        assert(l.c.size()\
    \ + r.c.size() == 3);\n                        l.c.insert(l.c.end(), r.c.begin(),\
    \ r.c.end());\n                        assert(l.c.size() == 3);\n            \
    \            l.siz += r.siz;\n                        l.v = {pool[l.c[1]].mi,\
    \ pool[l.c[2]].mi};\n                        pool.free(node.c[1]);\n         \
    \               node.c.pop_back();\n                        assert(node.c.size()\
    \ == 1);\n                        node.v = {pool[l.c[1]].mi};\n              \
    \          node.mi = l.mi;\n                        node.siz = l.siz;\n      \
    \                  return 3;\n                    }\n                }\n     \
    \           node.v[0] = pool[node.c[1]].mi;\n                node.mi = pool[node.c[0]].mi;\n\
    \                return 1;\n            }\n            else if(res == 2){\n  \
    \              if(node.v.size() == 2){\n                    pool.free(node.c[ins]);\n\
    \                    for(; ins < node.v.size(); ++ins){\n                    \
    \    if(ins + 1 != node.v.size())\n                            swap(node.v[ins],\
    \ node.v[ins + 1]);\n                        swap(node.c[ins], node.c[ins + 1]);\n\
    \                    }\n                    node.v.pop_back();\n             \
    \       node.c.pop_back();\n                    node.mi = pool[node.c[0]].mi;\n\
    \                    return 1;\n                }\n                else{\n   \
    \                 assert(node.v.size() == 1);\n                    assert(node.c.size()\
    \ == 2);\n                    // \u5144\u5F1F\u30CE\u30FC\u30C9\u5206\u306E\u51E6\
    \u7406\u3092\u89AA\u306B\u4EFB\u305B\u308B\u3088\u3046\u306B\u3059\u308B\n   \
    \                 Node& ch = pool[node.c[ins ^ 1]];\n                    if(ch.v.size()\
    \ == 2){\n                        vector<int> vs = ch.v;\n                   \
    \     vector<Index> cs = ch.c;\n                        pool[node.c[0]].siz =\
    \ pool[node.c[1]].siz = 1;\n                        pool[node.c[0]].v = {vs[0]};\n\
    \                        pool[node.c[1]].v = {vs[1]};\n                      \
    \  pool[node.c[0]].mi = pool[node.c[0]].v[0];\n                        node.v[0]\
    \ = pool[node.c[1]].mi = pool[node.c[1]].v[0];\n                        node.siz\
    \ = 2;\n                        node.mi = pool[node.c[0]].mi;\n              \
    \          return 1;\n                    }\n                    node.c = {node.c[ins\
    \ ^ 1]};\n                    assert(ch.v.size() == 1);\n                    node.v\
    \ = {ch.mi};\n                    node.mi = ch.mi;\n                    node.siz\
    \ = ch.siz;\n                    assert(node.c.size() == 1);\n               \
    \     return 3;\n                }\n            }\n            if(ins)\n     \
    \           node.v[ins - 1] = pool[node.c[ins]].mi;\n            return res;\n\
    \        }\n    }\n\n    bool erase(T x){\n        if(root == nil)\n         \
    \   return false;\n        int res = erase(x, root);\n        if(res == 2)\n \
    \           root = nil;\n        if(res == 3){\n            // \u89AA\u3092\u898B\
    \u308B\u51E6\u7406\u3067\u8A70\u307E\u3063\u3066\u308B(\u9AD8\u3055\u304C\u6E1B\
    \u308B)\n            assert(pool[root].v.size() == 1);\n            assert(pool[root].c.size()\
    \ == 1);\n            Index new_root = pool[root].c[0];\n            pool.free(root);\n\
    \            root = new_root;\n        }\n        return res;\n    }\n\n    pair<T,\
    \ bool> lower_bound(T x, Index idx = nil){\n        if(idx == nil)\n         \
    \   idx = root;\n        if(root == nil)\n            return make_pair(T(), false);\n\
    \        bool fl = false;\n        T nex_val;\n        while(1){\n           \
    \ Node& node = pool[idx];\n            int ins = 0;\n            if(node.leaf){\n\
    \                for(; node.v[ins] < x && ins < node.v.size(); ++ins);\n     \
    \           assert(node.c.empty());\n                if(ins == node.v.size())\n\
    \                    return make_pair(fl ? nex_val : T(), fl);\n             \
    \   return make_pair(pool[idx].v[ins], true);\n            }\n            for(;\
    \ node.v[ins] <= x && ins < node.v.size(); ++ins);\n            idx = node.c[ins];\n\
    \            if(ins + 1 < node.c.size()){\n                fl = true;\n      \
    \          nex_val = pool[node.c[ins + 1]].mi;\n            }\n        }\n   \
    \ }\n\n    void print(Index idx = nil, int cnt = 0){\n        if(idx == nil)\n\
    \            idx = root;\n        if(idx == nil){\n            cout << \"nil(0)[0]\"\
    \ << endl;\n            return;\n        }\n        string cs = \"\";\n      \
    \  for(int i = 0; i < cnt; ++i)\n            cs += ' ';\n        auto& node =\
    \ pool[idx];\n        // cout << cs << \"idx: \" << idx << \" val: \" << node.v[0]\
    \ <<  \" / leaf: \" << node.leaf << endl;\n        for(int i = 0; i < max(node.v.size(),\
    \ node.c.size()); ++i){\n            if(!node.leaf){\n                if(i < node.c.size()){\n\
    \                    print(node.c[i], cnt + 8);\n                }\n         \
    \   }\n            if(i < node.v.size()){\n                if(i == 0){\n     \
    \               cout << cs << \" \" << node.v[i] << \" (\" << node.mi << \"){\"\
    \ << node.siz << \"}[\" << idx.idx << \"]\";\n                    if(node.leaf){\n\
    \                        cout << \"[\";\n                        for(int i = 0;\
    \ i < node.c.size(); ++i){\n                            cout << node.c[i].idx;\n\
    \                            if(i)\n                                cout << \"\
    /\";\n                        }\n                        cout << \"]\" << endl;\n\
    \                    }\n                    else\n                        cout\
    \ << endl;\n                }\n                else\n                    cout\
    \ << cs << \" \" << node.v[i] << endl;\n            }\n        }\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/twothreetree.cpp
  requiredBy: []
  timestamp: '2020-04-21 13:16:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/twothreetree.test.cpp
documentation_of: lib/classes/twothreetree.cpp
layout: document
redirect_from:
- /library/lib/classes/twothreetree.cpp
- /library/lib/classes/twothreetree.cpp.html
title: lib/classes/twothreetree.cpp
---
