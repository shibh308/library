template <typename T, int W>
struct WaveletMatrix{

    array<BitVector, W> bv;
    array<int, W> zero_cnt;

    WaveletMatrix(vector<T>& a){
        int n = a.size();
        vector<T> v(a);
        for(int i = W - 1; i >= 0; --i){
            vector<uint64_t> b((n >> 6) + 1, 0);
            vector<T> v1, v2;
            for(int j = 0; j < n; ++j){
                ((v[j] >> i) & 1 ? v2 : v1).push_back(v[j]);
                b[j >> 6] |= uint64_t((v[j] >> i) & 1) << (j & 63);
            }
            for(int j = 0; j < v.size(); ++j)
                v[j] = (j < v1.size() ? v1[j] : v2[j - v1.size()]);
            bv[i].v = move(b);
            bv[i].build();
            zero_cnt[i] = bv[i].rank(n, 0);
        }
    }

    // [l, r)内のxの数
    int count(int l, int r, T x){
        for(int i = W - 1; i >= 0; --i){
            bool fl = (x >> i) & 1;
            int st = bv[i].rank(l, fl);
            int en = bv[i].rank(r, fl);
            l = (fl ? zero_cnt[i] : 0) + st;
            r = (fl ? zero_cnt[i] : 0) + en;
        }
        return r - l;
    }

    // [l, r)内で[0, x)を満たす値の数
    int count_lower(int l, int r, T x){
        int cnt = 0;
        for(int i = W - 1; i >= 0; --i){
            bool fl = (x >> i) & 1;
            int st = bv[i].rank(l, fl);
            int en = bv[i].rank(r, fl);
            if(fl){
                st += zero_cnt[i];
                en += zero_cnt[i];
                cnt += (bv[i].rank(r, 0) - bv[i].rank(l, 0));
            }
            l = st, r = en;
        }
        return cnt;
    }

    // [l, r)内で[x, y)を満たす値の数
    int count_range(int l, int r, T x, T y){
        return count_lower(l, r, y) - count_lower(l, r, x);
    }

    // 0-indexedでk番目に小さいものを返す
    T kth_min(int l, int r, int k){
        T ans = 0;
        for(int i = W - 1; i >= 0; --i){
            int st = bv[i].rank(l, 0);
            int en = bv[i].rank(r, 0);
            if(en - st <= k){
                k -= en - st;
                l = zero_cnt[i] + bv[i].rank(l, 1);
                r = zero_cnt[i] + bv[i].rank(r, 1);
                ans |= (1uLL << i);
            }
            else{
                l = st, r = en;
            }
        }
        return ans;
    }
};

