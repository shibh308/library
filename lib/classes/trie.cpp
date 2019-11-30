template <int size = 26, int start = 'a'>
struct Trie{
    struct Node{
        // 値, prefixに含む文字列の数, 文字列の数
        int val, len, cnt, exist_cnt;
        // 子のindex, 子の(indexの)一覧
        vector<int> next, exist;
        Node(int val = -1, int len = 0, bool back = false) : val(val), len(len), cnt(0), exist_cnt(back), next(size, -1){}
    };

    vector<Node> nodes;
    Trie() : nodes(1){}

    int insert(string& s, int str_index = 0){
        int pos = 0, idx = str_index;
        while(idx != s.size()){
            ++nodes[pos].cnt;
            int c = s[idx] - start;
            assert(c < size);

            if(nodes[pos].next[c] == -1){
                nodes[pos].next[c] = nodes.size();
                nodes[pos].exist.emplace_back(nodes.size());
                nodes.emplace_back(c, nodes[pos].len + 1);
            }
            pos = nodes[pos].next[c];
            ++idx;
        }
        ++nodes[pos].cnt;
        ++nodes[pos].exist_cnt;
        return pos;
    }

    // (sの部分文字列, s, sを部分文字列に含む文字列)に対して関数を実行する
    // ラムダ内でtrie.nodes[idx].exist_cntを判定する事で, 挿入された文字列そのもの以外判定しなくなる
    void query(string& s, function<void(int, string&)> f, bool from_prefix, bool correct, bool to_prefix, int str_index = 0){
        int pos = 0, idx = str_index;
        string str;
        while(idx != s.size()){
            if(from_prefix)
                f(pos, str);
            int c = s[idx] - start;
            assert(c < size);

            if(nodes[pos].next[c] == -1)
                return ;
            pos = nodes[pos].next[c];
            str += static_cast<char>(nodes[pos].val + start);
            ++idx;
        }
        if(correct)
            f(pos, str);
        function<void(int)> dfs = [&](int pos){
            for(auto& next : nodes[pos].exist){
                char c = nodes[next].val + start;
                if(to_prefix)
                    f(pos, str);
                str += c;
                dfs(next);
                str.pop_back();
            }
        };
        dfs(pos);
    }
};

