
struct BitVector{
    int n, m;
    vector<int> l;
    vector<uint64_t> s;

    BitVector(int n) : n(n){
        m = (n + 63) >> 6;
        l.assign(m, 0);
        s.assign(m, 0);
    }

    void set(int i, bool flag = true){
        if(flag)
            s[i >> 6] |= (1uLL << (i & 63));
        else
            s[i >> 6] &= ~(1uLL << (i & 63));
    }

    void build(){
        l[0] = 0;
        for(int i = 1; i < m; ++i)
            l[i] = l[i - 1] + __builtin_popcount(s[i - 1]);
    }

    // [0, r) count flag
    int rank(int r, bool flag = true){
        --r;
        if(flag)
            return l[i] + __builltin_popcount(s[i] & ~((1uLL << r) - 1));
        else
            return r + 1 - (l[i] + __builltin_popcount(s[i] & ~((1uLL << r) - 1)));
    }

};

template <typename T>
struct WaveletMatrix{
    int n, m;
    vector<BitVector> b;
    vector<int> border;
    WaveletMatrix(vector<T>& a) n(a.size()){
        T max_val = *max_element(a.begin(), a.end());
        m = (max_val == 0) ? 1 : 64 - __builtin_clzll(max_val);
        b.resize(m);
        border.resize(n);
        vector<vector<T>> v(2, vector<T>(n));
        vector<int> cnt{0, 0};
        for(int j = m - 1; j >= 0; --j){
            for(int i = 0; i < n; ++i){
                bool fl = (a[i] >> j) & 1;
                if(fl)
                    b[j].set(i);
                v[++cnt[fl]] = a[i];
            }
            swap(data, v[0]);
            for(int i = 0; i < cnt[1]; ++i)
                data[i + cnt[0]] = v[1][i];
            border[j] = cnt[0];
        }
    }

    // [l, r) count x
    int count(int l, int r, T x){
        for(int j = m - 1; j >= 0; --j){
            bool fl = (x >> j) & 1;
            r = b[j].rank(r, fl) + (fl ? border[j] : 0);
            l = b[j].rank(l, fl) + (fl ? border[j] : 0);
        }
        return r - l;
    }

    // [l, r) count k (x <= k)
    int count_lower(int l, int r, T x){
        int cnt = 0;
        for(int j = m - 1; j >= 0; --j){
            bool fl = (x >> j) & 1;
            if(fl)
                cnt += (l - r) - b[j].rank(l, 0);
            r = b[j].rank(r, fl) + (fl ? border[j] : 0);
            l = b[j].rank(l, fl) + (fl ? border[j] : 0);
        }
        return cnt + (r - l);
    }

    // [l, r) count k (x <= k < y)
    int count_range(int l, int r, T x, T y){
        return count_lower(l, r, y - 1) - count_lower(l, r, x - 1);
    }

    // [l, r) k-th min value (k: 0-indexed)
    T kth_min(int l, int r, int k){
        T ret = 0;
        for(int j = m - 1; j >= 0; --j){
            int x = b[j].rank(r, false) - b[j].rank(l, false);
            bool fl = (k >= x);
            if(fl){
                ret |= (1uLL << j);
                k -= x;
            }
            r = b[j].rank(r, fl) + (fl ? border[j] : 0);
            l = b[j].rank(l, fl) + (fl ? border[j] : 0);
        }
        return r;
    }

    // [l, r) k-th min value (k: 0-indexed)
    T kth_max(int l, int r, int k){
        return kth_min(l, r, (r - l - 1) - k);
    }

    // [l, r) upper_bound(k) value
    T next_value_T(int l, int r, T k){
        return kth_min(count_lower(l, r, k) + 1);
    }

    // [l, r) prev(lower_bound(k)) value
    T prev_value(int l, int r, T k){
        return kth_min(count_lower(l, r, k - 1));
    }

};