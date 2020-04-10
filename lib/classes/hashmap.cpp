template <typename T, typename U>
struct HashMap{
    const __int128_t z = 0xf332ac987401cba5;
    uint64_t n, q, d;

    vector<pair<T, U>> v;

    T del, null;

    HashMap(T del_flag, T null_flag) : n(0), q(0), d(1), del(del_flag), null(null_flag), v(1LL << d, make_pair(null_flag, U())){}

    uint64_t hash(T key){return uint64_t((z * __int128_t(key)) >> (64 - d)) & ((1LL << d) - 1);}

    pair<U, bool> find(T x){
        int cnt = 0;
        for(uint64_t i = hash(x); v[i].first != null; i = (i + 1 == (1 << d) ? 0 : i + 1), ++cnt)
            if(v[i].first == x)
                return make_pair(v[i].second, true);
        return make_pair(U(), false);
    }

    bool add(T x, U val){
        if(find(x).second)
            return false;
        if(((q + 1) << 1) > (1 << d))
            resize();
        uint64_t i = hash(x);
        for(; v[i].first != null && v[i].first != del; i = (i + 1 == (1 << d) ? 0 : i + 1));
        q += (v[i].first == null);
        ++n;
        v[i] = make_pair(x, val);
        return true;
    }

    bool erase(T x){
        uint64_t i = hash(x);
        for(; v[i].first != null && v[i].first != x; i = (i + 1 == (1 << d) ? 0 : i + 1));
        if(v[i].first == null)
            return false;
        --n;
        v[i] = make_pair(del, U());
        return true;
    }

    void resize(){
        for(d = 1; (1 << d) < 3 * n; ++d);
        vector<pair<T, U>> old_table;
        q = n;
        swap(old_table, v);
        v.assign(1 << d, make_pair(null, U()));
        for(int i = 0; i < old_table.size(); ++i)
            if(old_table[i].first != null && old_table[i].first != del)
                add(old_table[i].first, old_table[i].second);
    }
};
