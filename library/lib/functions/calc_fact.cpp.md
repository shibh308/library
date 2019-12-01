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


# :warning: lib/functions/calc_fact.cpp
* category: lib/functions


[Back to top page](../../../index.html)



## Code
```cpp
auto calc_fact = [mpow]{
	constexpr int N = 2e6;
	vector<mint> fact(N + 1, 1);
	vector<mint> inv(N + 1, 1);
	for(int i = 1; i < N; ++i){
		fact[i + 1] = fact[i] * (i + 1);
		inv[i + 1] = mpow(fact[i + 1], MOD - 2);
	}
	return make_pair(fact, inv);
};
vector<mint> fact, inv;
tie(fact, inv) = calc_fact();


```

[Back to top page](../../../index.html)

