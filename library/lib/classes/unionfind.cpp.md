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


# :warning: lib/classes/unionfind.cpp
* category: lib/classes


[Back to top page](../../../index.html)



## Verified
* :warning: [verify/unionfind.test.cpp](../../../verify/verify/unionfind.test.cpp.html)


## Code
```cpp
struct UnionFind{
    vector<int> par;
    int count;
    UnionFind(int n) : par(n, -1), count(0){}
    int Find(int x){return par[x] < 0 ? x : Find(par[x]);}
    int Size(int x){return par[x] < 0 ? -par[x] : Size(par[x]);}
    bool Unite(int x, int y){
        x = Find(x);
        y = Find(y);
        if(x == y)
            return false;
        if(par[x] > par[y])
            swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return ++count;
    }
};


```

[Back to top page](../../../index.html)

