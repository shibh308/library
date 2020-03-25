template <typename T>
struct SegmentSet{
    set<pair<T, T>> s;
    set<pair<T, T>> s_rev;
    SegmentSet(){}
    // [l, r)を追加する
    void insert(T l, T r){
        auto iter = get(l).second;
        if(iter != s.end() && iter->first <= l && r <= iter->second)
            return;
        vector<pair<T, T>> erase_elm;
        for(auto it = s.lower_bound(make_pair(l, numeric_limits<T>::min())); it != s.end() && it->first <= r; ++it)
            erase_elm.emplace_back(*it);
        for(auto it = s_rev.lower_bound(make_pair(l, numeric_limits<T>::min())); it != s_rev.end() && it->first <= r; ++it)
            erase_elm.emplace_back(it->second, it->first);
        for(auto& p : erase_elm){
            chmin(l, p.first);
            chmax(r, p.second);
            s.erase(p);
            s_rev.erase(make_pair(p.second, p.first));
        }
        s.emplace(l, r);
        s_rev.emplace(r, l);
    }
    // xが含まれるような区間を返す
    pair<bool, typename set<pair<T, T>>::const_iterator> get(T x){
        auto it = s.lower_bound(make_pair(x, numeric_limits<T>::min()));
        if(it != s.begin())
            --it;
        return make_pair(x < it->second, it);
    }
    set<pair<T, T>>& operator*(){return s;}
};

