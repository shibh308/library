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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: lib/classes/succinctbitvector.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/succinctbitvector.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-25 14:12:39+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct FastSelect {
    static const int l_size = 65536;
    static const int m_size = 256;
    static const int mb = 255;
    static const int s_size = 32;
    static const int ss_size = 8;

    struct Table{
        uint16_t l_table[m_size][m_size][s_size];
        uint32_t s_table[m_size];
        Table() : l_table(), s_table(){
            for(int i = 0; i < m_size; ++i)
                for(int j = 0; j < m_size; ++j){
                    for(int k = 0; k < s_size; ++k)
                        l_table[i][j][k] = 0;
                    for(int k = 0; k < m_size; ++k){
                        if(k >= i && k < i + j)
                            l_table[i][j][k >> 3] |= 1 << ((k & 7) * 2);
                        else if(k >= i + j)
                            l_table[i][j][k >> 3] |= 2 << ((k & 7) * 2);
                    }
                }
            for(int i = 0; i < m_size; ++i){
                s_table[i] = 0;
                for(int j = 0; j < ss_size; ++j){
                    int c = 0;
                    for(int k = 0; k < ss_size; ++k){
                        c += bool(i & (1 << k));
                        if(j < c){
                            s_table[i] |= (k << (j * 4));
                            break;
                        }
                    }
                }
            }
        }
    };
    const static Table tab;

    struct AbstractSelect{virtual int select(int x) = 0;};
    struct BigSelect : public AbstractSelect{
        vector<int> w;
        BigSelect(vector<uint32_t>& v, int l, int r, bool fl){
            for(int i = l; i < r; ++i){
                if(bool(v[i / s_size] & (1u << (i % s_size))) == fl){
                    w.emplace_back(i - l);
                }
            }
        }
        int select(int x){return w[x];}
    };
    struct SmallSelect : public AbstractSelect{
        vector<uint32_t>& v;
        int l;
        bool fl;
        vector<int> siz;
        vector<unsigned char> w;
        bool flag(int i){
            return bool(v[(l + i) / s_size] & (1u << ((l + i) % s_size))) == fl;
        }
        uint16_t get(int i){
            i += l;
            if(i % s_size <= 24){
                return (v[i / s_size] >> (i % s_size)) & 255;
            }
            else{
                int l_bit = 32 - (i % s_size);
                uint16_t lv = (v[i / s_size] >> (i % s_size));
                uint16_t rv = v[i / s_size + 1] & ((1u << (8 - l_bit)) - 1);
                return lv + (rv << l_bit);
            }
        }
        SmallSelect(vector<uint32_t>& v, int l, int r, bool fl) : v(v), l(l), fl(fl){
            int n = r - l;
            siz.emplace_back(0);
            for(int k = (n + 7) / 8; k != 1; k = (k + 3) / 4){
                siz.emplace_back(siz.back() + (k + 3) / 4 * 4);
            }
            siz.emplace_back(siz.back() + 1);
            w.assign(siz.back(), 0);
            for(int i = 0; i < n; ++i){
                if(flag(i)){
                    ++w[i / ss_size];
                }
            }
            for(int i = 0; i < siz.size() - 2; ++i){
                for(int j = siz[i]; j < siz[i + 1]; ++j){
                    w[siz[i + 1] + (j - siz[i]) / 4] += w[j];
                }
            }
        }
        int select(int x){
            int d = siz.size() - 1;
            int idx = siz[d];
            for(; d > 0; --d){
                int ch = siz[d - 1] + (idx - siz[d]) * 4;
                int res = (tab.l_table[w[ch]][w[ch + 1]][x >> 3] >> ((x & 7) * 2)) & 3;
                if(res < 2){
                    if(res)
                        x -= w[ch];
                    idx = ch + res;
                }
                else{
                    x -= w[ch] + w[ch + 1];
                    int res2 = (tab.l_table[w[ch + 2]][w[ch + 3]][x >> 3] >> ((x & 7) * 2)) & 3;
                    assert(res2 < 2);
                    if(res2)
                        x -= w[ch + 2];
                    idx = ch + 2 + res2;
                }
            }
            return idx * ss_size + ((tab.s_table[get(idx * ss_size) ^ (fl ? 0 : 255)] >> (x * 4)) & 15);
        }
    };

    int cnt;
    vector<AbstractSelect*> b;
    vector<int> st;
    FastSelect(){}
    FastSelect(int n, vector<uint32_t>& v, bool fl) : cnt(0){
        int s = 0;
        for(int i = 0; i < n; ++i){
            if(bool(v[i / s_size] & (1u << (i % s_size))) == fl){
                ++cnt;
                if(cnt % mb == 0){
                    if(i - s + 1 > l_size)
                        b.emplace_back(new BigSelect(v, s, i + 1, fl));
                    else
                        b.emplace_back(new SmallSelect(v, s, i + 1, fl));
                    st.emplace_back(s);
                    s = i + 1;
                }
            }
        }
        if(s != n){
            st.emplace_back(s);
            b.emplace_back(new BigSelect(v, s, n, fl));
        }
    }
    int select(int x){
        if(x >= cnt)
            return -1;
        else{
            return st[x / mb] + b[x / mb]->select(x % mb);
        }
    }
};

const FastSelect::Table FastSelect::tab = FastSelect::Table();

struct SuccinctBitVector {
    const int m_size = 256;
    const int s_size = 32;
    int n;
    vector<uint32_t> l;
    vector<unsigned char> m;
    vector<uint32_t> s;
    FastSelect sel[2];
    SuccinctBitVector(int n) : n(n), l((n + m_size - 1) / m_size + 1, 0), m((n + s_size - 1) / s_size + 1, 0), s((n + s_size - 1) / s_size, 0){}
    void set(int x, bool fl = true){
        if(bool(s[x / s_size] & (1u << (x % s_size))) == fl)
            return;
        if(fl){
            s[x / s_size] |= (1u << (x % s_size));
            ++l[x / m_size + 1];
            ++m[x / s_size + 1];
        }
        else{
            s[x / s_size] &= ~(1u << (x % s_size));
            --l[x / m_size + 1];
            --m[x / s_size + 1];
        }
    }
    void build(){
        for(int i = 0; i < l.size() - 1; ++i)
            l[i + 1] += l[i];
        for(int i = 0; i < m.size() - 1; ++i){
            if(i % 8 != 7)
                m[i + 1] += m[i];
            else
                m[i + 1] = 0;
        }
        sel[0] = FastSelect(n, s, 0);
        sel[1] = FastSelect(n, s, 1);
    }
    // [0, x)
    int rank(int x){
        return l[x / m_size] + m[x / s_size] + __builtin_popcount(s[x / s_size] & ((1uLL << (x % s_size)) - 1));
    }
    int rank(int x, bool fl){
        return fl ? rank(x) : x - rank(x);
    }
    // flがx回目に出現する位置(0-indexedなので注意)
    int select(int x, bool fl = true){
        return sel[fl].select(x);
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/succinctbitvector.cpp"
struct FastSelect {
    static const int l_size = 65536;
    static const int m_size = 256;
    static const int mb = 255;
    static const int s_size = 32;
    static const int ss_size = 8;

    struct Table{
        uint16_t l_table[m_size][m_size][s_size];
        uint32_t s_table[m_size];
        Table() : l_table(), s_table(){
            for(int i = 0; i < m_size; ++i)
                for(int j = 0; j < m_size; ++j){
                    for(int k = 0; k < s_size; ++k)
                        l_table[i][j][k] = 0;
                    for(int k = 0; k < m_size; ++k){
                        if(k >= i && k < i + j)
                            l_table[i][j][k >> 3] |= 1 << ((k & 7) * 2);
                        else if(k >= i + j)
                            l_table[i][j][k >> 3] |= 2 << ((k & 7) * 2);
                    }
                }
            for(int i = 0; i < m_size; ++i){
                s_table[i] = 0;
                for(int j = 0; j < ss_size; ++j){
                    int c = 0;
                    for(int k = 0; k < ss_size; ++k){
                        c += bool(i & (1 << k));
                        if(j < c){
                            s_table[i] |= (k << (j * 4));
                            break;
                        }
                    }
                }
            }
        }
    };
    const static Table tab;

    struct AbstractSelect{virtual int select(int x) = 0;};
    struct BigSelect : public AbstractSelect{
        vector<int> w;
        BigSelect(vector<uint32_t>& v, int l, int r, bool fl){
            for(int i = l; i < r; ++i){
                if(bool(v[i / s_size] & (1u << (i % s_size))) == fl){
                    w.emplace_back(i - l);
                }
            }
        }
        int select(int x){return w[x];}
    };
    struct SmallSelect : public AbstractSelect{
        vector<uint32_t>& v;
        int l;
        bool fl;
        vector<int> siz;
        vector<unsigned char> w;
        bool flag(int i){
            return bool(v[(l + i) / s_size] & (1u << ((l + i) % s_size))) == fl;
        }
        uint16_t get(int i){
            i += l;
            if(i % s_size <= 24){
                return (v[i / s_size] >> (i % s_size)) & 255;
            }
            else{
                int l_bit = 32 - (i % s_size);
                uint16_t lv = (v[i / s_size] >> (i % s_size));
                uint16_t rv = v[i / s_size + 1] & ((1u << (8 - l_bit)) - 1);
                return lv + (rv << l_bit);
            }
        }
        SmallSelect(vector<uint32_t>& v, int l, int r, bool fl) : v(v), l(l), fl(fl){
            int n = r - l;
            siz.emplace_back(0);
            for(int k = (n + 7) / 8; k != 1; k = (k + 3) / 4){
                siz.emplace_back(siz.back() + (k + 3) / 4 * 4);
            }
            siz.emplace_back(siz.back() + 1);
            w.assign(siz.back(), 0);
            for(int i = 0; i < n; ++i){
                if(flag(i)){
                    ++w[i / ss_size];
                }
            }
            for(int i = 0; i < siz.size() - 2; ++i){
                for(int j = siz[i]; j < siz[i + 1]; ++j){
                    w[siz[i + 1] + (j - siz[i]) / 4] += w[j];
                }
            }
        }
        int select(int x){
            int d = siz.size() - 1;
            int idx = siz[d];
            for(; d > 0; --d){
                int ch = siz[d - 1] + (idx - siz[d]) * 4;
                int res = (tab.l_table[w[ch]][w[ch + 1]][x >> 3] >> ((x & 7) * 2)) & 3;
                if(res < 2){
                    if(res)
                        x -= w[ch];
                    idx = ch + res;
                }
                else{
                    x -= w[ch] + w[ch + 1];
                    int res2 = (tab.l_table[w[ch + 2]][w[ch + 3]][x >> 3] >> ((x & 7) * 2)) & 3;
                    assert(res2 < 2);
                    if(res2)
                        x -= w[ch + 2];
                    idx = ch + 2 + res2;
                }
            }
            return idx * ss_size + ((tab.s_table[get(idx * ss_size) ^ (fl ? 0 : 255)] >> (x * 4)) & 15);
        }
    };

    int cnt;
    vector<AbstractSelect*> b;
    vector<int> st;
    FastSelect(){}
    FastSelect(int n, vector<uint32_t>& v, bool fl) : cnt(0){
        int s = 0;
        for(int i = 0; i < n; ++i){
            if(bool(v[i / s_size] & (1u << (i % s_size))) == fl){
                ++cnt;
                if(cnt % mb == 0){
                    if(i - s + 1 > l_size)
                        b.emplace_back(new BigSelect(v, s, i + 1, fl));
                    else
                        b.emplace_back(new SmallSelect(v, s, i + 1, fl));
                    st.emplace_back(s);
                    s = i + 1;
                }
            }
        }
        if(s != n){
            st.emplace_back(s);
            b.emplace_back(new BigSelect(v, s, n, fl));
        }
    }
    int select(int x){
        if(x >= cnt)
            return -1;
        else{
            return st[x / mb] + b[x / mb]->select(x % mb);
        }
    }
};

const FastSelect::Table FastSelect::tab = FastSelect::Table();

struct SuccinctBitVector {
    const int m_size = 256;
    const int s_size = 32;
    int n;
    vector<uint32_t> l;
    vector<unsigned char> m;
    vector<uint32_t> s;
    FastSelect sel[2];
    SuccinctBitVector(int n) : n(n), l((n + m_size - 1) / m_size + 1, 0), m((n + s_size - 1) / s_size + 1, 0), s((n + s_size - 1) / s_size, 0){}
    void set(int x, bool fl = true){
        if(bool(s[x / s_size] & (1u << (x % s_size))) == fl)
            return;
        if(fl){
            s[x / s_size] |= (1u << (x % s_size));
            ++l[x / m_size + 1];
            ++m[x / s_size + 1];
        }
        else{
            s[x / s_size] &= ~(1u << (x % s_size));
            --l[x / m_size + 1];
            --m[x / s_size + 1];
        }
    }
    void build(){
        for(int i = 0; i < l.size() - 1; ++i)
            l[i + 1] += l[i];
        for(int i = 0; i < m.size() - 1; ++i){
            if(i % 8 != 7)
                m[i + 1] += m[i];
            else
                m[i + 1] = 0;
        }
        sel[0] = FastSelect(n, s, 0);
        sel[1] = FastSelect(n, s, 1);
    }
    // [0, x)
    int rank(int x){
        return l[x / m_size] + m[x / s_size] + __builtin_popcount(s[x / s_size] & ((1uLL << (x % s_size)) - 1));
    }
    int rank(int x, bool fl){
        return fl ? rank(x) : x - rank(x);
    }
    // flがx回目に出現する位置(0-indexedなので注意)
    int select(int x, bool fl = true){
        return sel[fl].select(x);
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

