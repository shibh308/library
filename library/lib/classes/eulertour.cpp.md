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


# :heavy_check_mark: lib/classes/eulertour.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/eulertour.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-06 18:23:18+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/eulertour.test.cpp.html">verify/eulertour.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct EulerTour{
    int n;
    vector<int> in, out;
    EulerTour(vector<vector<int>>& edges, int par = 0) : n(edges.size()), in(n, -1), out(n, -1){
        int cnt = 0;
        function<void(int)> f = [&](int x){
            in[x] = cnt++;
            for(auto y : edges[x]){
                if(in[y] == -1)
                    f(y);
            }
            out[x] = cnt;
        };
        f(par);
    }
    int get_pos(int x){
        return in[x];
    }
    // 自身を含みたくない場合は(in[x] + 1, out[x])
    pair<int,int> get_subtree(int x){
        return make_pair(in[x], out[x]);
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/eulertour.cpp"
struct EulerTour{
    int n;
    vector<int> in, out;
    EulerTour(vector<vector<int>>& edges, int par = 0) : n(edges.size()), in(n, -1), out(n, -1){
        int cnt = 0;
        function<void(int)> f = [&](int x){
            in[x] = cnt++;
            for(auto y : edges[x]){
                if(in[y] == -1)
                    f(y);
            }
            out[x] = cnt;
        };
        f(par);
    }
    int get_pos(int x){
        return in[x];
    }
    // 自身を含みたくない場合は(in[x] + 1, out[x])
    pair<int,int> get_subtree(int x){
        return make_pair(in[x], out[x]);
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

