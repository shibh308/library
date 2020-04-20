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


# :heavy_check_mark: lib/classes/memorypool.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/memorypool.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-20 22:13:13+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/twothreetree.test.cpp.html">verify/twothreetree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T>
struct MemoryPool{
    int siz, idx;
    stack<int> st;
    vector<T*> pool;
    MemoryPool() : siz(1), idx(0){}
    void resize(){
        pool.emplace_back(new T[siz]);
        siz <<= 1;
    }
    int alloc(){
        if(!st.empty()){
            int res = st.top();
            st.pop();
            return res;
        }
        if(++idx == siz)
            resize();
        return idx;
    }
    void free(int x){
        st.push(x);
    }
    T& operator[](int x){return pool[31 - __builtin_clz(x)][x & ~(1 << (31 - __builtin_clz(x)))];}
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/memorypool.cpp"
template <typename T>
struct MemoryPool{
    int siz, idx;
    stack<int> st;
    vector<T*> pool;
    MemoryPool() : siz(1), idx(0){}
    void resize(){
        pool.emplace_back(new T[siz]);
        siz <<= 1;
    }
    int alloc(){
        if(!st.empty()){
            int res = st.top();
            st.pop();
            return res;
        }
        if(++idx == siz)
            resize();
        return idx;
    }
    void free(int x){
        st.push(x);
    }
    T& operator[](int x){return pool[31 - __builtin_clz(x)][x & ~(1 << (31 - __builtin_clz(x)))];}
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

